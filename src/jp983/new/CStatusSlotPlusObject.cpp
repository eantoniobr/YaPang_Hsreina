// Original: unknown, JP-only RTTI class CStatusSlotPlusObject (JP 983 exe)
#include "CStatusSlotPlusObject.h"

// Constructor (no body of its own in the original; the real one taking the
// owner is 0x56b8c0). Defining it here emits the vtable and with it the
// ??_G at 0x56ba00, which calls the out-of-line ~CStatusSlotPlusObject
// (0x56b930) as the original does.
CStatusSlotPlusObject::CStatusSlotPlusObject()
{
}

// 0x56b940
void CStatusSlotPlusObject::Load(const void* source)
{
}

// 0x56b950
void CStatusSlotPlusObject::OnDetach(int owner)
{
}

// 0x56b960
void CStatusSlotPlusObject::OnHide(int arg)
{
}

// 0x56b970
void CStatusSlotPlusObject::OnSelect(int arg)
{
}

// 0x56b980: no code or data reference to it was found.
void UnreferencedEmpty_0056b980(void)
{
}

// 0x56b990
CControlledObject* CStatusSlotPlusObject::Create(CControlledObjectOwner* owner)
{
    return new CStatusSlotPlusObject(owner);
}
