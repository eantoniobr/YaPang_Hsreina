// Original: unknown, JP-only RTTI class ShotTrajectoryForMassGame (JP 983 exe)
#include "ShotTrajectoryForMassGame.h"

#include "jp983/client/ProjectG/SharedDoc.h"

// The current time a delayed message's delivery time is compared with
// (KR g_CurrentTime).
extern "C" unsigned long data_f022d4;

// Unnamed double constants of Update (values not read yet).
extern "C" const double data_d05d90; // lead points per unit of speed
extern "C" const double data_cff068; // trail points per unit of speed
extern "C" const double data_d05020; // points per unit of progress

// Constructor (VA unknown). Defining it here emits the vtable and with it
// the ??_G at 0x64dd50, which calls the out-of-line
// ~ShotTrajectoryForMassGame (0x64dad0) as the original does.
ShotTrajectoryForMassGame::ShotTrajectoryForMassGame()
{
}

// 0x64b2a0
void ShotTrajectoryForMassGame::OnLoad(void)
{
}

// 0x64b2b0
void ShotTrajectoryForMassGame::OnReload(void)
{
    OnLoad();
}

// 0x64d6e0
void ShotTrajectoryForMassGame::HandleMsg(const MsgObject& msg)
{
    if (msg.m_reserved > data_f022d4) {
        StoreDelayedMsg(msg);
    } else if (msg.m_msg == 0x312) {
        m_state.OnTrajectoryMessage(msg.m_param1);
    }
}

// 0x64dac0
const WRTTI* ShotTrajectoryForMassGame::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x64dd80
void ShotTrajectoryForMassGame::OnInit(void)
{
    for (int i = 0; i < 12; ++i) {
        m_trajectories[i].clear();
    }
    m_trajectoryCount = 0;
}

// 0x64ee70
void ShotTrajectoryForMassGame::OnProcess(float elapsed)
{
    m_time += elapsed;
    m_elapsed += elapsed;
    float advance = m_speed * elapsed;
    int lead = (int)(m_speed * data_d05d90);
    float step = m_step;
    int trail = (int)(m_speed * data_cff068);
    for (int i = 0; i < 12; ++i) {
        std::vector<ShotTrajectoryPoint>& points = m_trajectories[i];
        if (points.empty() || !m_paths[i].m_active || m_paths[i].m_startTime > m_elapsed) {
            continue;
        }
        m_paths[i].m_progress += advance;
        if (m_paths[i].m_index > points.size() - lead) {
            step *= 2.0f;
            trail = 0;
        }
        if (m_eventsEnabled && m_paths[i].m_index >= m_paths[i].m_eventIndex && m_paths[i].m_eventIndex != -1) {
            if ((m_paths[i].m_flags & 0x70) && (data_e47dbc->m_pGolfDoc->m_gameMode & 0xfffffdff)) {
                m_events[i].m_kind = 3;
            } else {
                m_events[i].m_kind = 4;
            }
            m_paths[i].m_eventIndex = -1;
        }
        int last = m_paths[i].m_index - trail;
        last = last < 0 ? 0 : last;
        for (int j = 0; j <= last; ++j) {
            m_paths[i].m_values[j] -= step * elapsed;
            if (m_paths[i].m_values[j] < 0.0f) {
                m_paths[i].m_values[j] = 0.0f;
            }
        }
        if (m_paths[i].m_values.back() <= 0.0f) {
            points.clear();
        }
        int reached = (int)(m_paths[i].m_progress * data_d05020);
        int previous = m_paths[i].m_index;
        unsigned int end = points.size() - 1;
        m_paths[i].m_index = reached > end ? end : reached;
        if (m_paths[i].m_index != previous) {
            m_paths[i].m_fade = 0.0f;
        } else {
            m_paths[i].m_fade += advance;
            if (m_paths[i].m_fade > 1.0f) {
                m_paths[i].m_fade = 1.0f;
            }
        }
    }
    if (m_time > m_duration) {
        m_time = 0.0f;
        if (!IsPlaying()) {
            Finish();
        }
    }
}
