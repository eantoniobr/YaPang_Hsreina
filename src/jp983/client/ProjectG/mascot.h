// Original: d:\build\custom\temp\code\client\projectg\mascot.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_MASCOT_H
#define PG_JP983_CLIENT_PROJECTG_MASCOT_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/actor.h"
#include "jp983/client/ProjectG/scenemanager.h"
#include "jp983/client/ProjectG/npc.h"

class IObject;
class WPuppet;
class WRTTI;

namespace IFF_STRUCT {
struct sMascot;
}

struct sMascotInfo;

IObject* CMascotMakeInstance(void);

// The 0x1e0-byte object CMascot's constructor makes (vtable 0xd34928; class
// name unknown). Only its constructor is declared.
class CMascotMsgObject
{
public:
    CMascotMsgObject(int a, int b);                           // 0x88e520
    virtual ~CMascotMsgObject(void);
};

// The bird carrying a player's mascot (RTTI name CCameraBird, vtable
// 0xd223e8: Display 0x7629b0, ??_G 0x763330, Process 0x762930, CheckTarget
// 0x762300). The destructor is implicit (0x763320: no vtable store before
// the base destructor, as cl emits for an implicit one). Only the members the functions decompiled so far use are
// declared.
class CCameraBird : public CCreature
{
    LAYOUT_CHECK_FRIEND;
public:
    CCameraBird(const char* name, unsigned char playerIndex); // 0x7632b0

    virtual void Display(void);                               // 1 (0x7629b0)
    virtual void Process(float dt);                           // 4 (0x762930)
    virtual void CheckTarget(float dt);                       // 8 (0x762300)

    void ChangePet(const char* name);                         // 0x762140

protected:
    unsigned char m_playerIndex;    // 0x120, the player the bird follows
    PADDING(0x121, 0x124);
};

BEGIN_LAYOUT_CHECK(CCameraBird)
    CHECK_FIELD(CCameraBird, m_playerIndex, 0x120);
END_LAYOUT_CHECK

// The mascots following the players of a round (RTTI name CMascot; IActor at
// 0x0 with vtable 0xd22264, CRenderFuncPtr at 0x18 with vtable 0xd22250).
// Size 0x84 (the `new` of the factory function 0x762230). Only the members
// the functions decompiled so far use are declared.
class CMascot : public IActor, public CRenderFuncPtr
{
    LAYOUT_CHECK_FRIEND;
    friend IObject* CMascotMakeInstance(void);

// The 0x1e0-byte object CMascot's constructor makes (vtable 0xd34928; class
// name unknown). Only its constructor is declared.
class CMascotMsgObject
{
public:
    CMascotMsgObject(int a, int b);                           // 0x88e520
    virtual ~CMascotMsgObject(void);
};
public:
    static const WRTTI m_RTTI;                                // 0xe79ff8

protected:
    CMascot(void);                                            // 0x761cd0
public:
    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x761d90)
    virtual ~CMascot(void);                                   // 1 (0x761da0, ??_G 0x7622d0)
    virtual void OnPreLoadInit(void);                         // 2 (0x761e20)
    virtual void OnLoad(void);                                // 3 (0x763360)
    virtual void OnInit(void);                                // 4 (0x761bc0)
    virtual void OnReload(void);                              // 5 (0x761bb0)
    virtual void OnProcess(float dt);                         // 6 (0x7628d0)
    virtual void OnDestroy(void);                             // 8 (0x761b70)
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x762f60)

    // CRenderFuncPtr slot 1 (0x761bd0).
    virtual void Display(void);

    static int ChangeMascotMsgInTex(const char* msg, const IFF_STRUCT::sMascot* pMascot, WPuppet* pPet, const char* suffix); // 0x761e70

protected:
    // One player's mascot, 0x18 bytes.
    struct sMascot {
        sMascot(void) : m_pBird(0), m_pIffMascot(0), m_pPlayer(0) {}

        CCreature* m_pBird;                       // 0x00, a CCameraBird
        UNKNOWN(0x4, 0x10);
        const IFF_STRUCT::sMascot* m_pIffMascot;  // 0x10
        const sMascotInfo* m_pPlayer;             // 0x14
    };

    sMascot m_mascots[4];       // 0x1c
    // JP only: a 0x1e0-byte object made by the constructor (its constructor
    // 0x88e520 takes (0, 0)); OnDestroy calls its 0x88c420 with -1, the
    // destructor deletes it through its first virtual slot.
    CMascotMsgObject* m_pMsgObject; // 0x7c
    int m_unk80;                // 0x80, set to -1 by OnDestroy (KR m_unk7C)
};

CHECK_SIZE(CMascot, 0x84);
BEGIN_LAYOUT_CHECK(CMascot)
    CHECK_SIZE(CMascot::sMascot, 0x18);
    CHECK_FIELD(CMascot::sMascot, m_pIffMascot, 0x10);
    CHECK_FIELD(CMascot::sMascot, m_pPlayer, 0x14);
    CHECK_FIELD(CMascot, m_mascots, 0x1c);
    CHECK_FIELD(CMascot, m_pMsgObject, 0x7c);
    CHECK_FIELD(CMascot, m_unk80, 0x80);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_MASCOT_H
