// Original: unknown, JP-only RTTI class CTutorGuide (JP 983 exe)
#include "CTutorGuide.h"

extern "C" CSceneManager* data_e741c0;
extern "C" TutorGuideApp* data_e47db0;

// Constructor (VA unknown): defined here to emit the vtable; the real one
// is elsewhere.
CTutorGuide::CTutorGuide(void)
{
}

// Inlined into the scalar deleting destructor at 0x6b2a80.
CTutorGuide::~CTutorGuide(void)
{
}

// 0x6b1f60
void CTutorGuide::OnInit(void)
{
}

// 0x6b1f70
void CTutorGuide::OnDestroy(void)
{
    for (int i = 0; i < 4; i++)
        m_entries[i].Release();
}

// 0x6b1fa0
void CTutorGuide::OnDisplay(void)
{
}

// 0x6b2490
void CTutorGuide::OnPreLoadInit(void)
{
    // The element name is the string at 0xd19df0; its text is not read yet
    // (Binary Ninja was unavailable), "TutorGuide" stands in for it.
    data_e741c0->RegisterElement((eObjType)6, 0, this, "TutorGuide", 0, 0);
}

// 0x6b24c0
void CTutorGuide::OnLoad(void)
{
    for (int i = 0; i < 4; i++)
        m_entries[i].Load(i);
}

// 0x6b26e0
void CTutorGuide::OnProcess(float elapsed)
{
    if (data_e47db0->m_timeScale == 0.0f)
        return;
    elapsed /= data_e47db0->m_timeScale;
    m_elapsed += elapsed;
    for (int i = 0; i < 4; i++)
        m_entries[i].Process(elapsed);
}

// 0x6b2740
void CTutorGuide::HandleMsg(const MsgObject& msg)
{
    switch (msg.m_msg) {
    case 0x1ce:
        OnMsg1CE();
        return;
    case 0x97:
        OnMsg97();
        return;
    case 0x30f:
        if (!IsBusy(0.0f)) {
            TutorGuidePos pos = *reinterpret_cast<const TutorGuidePos*>(msg.m_param1);
            WSendPacket packet((enumClientPacket)0x12e);
            packet.EncodeBuffer(&pos.x, 4);
            packet.EncodeBuffer(&pos.y, 4);
            packet.EncodeBuffer(&pos.z, 4);
            packet.Send((eSendTo)0);
            m_elapsed = 0.0f;
        }
        return;
    case 0x310: {
        TutorGuidePos pos = *reinterpret_cast<const TutorGuidePos*>(msg.m_param1);
        m_entries[msg.m_param2].SetTarget(pos, msg.m_param2);
        return;
    }
    case 0x311:
        OnMsg311();
        return;
    }
}

// 0x6b29f0
const WRTTI* CTutorGuide::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x6b2b10
void CTutorGuide::Display(void)
{
    for (int i = 0; i < 4; i++)
        m_entries[i].Display();
}
