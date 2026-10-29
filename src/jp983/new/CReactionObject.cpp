// Original: unknown, JP-only RTTI class CReactionObject (JP 983 exe)
#include "CReactionObject.h"

// Constructor (VA unknown; not in this unit). Defining it here emits the
// vtable and with it the ??_G at 0x5f0870, which calls the out-of-line
// ~CReactionObject (0x5f0230) as the original does.
CReactionObject::CReactionObject()
{
}

// 0x5f0200
void CReactionObject::Start()
{
}

// 0x5f0210
void CReactionObject::Stop()
{
}

// 0x5f0260
void CReactionObject::SetTarget(void* target)
{
    m_target = target;
    if (target) {
        m_scale = 0.8f;
        m_finished = false;
        Start();
    }
}
