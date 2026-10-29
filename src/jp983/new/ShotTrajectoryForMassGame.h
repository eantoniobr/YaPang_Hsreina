// Original: unknown, JP-only RTTI class ShotTrajectoryForMassGame (JP 983 exe)
#ifndef PG_JP983_NEW_SHOTTRAJECTORYFORMASSGAME_H
#define PG_JP983_NEW_SHOTTRAJECTORYFORMASSGAME_H

#include "defines.h"
#include "padding.h"

#include <vector>

#include "jp983/client/ProjectG/actor.h"

class WRTTI;

// A point of a drawn shot trajectory (12 bytes).
struct ShotTrajectoryPoint
{
    float x; // 0x0
    float y; // 0x4
    float z; // 0x8
};

// One trajectory's animation state (0x30 bytes, 12 of them at +0xe0).
struct ShotTrajectoryPath
{
    int m_index;                  // 0x00, last point reached
    float m_progress;             // 0x04
    float m_fade;                 // 0x08, 0..1
    int m_eventIndex;             // 0x0c, -1 once its event fired
    PADDING(0x10, 0x14);
    unsigned char m_flags;        // 0x14
    PADDING(0x15, 0x18);
    bool m_active;                // 0x18
    float m_startTime;            // 0x1c
    std::vector<float> m_values;  // 0x20
};

// 12-byte entry of the array at +0x320; +8 receives the event kind.
struct ShotTrajectoryEvent
{
    PADDING(0x0, 0x8);
    int m_kind;                   // 0x8
};

// Unnamed member object at +0x3b4; 0x64d290 handles message 0x312.
class ShotTrajectoryState
{
public:
    void OnTrajectoryMessage(int param); // 0x64d290
};

// JP-only class (RTTI name ShotTrajectoryForMassGame; bases IActor, IObject,
// CRenderFuncPtr), vtable at 0xd16874, IActor's 15 slots; slots 2, 7-10 and
// 12-14 keep IActor's bodies. CRenderFuncPtr's vtable 0xd16864 at +0x18 is
// not modelled (slot 1 of it is 0x64be90, the draw function). The layout is
// known only as far as the bodies read it.
class ShotTrajectoryForMassGame : public IActor
{
public:
    static const WRTTI m_RTTI;                                // 0xe78d0c

    ShotTrajectoryForMassGame();
    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x64dac0)
    virtual ~ShotTrajectoryForMassGame(void);                 // 1 (??_G 0x64dd50; ~ 0x64dad0, not split)
    virtual void OnLoad(void);                                // 3 (0x64b2a0, empty)
    virtual void OnInit(void);                                // 4 (0x64dd80)
    virtual void OnReload(void);                              // 5 (0x64b2b0)
    virtual void OnProcess(float elapsed);                    // 6 (0x64ee70)

    bool IsPlaying();                                 // 0x64bd00
    void Finish();                                    // 0x64ec10

protected:
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x64d6e0)

private:
    PADDING(0x18, 0x20);
    std::vector<ShotTrajectoryPoint> m_trajectories[12]; // 0x20
    ShotTrajectoryPath m_paths[12];                   // 0xe0
    ShotTrajectoryEvent m_events[12];                 // 0x320
    int m_trajectoryCount;                            // 0x3b0
    ShotTrajectoryState m_state;                      // 0x3b4
    PADDING(0x3b5, 0x3d0);
    float m_time;                                     // 0x3d0
    PADDING(0x3d4, 0x3dc);
    float m_speed;                                    // 0x3dc
    PADDING(0x3e0, 0x3e4);
    float m_elapsed;                                  // 0x3e4
    PADDING(0x3e8, 0x3f8);
    float m_duration;                                 // 0x3f8
    float m_step;                                     // 0x3fc
    PADDING(0x400, 0x404);
    bool m_eventsEnabled;                             // 0x404

    LAYOUT_CHECK_FRIEND;
};

BEGIN_LAYOUT_CHECK(ShotTrajectoryForMassGame)
    CHECK_FIELD(ShotTrajectoryForMassGame, m_trajectories, 0x20);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_paths, 0xe0);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_events, 0x320);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_trajectoryCount, 0x3b0);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_state, 0x3b4);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_time, 0x3d0);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_speed, 0x3dc);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_elapsed, 0x3e4);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_duration, 0x3f8);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_step, 0x3fc);
    CHECK_FIELD(ShotTrajectoryForMassGame, m_eventsEnabled, 0x404);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_SHOTTRAJECTORYFORMASSGAME_H
