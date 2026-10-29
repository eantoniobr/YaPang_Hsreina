// Original: unknown, JP-only RTTI class CSubGolfRuleBase (JP 983 exe)
#include "CSubGolfRuleBase.h"

// The real constructor and destructor (0x64f910, stores the vtable) live
// elsewhere; this empty constructor makes the TU emit the vtable and the
// scalar deleting destructor at 0x64f9e0.
CSubGolfRuleBase::CSubGolfRuleBase(void)
{
}

// 0x64f920
void CSubGolfRuleBase::OnStart(void)
{
}

// 0x64f930
void CSubGolfRuleBase::OnEvent(int value)
{
}

// 0x64f940
void CSubGolfRuleBase::OnUpdate(void)
{
}

// 0x64f950
void CSubGolfRuleBase::OnEnd(void)
{
}
