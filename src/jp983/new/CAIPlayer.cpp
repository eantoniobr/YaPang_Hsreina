// Original: unknown, JP-only RTTI class CAIPlayer (JP 983 exe)
#include "CAIPlayer.h"

// 0x46ec10
void CAIPlayer::OnDestroy(void)
{
    CallController();
}

// 0x4750c0
const WRTTI* CAIPlayer::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x4750d0
void CAIPlayer::OnReload(void)
{
}

// 0x4750e0
void CAIPlayer::OnDisplay(void)
{
}

// 0x4750f0
void CAIPlayer::OnPreserveBack(const char* name)
{
}

// 0x475100
void CAIPlayer::OnRestorePreserved(void)
{
}

// 0x475110
IActor::eDispPriority CAIPlayer::GetDisplayPriority(void)
{
    return (eDispPriority)m_priority;
}

// 0xa46310
void CAIPlayer::StoreDelayedMsg(const MsgObject& msg) const
{
}
