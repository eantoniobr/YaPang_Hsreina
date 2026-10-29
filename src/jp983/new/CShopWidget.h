// Original: unknown, JP-only RTTI class CShopWidget (JP 983 exe)
#ifndef PG_JP983_NEW_CSHOPWIDGET_H
#define PG_JP983_NEW_CSHOPWIDGET_H

#include "defines.h"

#include "CTaskWidget.h"

class WRTTI;

// JP-only class (RTTI name CShopWidget), vtables 0xd12380 (9 slots),
// 0xd12378 (CHandOwner, at 4) and 0xd1236c (FrCmdTarget, at 8, whose slot 0
// is the compiler's this-adjusting thunk 0x5e0d60 to the ??_G 0x5e0e50).
class CShopWidget : public CTaskWidget
{
public:
    CShopWidget(void);
    static const WRTTI m_RTTI;                                // 0xe78be0

    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x5e0cc0)
    virtual ~CShopWidget(void);                               // 1 (??_G 0x5e0e50; ~ 0x5e0e00, not split)
    virtual void UnknownSlot2(void);                          // 2 (0x5e0fd0)
    virtual void UnknownSlot3(void);                          // 3 (0x5e0e80)
    virtual void UnknownSlot4(void);                          // 4 (0x5e0cd0, empty)
    virtual void UnknownSlot5(void);                          // 5 (0x5e0ce0)
    virtual void UnknownSlot6(void);                          // 6 (0x5e0ff0)
};

#endif // PG_JP983_NEW_CSHOPWIDGET_H
