// Original: unknown, JP-only RTTI class CControlledObject (JP 983 exe)
#ifndef PG_JP983_NEW_CCONTROLLEDOBJECT_H
#define PG_JP983_NEW_CCONTROLLEDOBJECT_H

#include "defines.h"

// Base of the JP sign and effect objects (RTTI name CControlledObject, no
// base class), vtable 0xd022d8, 12 slots; about 36 classes derive from it.
// Slot 1 is pure (_purecall); slots 2-11 hold its own bodies, which the
// derived classes that do not override them share. The slot names are
// descriptive guesses; the layout is not modelled yet.
class CControlledObject
{
public:
    CControlledObject(void);
    virtual ~CControlledObject(void);                         // 0 (??_G 0x4b3f30; ~ 0x4b3db0)
    virtual void Load(const void* source) = 0;                // 1 (_purecall)
    virtual void OnAttach(int owner);                         // 2 (0x4b0e50, empty)
    virtual void OnDetach(int owner);                         // 3 (0x4b0e60, empty)
    virtual void Update(int context);                         // 4 (0x4b3300)
    virtual void OnReset(void);                               // 5 (0x4b0e70, empty)
    virtual void OnShow(int arg);                             // 6 (0x4b0e80, empty)
    virtual void OnHide(int arg);                             // 7 (0x4b0e90, empty)
    virtual void OnEnter(int arg);                            // 8 (0x4b0ea0, empty)
    virtual void OnLeave(int arg);                            // 9 (0x4b0eb0, empty)
    virtual void OnSelect(int arg);                           // 10 (0x4b0ec0, empty)
    virtual bool IsActive(void) const;                        // 11 (0x4b0ed0, returns true)
};

#endif // PG_JP983_NEW_CCONTROLLEDOBJECT_H
