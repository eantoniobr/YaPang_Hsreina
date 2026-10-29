// Original: unknown, JP-only RTTI class LobbyItems (JP 983 exe)
#ifndef PG_JP983_NEW_LOBBYITEMS_H
#define PG_JP983_NEW_LOBBYITEMS_H

#include <functional>
#include <memory>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/actor.h"
#include "jp983/client/ProjectG/AnotherHand.h"

class WRTTI;

// One of the two objects LobbyItems shows (class name unknown). It holds a
// std::string at 0x10 (its name); only the per-frame slots are known, from
// LobbyItems::OnProcess (slot 15, takes the elapsed time) and OnDisplay.
class LobbyItemObject
{
public:
    virtual void UnknownSlot0();                              // 0
    virtual void UnknownSlot1();                              // 1
    virtual void UnknownSlot2();                              // 2
    virtual void UnknownSlot3();                              // 3
    virtual void UnknownSlot4();                              // 4
    virtual void UnknownSlot5();                              // 5
    virtual void UnknownSlot6();                              // 6
    virtual void UnknownSlot7();                              // 7
    virtual void UnknownSlot8();                              // 8
    virtual void UnknownSlot9();                              // 9
    virtual void UnknownSlot10();                             // 10
    virtual void UnknownSlot11();                             // 11
    virtual void UnknownSlot12();                             // 12
    virtual void UnknownSlot13();                             // 13
    virtual void UnknownSlot14();                             // 14
    virtual void Process(float elapsed);                      // 15
    virtual void Display();                                   // 16
};

// JP-only actor (RTTI name LobbyItems), vtables 0xd0a4ac (IActor, 15 slots)
// and 0xd0a4a4 (CHandOwner at 0x18). Shows two lobby item objects and loads
// them on a CAnotherHand worker thread (0x90).
class LobbyItems : public IActor, public CHandOwner
{
    LAYOUT_CHECK_FRIEND;
public:
    static const WRTTI m_RTTI;                                // 0xe75198

    LobbyItems(void);
    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x562ee0)
    virtual ~LobbyItems(void);                                // 1 (??_G 0x5635a0; ~ 0x562df0, not split)
    virtual void OnPreLoadInit(void);                         // 2 (0x563750)
    virtual void OnLoad(void);                                // 3 (0x561b80, empty)
    virtual void OnProcess(float elapsed);                    // 6 (0x562ef0)
    virtual void OnDisplay(void);                             // 7 (0x5621f0)
    virtual void OnDestroy(void);                             // 8 (0x5635d0)

    // CHandOwner slot 0 (0x561f10): the worker thread's job.
    virtual void OnAnotherHand(int nWork, void* pData);

protected:
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x5637c0)

private:
    // 0x18: CHandOwner
    std::tr1::shared_ptr<LobbyItemObject> m_items[2];         // 0x1c
    PADDING(0x2c, 0x68);
    std::tr1::function<void ()> m_loadJob;                    // 0x68, run by OnAnotherHand
    bool m_loadDone;                                          // 0x80
    PADDING(0x81, 0x90);
};

BEGIN_LAYOUT_CHECK(LobbyItems)
    CHECK_FIELD(LobbyItems, m_items, 0x1c);
    CHECK_FIELD(LobbyItems, m_loadJob, 0x68);
    CHECK_FIELD(LobbyItems, m_loadDone, 0x80);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_LOBBYITEMS_H
