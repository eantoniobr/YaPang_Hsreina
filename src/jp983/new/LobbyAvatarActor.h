// Original: unknown, JP-only RTTI class LobbyAvatarActor (JP 983 exe)
#ifndef PG_JP983_NEW_LOBBYAVATARACTOR_H
#define PG_JP983_NEW_LOBBYAVATARACTOR_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/actor.h"
#include "jp983/client/ProjectG/AnotherHand.h"

class WRTTI;

// Unnamed object behind the global pointer at 0xe74d14; 0x4ddbe0 returns
// the text of an id (the empty string when it has none).
class LobbyTextSource
{
public:
    const char* GetText(int id);                      // 0x4ddbe0
};

// JP-only actor (RTTI name LobbyAvatarActor; bases IActor, IObject,
// CHandOwner), vtables 0xd0b524 (IActor, 15 slots) and 0xd0b51c
// (CHandOwner at 0x18). Slots 5, 9, 10, 12, 13 and 14 are IActor's. The
// layout is known only as far as the bodies read it.
class LobbyAvatarActor : public IActor, public CHandOwner
{
    LAYOUT_CHECK_FRIEND;
public:
    static const WRTTI m_RTTI;                                // 0xe75ca4

    LobbyAvatarActor(void);
    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x590ef0)
    virtual ~LobbyAvatarActor(void);                          // 1 (??_G 0x591a00; ~ 0x590da0, not split)
    virtual void OnPreLoadInit(void);                         // 2 (0x58d120)
    virtual void OnLoad(void);                                // 3 (0x58c3f0, empty)
    virtual void OnInit(void);                                // 4 (0x58c400, empty)
    virtual void OnProcess(float elapsed);                    // 6 (0x5928e0)
    virtual void OnDisplay(void);                             // 7 (0x58e610)
    virtual void OnDestroy(void);                             // 8 (0x592610)

    // CHandOwner slot 0 (0x592f50).
    virtual void OnAnotherHand(int nWork, void* pData);

    // 0x58c410: loads the named overlay through the resource manager.
    void LoadOverlay(const char* name);
    // 0x592030: releases the overlays the actor holds (from 0x1c).
    void ReleaseOverlays();

protected:
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x592620)

private:
    // 0x18: CHandOwner
    PADDING(0x1c, 0x254);
    bool m_attached;                                          // 0x254
};

BEGIN_LAYOUT_CHECK(LobbyAvatarActor)
    CHECK_FIELD(LobbyAvatarActor, m_attached, 0x254);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_LOBBYAVATARACTOR_H
