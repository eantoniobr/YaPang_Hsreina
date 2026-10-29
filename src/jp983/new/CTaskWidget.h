// Original: unknown, JP-only RTTI class CTaskWidget (JP 983 exe)
#ifndef PG_JP983_NEW_CTASKWIDGET_H
#define PG_JP983_NEW_CTASKWIDGET_H

#include "defines.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/AnotherHand.h"
#include "client/FreshNext/include/frcmdtarget.h"

class WRTTI;

// The widget a CTaskManager shows while its task loads (RTTI name
// CTaskWidget; bases IObject at 0, CHandOwner at 4, FrCmdTarget at 8).
// Vtables 0xd1694c (9 slots), 0xd16944 (CHandOwner) and 0xd16938
// (FrCmdTarget). Slots 2-8 are not named yet: only their shape is known.
// Slots 7 (0x64f1c0, ret 4) and 8 (0x64f1d0) are empty.
class CTaskWidget : public IObject, public CHandOwner, public FrCmdTarget
{
public:
    static const WRTTI m_RTTI;                                // 0xe78d18

    CTaskWidget(void);
    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x64f700)
    virtual ~CTaskWidget(void);                               // 1 (??_G 0x64f8a0)
    virtual void UnknownSlot2(void);                          // 2 (0x64f3b0)
    virtual void UnknownSlot3(void);                          // 3 (0x64f230)
    virtual void UnknownSlot4(void);                          // 4 (0x64f1a0)
    virtual void UnknownSlot5(void);                          // 5 (0x64f290)
    virtual void UnknownSlot6(void);                          // 6 (0x64f1e0)
    virtual void UnknownSlot7(int arg);                       // 7 (0x64f1c0, empty)
    virtual void UnknownSlot8(void);                          // 8 (0x64f1d0, empty)

    virtual void OnAnotherHand(int nWork, void* pData);       // CHandOwner 0 (0x64f5d0)
};

#endif // PG_JP983_NEW_CTASKWIDGET_H
