// Original: unknown, JP-only RTTI class CAutoMiracleSignObject (JP 983 exe)
#ifndef PG_JP983_NEW_CAUTOMIRACLESIGNOBJECT_H
#define PG_JP983_NEW_CAUTOMIRACLESIGNOBJECT_H

#include "defines.h"

#include "CControlledObject.h"

// JP-only class (RTTI name CAutoMiracleSignObject : CControlledObject),
// vtable at 0xcfeaf0. Slots 2-11 hold CControlledObject's own bodies (the
// same VAs as its vtable 0xd022d8); the split assigned those shared bodies
// to this unit, so they are written here as overrides with
// CControlledObject's code. The layout is known only as far as the bodies
// read it.
class CAutoMiracleSignObject : public CControlledObject
{
public:
    CAutoMiracleSignObject(void);
    virtual ~CAutoMiracleSignObject(void);                    // 0 (??_G 0x47e090; ~ 0x47df00, not split)
    virtual void Load(const void* source);                    // 1 (0x47df10)
    virtual void OnAttach(int owner);                         // 2 (0x4b0e50, empty)
    virtual void OnDetach(int owner);                         // 3 (0x4b0e60, empty)
    virtual void Update(int context);                         // 4 (0x4b3300)
    virtual void OnReset(void);                               // 5 (0x4b0e70, empty)
    virtual void OnShow(int arg);                             // 6 (0x4b0e80, empty)
    virtual void OnHide(int arg);                             // 7 (0x4b0e90, empty)
    virtual void OnEnter(int arg);                            // 8 (0x4b0ea0, empty)
    virtual void OnLeave(int arg);                            // 9 (0x4b0eb0, empty)
    virtual void OnSelect(int arg);                           // 10 (0x4b0ec0, empty)
    virtual bool IsActive(void) const;                        // 11 (0x4b0ed0)
};

#endif // PG_JP983_NEW_CAUTOMIRACLESIGNOBJECT_H
