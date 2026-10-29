// Original: d:\build\custom\temp\code\client\projectg\actor.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_ACTOR_H
#define PG_JP983_CLIENT_PROJECTG_ACTOR_H

#include <stddef.h>

#include "defines.h"
#include "padding.h"

#include "ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"

class IActor;
class WRTTI;

// Message passed between actors (KR actor.h, 0x20 bytes): the sender, the
// message id and five generic parameters. A parameter carries either an
// integer or a pointer (handlers cast it back), so it is pointer-sized.
// m_reserved holds the delivery time of a delayed message (compared with
// g_CurrentTime). JP bodies read the KR offsets (ShotTrajectoryForMassGame,
// CTutorGuide).
class MsgObject
{
public:
    const IActor* m_pSender; // 0x00
    int m_msg;               // 0x04
    intptr_t m_param1;       // 0x08
    intptr_t m_param2;       // 0x0c
    intptr_t m_param3;       // 0x10
    intptr_t m_param4;       // 0x14
    intptr_t m_param5;       // 0x18
    int m_reserved;          // 0x1c, delivery time, against g_CurrentTime
};

CHECK_SIZE(MsgObject, 0x20);

// Base of the game's actors (RTTI name IActor), vtable 0xd41ab4, 15 slots in
// KR actor.h's order (GetRTTI and the destructor are IObject's). The JP
// bodies at 0x4750d0 (5), 0x4750e0 (7), 0x4750f0 (9), 0x475100 (10),
// 0xa46310 (12) and 0x475110 (13) are shared by every actor vtable that
// does not override the slot. Size 0x18: a derived class's second base
// (CHandOwner in LobbyItems and LobbyAvatarActor) sits at 0x18.
class IActor : public IObject
{
    LAYOUT_CHECK_FRIEND;
public:
    // Display priority (values not known yet).
    enum eDispPriority {
        DISP_PRIORITY_DEFAULT = 0
    };

    static const WRTTI m_RTTI;                                // 0xf006cc, returned by slot 0

    IActor(void);
    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0xa46380)
    virtual ~IActor(void);                                    // 1 (??_G 0xa46550)
    virtual void OnPreLoadInit(void);                         // 2 (0x4912a0)
    virtual void OnLoad(void);                                // 3 (0x4912b0)
    virtual void OnInit(void);                                // 4 (0x4912c0)
    virtual void OnReload(void);                              // 5 (0x4750d0)
    virtual void OnProcess(float elapsed);                    // 6 (0x4912d0)
    virtual void OnDisplay(void);                             // 7 (0x4750e0)
    virtual void OnDestroy(void);                             // 8 (0x4912e0)
    virtual void OnPreserveBack(const char* name);            // 9 (0x4750f0)
    virtual void OnRestorePreserved(void);                    // 10 (0x475100)

protected:
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0xa462c0)
    virtual void StoreDelayedMsg(const MsgObject& msg) const; // 12 (0xa46310)
    virtual eDispPriority GetDisplayPriority(void);           // 13 (0x475110)
    virtual bool Skipped(void) const;                         // 14 (0xa46320)

    void AddSkipList(unsigned long layer);                    // 0xa46340

    PADDING(0x04, 0x08);
    int m_priority;                                           // 0x08, returned by slot 13
    PADDING(0x0c, 0x18);
};

CHECK_SIZE(IActor, 0x18);
BEGIN_LAYOUT_CHECK(IActor)
    CHECK_FIELD(IActor, m_priority, 0x08);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_ACTOR_H
