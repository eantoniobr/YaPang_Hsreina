// Original: unknown, JP-only RTTI class CAutoMiracleSignController (JP 983 exe)
#include "CAutoMiracleSignController.h"

// Constructor (VA unknown). Defining it here emits the vtable and with it
// the ??_G at 0x47dc00, which calls the out-of-line destructor (0x47db40)
// as the original does; the real constructor and destructor are elsewhere.
CAutoMiracleSignController::CAutoMiracleSignController(void)
{
}

// 0x47db30
const WRTTI* CAutoMiracleSignController::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x47de80
bool CAutoMiracleSignController::CheckPlayer(unsigned char playerIndex)
{
    return CanShowForPlayer(playerIndex);
}

// 0x4b4f90
bool CAutoMiracleSignController::Reset(void)
{
    m_state = 0;
    return true;
}

// 0x4b4fa0
bool CAutoMiracleSignController::IsReady(void)
{
    return true;
}

// 0x4b4fb0
bool CAutoMiracleSignController::CheckEnabled4(void)
{
    return m_enabled;
}

// 0x4b4fc0
bool CAutoMiracleSignController::CheckEnabled5(void)
{
    return m_enabled;
}

// 0x4b4fd0
bool CAutoMiracleSignController::CheckEnabled6(int arg)
{
    return m_enabled;
}

// 0x4b4ff0
bool CAutoMiracleSignController::CheckEnabled8(void)
{
    return m_enabled;
}

// 0x4b5000
bool CAutoMiracleSignController::CheckEnabled9(void)
{
    return m_enabled;
}

// 0x4b5010
bool CAutoMiracleSignController::CheckEnabled10(int arg)
{
    return m_enabled;
}

// 0x4b5020
bool CAutoMiracleSignController::CheckEnabled11(void)
{
    return m_enabled;
}

// 0x4b5030
bool CAutoMiracleSignController::CheckEnabled12(void)
{
    return m_enabled;
}

// 0x4b5040
bool CAutoMiracleSignController::CheckEnabled13(void)
{
    return m_enabled;
}
