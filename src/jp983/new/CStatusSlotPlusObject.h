// Original: unknown, JP-only RTTI class CStatusSlotPlusObject (JP 983 exe)
#ifndef PG_JP983_NEW_CSTATUSSLOTPLUSOBJECT_H
#define PG_JP983_NEW_CSTATUSSLOTPLUSOBJECT_H

#include "defines.h"
#include "padding.h"

#include "CControlledObject.h"

// The object the controlled-object factories receive; CControlledObject's
// constructor (0x4b3d70) keeps it at +0x4c. Not modelled yet.
class CControlledObjectOwner;

// JP-only class (RTTI name CStatusSlotPlusObject : CControlledObject),
// vtable at 0xd0a950, size 0x5c. Slots 2, 4-6, 8, 9 and 11 keep
// CControlledObject's bodies. Its constructor (0x56b8c0, not split) looks
// up the "CStatusSlotPlusController" and clears m_slot (0x50), 0x54 and
// 0x58. The layout is known only as far as the bodies read it.
class CStatusSlotPlusObject : public CControlledObject
{
public:
    CStatusSlotPlusObject();
    explicit CStatusSlotPlusObject(CControlledObjectOwner* owner); // 0x56b8c0, not split
    virtual ~CStatusSlotPlusObject();                         // 0 (??_G 0x56ba00; ~ 0x56b930, not split)
    virtual void Load(const void* source);                    // 1 (0x56b940, empty)
    virtual void OnDetach(int owner);                         // 3 (0x56b950, empty)
    virtual void OnHide(int arg);                             // 7 (0x56b960, empty)
    virtual void OnSelect(int arg);                           // 10 (0x56b970, empty)

    // 0x56b990: the factory registered (type 0x21) by 0x56ba30.
    static CControlledObject* Create(CControlledObjectOwner* owner);

private:
    PADDING(0x04, 0x5c);

    LAYOUT_CHECK_FRIEND;
};

BEGIN_LAYOUT_CHECK(CStatusSlotPlusObject)
    CHECK_SIZE(CStatusSlotPlusObject, 0x5c);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_CSTATUSSLOTPLUSOBJECT_H
