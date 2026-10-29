// Original: unknown, JP-only RTTI class CAutoMiracleSignObject (JP 983 exe)
#include "CAutoMiracleSignObject.h"

// Constructor (VA unknown; the JP vtable 0xcfeaf0 store was not found).
// Defining it here emits the vtable and with it the ??_G at 0x47e090, which
// then calls the out-of-line ~CAutoMiracleSignObject (0x47df00) as the original does.
CAutoMiracleSignObject::CAutoMiracleSignObject()
{
}

// 0x4b0e50
void CAutoMiracleSignObject::OnAttach(int owner)
{
}

// 0x4b0e60
void CAutoMiracleSignObject::OnDetach(int owner)
{
}

// 0x4b0e70
void CAutoMiracleSignObject::OnReset()
{
}

// 0x4b0e80
void CAutoMiracleSignObject::OnShow(int arg)
{
}

// 0x4b0e90
void CAutoMiracleSignObject::OnHide(int arg)
{
}

// 0x4b0ea0
void CAutoMiracleSignObject::OnEnter(int arg)
{
}

// 0x4b0eb0
void CAutoMiracleSignObject::OnLeave(int arg)
{
}

// 0x4b0ec0
void CAutoMiracleSignObject::OnSelect(int arg)
{
}

// 0x4b0ed0
bool CAutoMiracleSignObject::IsActive() const
{
    return true;
}
