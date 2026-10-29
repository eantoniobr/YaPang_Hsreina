// Original: d:\build\custom\temp\code\client\projectg\privatetrade.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_PRIVATETRADE_H
#define PG_JP983_CLIENT_PROJECTG_PRIVATETRADE_H

#include "defines.h"

#include "jp983/client/ProjectG/actor.h"

class CPrivateTradeImpl;
class WRTTI;

// The private-trade actor (RTTI name CPrivateTrade), vtable 0xd22ed4, size
// 0x1c (the `new` of the JP CPrivateTradeMakeInstance): an IActor whose work
// is done by a CPrivateTradeImpl it owns. Slots 2, 9, 10, 12-14 keep IActor's
// bodies.
class CPrivateTrade : public IActor
{
    LAYOUT_CHECK_FRIEND;
public:
    static const WRTTI m_RTTI;                                // 0xe7a424

    CPrivateTrade(void);                                      // 0x77aad0
    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x77a800)
    virtual ~CPrivateTrade(void);                             // 1 (??_G 0x77a880, dtor 0x77a790)

    virtual void OnLoad(void);                                // 3 (0x77a810)
    virtual void OnInit(void);                                // 4 (0x77a820)
    virtual void OnReload(void);                              // 5 (0x77a840)
    virtual void OnProcess(float elapsed);                    // 6 (0x77a850)
    virtual void OnDisplay(void);                             // 7 (0x77a860)
    virtual void OnDestroy(void);                             // 8 (0x77a870)

protected:
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x77b1b0)

private:
    CPrivateTradeImpl* m_impl;                                // 0x18
};

CHECK_SIZE(CPrivateTrade, 0x1c);
BEGIN_LAYOUT_CHECK(CPrivateTrade)
    CHECK_FIELD(CPrivateTrade, m_impl, 0x18);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_PRIVATETRADE_H
