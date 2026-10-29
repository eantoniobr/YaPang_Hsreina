// Original: unknown, JP-only RTTI class CAIPlayer (JP 983 exe)
#ifndef PG_JP983_NEW_CAIPLAYER_H
#define PG_JP983_NEW_CAIPLAYER_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/actor.h"

class WRTTI;

// JP-only actor (RTTI name CAIPlayer), vtable at 0xcfe584, IActor's 15
// slots. Slots 5, 7, 9, 10, 12 and 13 hold IActor's own bodies (the same
// VAs as IActor's vtable 0xd41ab4); the split assigned those shared bodies
// to this unit, so they are written here as overrides with IActor's code.
// The layout is known only as far as the bodies read it.
class CAIPlayer : public IActor
{
    LAYOUT_CHECK_FRIEND;
public:
    static const WRTTI m_RTTI;                                // 0xe73dc8

    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x4750c0)
    virtual ~CAIPlayer(void);                                 // 1 (0x4752c0)
    virtual void OnPreLoadInit(void);                         // 2 (0x46ebe0)
    virtual void OnLoad(void);                                // 3 (0x471980)
    virtual void OnInit(void);                                // 4 (0x46f7e0)
    virtual void OnReload(void);                              // 5 (0x4750d0, empty)
    virtual void OnProcess(float elapsed);                    // 6 (0x4719a0)
    virtual void OnDisplay(void);                             // 7 (0x4750e0, empty)
    virtual void OnDestroy(void);                             // 8 (0x46ec10)
    virtual void OnPreserveBack(const char* name);            // 9 (0x4750f0, empty)
    virtual void OnRestorePreserved(void);                    // 10 (0x475100, empty)

    // 0x46da20: calls slot 2 of m_controller when it is set.
    void CallController();

protected:
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x475560)
    virtual void StoreDelayedMsg(const MsgObject& msg) const; // 12 (0xa46310, empty)
    virtual eDispPriority GetDisplayPriority(void);           // 13 (0x475110)

private:
    PADDING(0x18, 0x58);
    void* m_controller;                                       // 0x58
};

BEGIN_LAYOUT_CHECK(CAIPlayer)
    CHECK_FIELD(CAIPlayer, m_controller, 0x58);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_CAIPLAYER_H
