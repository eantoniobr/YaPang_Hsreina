// Original: unknown, JP-only RTTI class CGhostStateUnit (JP 983 exe)
#include "CGhostStateUnit.h"

// Not at a known VA: the real constructor is inlined into the states'
// constructors (GhostPlayer); defined here so the vtable and the scalar
// deleting destructor are emitted.
CGhostStateUnit::CGhostStateUnit(void)
    : m_elapsed(0.0f), m_timer(2.0f), m_timeLimit(2.0f), m_done(false)
{
}

// 0x829500
void CGhostStateUnit::OnRender(void)
{
}

// 0x829590
bool CGhostStateUnit::OnFinished(void)
{
    return m_timer <= 0.0f;
}
