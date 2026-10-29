// Original: unknown, JP-only RTTI class CMyRoomWidget (JP 983 exe)
#ifndef PG_JP983_NEW_CMYROOMWIDGET_H
#define PG_JP983_NEW_CMYROOMWIDGET_H

#include "defines.h"

#include "CTaskWidget.h"

class WRTTI;

// JP-only class (RTTI name CMyRoomWidget : CTaskWidget), vtables 0xd0ceb8
// (9 slots), 0xd0ceb0 (CHandOwner, +4) and 0xd0cea4 (FrCmdTarget, +8).
// Slots 7 and 8 hold CTaskWidget's own empty bodies (the same VAs as
// CTaskWidget's vtable 0xd1694c); the split assigned them to this unit, so
// they are written here as overrides with CTaskWidget's code.
class CMyRoomWidget : public CTaskWidget
{
public:
    CMyRoomWidget(void);
    static const WRTTI m_RTTI;                                // 0xe76c10

    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x5a7030)
    virtual ~CMyRoomWidget(void);                             // 1 (??_G 0x5a7d10; FrCmdTarget thunk 0x5a73c0)
    virtual void UnknownSlot7(int arg);                       // 7 (0x64f1c0, empty)
    virtual void UnknownSlot8(void);                          // 8 (0x64f1d0, empty)
};

#endif // PG_JP983_NEW_CMYROOMWIDGET_H
