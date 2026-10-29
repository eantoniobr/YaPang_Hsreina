// Original: client/ProjectG/particle.cpp (JP 983 exe)
#include "particle.h"

// The real constructor is elsewhere; this empty one makes the compiler emit
// the vtables (and the ??_G) here.
CParticleEffect::CParticleEffect(void)
{
}

// 0x776780
void CParticleRecv::SetCenter(const WVector& center)
{
    m_center = center;
}

// 0x7767c0
void CParticleEffect::DisplayShadow(void)
{
    if (m_pManager) {
        m_pManager->DisplayShadow();
    }
}

// 0x776880, no reference found: returns its argument.
void* UnreferencedReturnThis_00776880(void* p)
{
    return p;
}

// 0x776890
CParticleRecv::~CParticleRecv(void)
{
    Destroy();
}

// 0x7773a0, no reference found: returns its argument.
void* UnreferencedReturnThis_007773a0(void* p)
{
    return p;
}

// 0x777cd0
FxInterpreter* CParticleEffect::GetFxInterpreter(void) const
{
    return m_fx.get();
}

// 0x777d10
void CParticleEffect::Display(void)
{
    for (CParticleRecv* recv = m_recvList.Start(); recv != NULL; recv = m_recvList.Next()) {
        if (recv->IsActive()) {
            recv->Display();
        }
    }

    m_pManager->Display();
}

// 0x7782e0
void CParticleEffect::Clear(void)
{
    CParticleRecv::Disconnect();

    for (CParticleRecv* recv = m_recvList.Start(); recv != NULL; recv = m_recvList.Next()) {
        delete recv;
    }
    m_recvList.Reset();
}

// 0x778350
void CParticleEffect::OnInit(void)
{
    Clear();
}

// 0x778360
void CParticleEffect::OnProcess(float elapsed)
{
    for (CParticleRecv* recv = m_recvList.Start(); recv != NULL; recv = m_recvList.Next()) {
        if (recv->IsActive()) {
            recv->Process(elapsed);
        }
    }

    m_pManager->Process(elapsed);
}

// 0x778c80
void CParticleEffect::OnDestroy(void)
{
    if (m_pManager) {
        delete m_pManager;
        m_pManager = NULL;
    }

    Clear();
}

// 0x779d20
const WRTTI* CParticleEffect::GetRTTI(void) const
{
    return &m_RTTI;
}
