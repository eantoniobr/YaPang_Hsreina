// Original: d:\build\custom\temp\code\client\projectg\privatetrade.cpp (JP 983 exe)
#include "jp983/client/ProjectG/PrivateTrade.h"

#include <string>

#include "client/FreshNext/include/frcmdtarget.h"
#include "jp983/client/ProjectG/ObjectFactory.h"

class FrPrivateTrade;
class FrFormBar;

enum _ePrivateTradeState {
    _ePrivateTradeState_None = 0,
    _ePrivateTradeState_Wait = 2,    // a request or accept wait bar is open
    _ePrivateTradeState_Accepted = 6 // the trade window closed with OK
};

// The private-trade state machine owned by CPrivateTrade (RTTI name
// CPrivateTradeImpl), vtable 0xd22f14, size 0x34 (the `new` of
// CPrivateTrade's constructor). Same layout as KR.
class CPrivateTradeImpl : public FrCmdTarget
{
    LAYOUT_CHECK_FRIEND;
    friend class CPrivateTrade;
private:
    CPrivateTradeImpl(void);                                  // 0x77aa50
    virtual ~CPrivateTradeImpl(void);                         // 0 (??_G 0x77ab50, dtor 0x77aa90)
    void SetTraderNick(const std::string& nick);              // 0x77ad00
    void SetState(_ePrivateTradeState state) { m_state = state; }
    void Reset(void);                                         // 0x77ac20
    void Init(void);                                          // 0x77a720
    void CloseWnd(void);                                      // 0x77a750

    _ePrivateTradeState m_state;     // 0x4
    float m_elapsed;                 // 0x8, 1.0f in the constructor
    FrPrivateTrade* m_tradeForm;     // 0xc, closed by CloseWnd
    FrFormBar* m_waitForm;           // 0x10, closed by CloseWnd
    unsigned long m_traderGuid;      // 0x14
    std::string m_traderNick;        // 0x18
};

CHECK_SIZE(CPrivateTradeImpl, 0x34);
BEGIN_LAYOUT_CHECK(CPrivateTradeImpl)
    CHECK_FIELD(CPrivateTradeImpl, m_state, 0x4);
    CHECK_FIELD(CPrivateTradeImpl, m_elapsed, 0x8);
    CHECK_FIELD(CPrivateTradeImpl, m_tradeForm, 0xc);
    CHECK_FIELD(CPrivateTradeImpl, m_waitForm, 0x10);
    CHECK_FIELD(CPrivateTradeImpl, m_traderGuid, 0x14);
    CHECK_FIELD(CPrivateTradeImpl, m_traderNick, 0x18);
END_LAYOUT_CHECK

// 0x77a800
const WRTTI* CPrivateTrade::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x77a810
void CPrivateTrade::OnLoad(void)
{
}

// 0x77a820
void CPrivateTrade::OnInit(void)
{
    m_impl->SetState(_ePrivateTradeState_None);
    m_impl->Init();
}

// 0x77a840
void CPrivateTrade::OnReload(void)
{
    m_impl->SetState(_ePrivateTradeState_None);
}

// 0x77a850
void CPrivateTrade::OnProcess(float elapsed)
{
}

// 0x77a860
void CPrivateTrade::OnDisplay(void)
{
}

// 0x77a870
void CPrivateTrade::OnDestroy(void)
{
    m_impl->CloseWnd();
}

// 0x77aa50
CPrivateTradeImpl::CPrivateTradeImpl(void)
    : m_state(_ePrivateTradeState_None), m_elapsed(1.0f), m_tradeForm(NULL), m_waitForm(NULL), m_traderGuid(0)
{
}

// 0x77aa90
CPrivateTradeImpl::~CPrivateTradeImpl(void)
{
}

// 0x77aad0
CPrivateTrade::CPrivateTrade(void) : m_impl(NULL)
{
    m_impl = new CPrivateTradeImpl;
}

// 0x77ab80
IObject* CPrivateTradeMakeInstance(void)
{
    return new CPrivateTrade;
}

struct __impCPrivateTrade {
    // 0x77abf0
    __impCPrivateTrade(void)
    {
        ObjectFactory().AddObjectFunctor(CPrivateTradeMakeInstance, "CPrivateTrade");
        ActorFactory().AddActorClass("CPrivateTrade");
    }
};
static __impCPrivateTrade s_registerCPrivateTrade;

// 0x77ac20
void CPrivateTradeImpl::Reset(void)
{
    m_tradeForm = NULL;
    m_waitForm = NULL;
    m_state = _ePrivateTradeState_None;
    m_elapsed = 0.0f;
    m_traderGuid = 0;
    m_traderNick = "";
}

// 0x77ad00
void CPrivateTradeImpl::SetTraderNick(const std::string& nick)
{
    m_traderNick = nick;
}
