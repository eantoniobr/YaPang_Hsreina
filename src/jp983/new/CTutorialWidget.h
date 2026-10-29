// Original: unknown, JP-only RTTI class CTutorialWidget (JP 983 exe)
#ifndef PG_JP983_NEW_CTUTORIALWIDGET_H
#define PG_JP983_NEW_CTUTORIALWIDGET_H

#include "defines.h"

#include "CTaskWidget.h"

class WRTTI;

// JP-only class (RTTI name CTutorialWidget), vtables 0xd19e6c (9 slots),
// 0xd19e64 (CHandOwner, at 4) and 0xd19e58 (FrCmdTarget, at 8, whose slot 0
// is the compiler's this-adjusting thunk 0x6b2c50 to the ??_G 0x6b2d10).
class CTutorialWidget : public CTaskWidget
{
public:
    CTutorialWidget(void);
    static const WRTTI m_RTTI;                                // 0xe78fe8

    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x6b2c10)
    virtual ~CTutorialWidget(void);                           // 1 (??_G 0x6b2d10)
    virtual void UnknownSlot2(void);                          // 2 (0x6b3020)
    virtual void UnknownSlot3(void);                          // 3 (0x6b2d40)
    virtual void UnknownSlot4(void);                          // 4 (0x6b2c20, empty)
    virtual void UnknownSlot5(void);                          // 5 (0x6b2c30)
    virtual void UnknownSlot6(void);                          // 6 (0x6b2ee0)
};

#endif // PG_JP983_NEW_CTUTORIALWIDGET_H
