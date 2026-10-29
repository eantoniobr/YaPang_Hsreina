// Original: client/ProjectG/particle.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_PARTICLE_H
#define PG_JP983_CLIENT_PROJECTG_PARTICLE_H

#include <memory>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/actor.h"
#include "jp983/client/ProjectG/scenemanager.h"
#include "jp983/client/Wangreal/include/wlist.h"
#include "jp983/client/Wangreal/include/wmath.h"

class WRTTI;
class CBgEffect;
class CLightColumn;
class FxInterpreter;

// Particle emitter loaded from a particle definition file. Declared only as
// far as the JP bodies need it; the KR offsets hold (m_active 0x50, the
// sprite 0x5c and the fragments 0x54 read by Destroy at 0x775e20).
class CParticleRecv
{
    LAYOUT_CHECK_FRIEND;
public:
    ~CParticleRecv(void);

    void Process(float elapsed);                              // 0x777f40
    void Display(void);                                       // 0x775e80
    // particle.h:124
    bool IsActive(void) { return m_active; }
    static void Disconnect(void);                             // 0x775fd0
    // KR: inline at particle.h:126; the JP code calls it out of line.
    void SetCenter(const WVector& center);                    // 0x776780

protected:
    void Destroy(void);                                       // 0x775e20

    PADDING(0x00, 0x50);
    bool m_active;                                            // 0x50
    PADDING(0x51, 0xfc);
    WVector m_center;                                         // 0xfc
};

BEGIN_LAYOUT_CHECK(CParticleRecv)
    CHECK_FIELD(CParticleRecv, m_active, 0x50);
    CHECK_FIELD(CParticleRecv, m_center, 0xfc);
END_LAYOUT_CHECK

// Owner of the particle textures and of the live particles of an effect;
// only the members the JP bodies call are declared.
class CParticleManager
{
public:
    ~CParticleManager(void);                                  // 0x777df0

    void Process(float elapsed);                              // 0x775c90
    void Display(void);                                       // 0x775d10
    void DisplayShadow(void);                                 // 0x775d40
};

// Actor that plays the particle effects of a scene (RTTI name
// CParticleEffect). Vtables 0xd22e84 (IActor's 15 slots) and 0xd22e74
// (CRenderFuncPtr at 0x18). KR layout: the JP bodies read m_recvList at
// 0x1c and m_pManager at 0x3c.
class CParticleEffect : public IActor, public CRenderFuncPtr
{
    LAYOUT_CHECK_FRIEND;
public:
    static const WRTTI m_RTTI;                                // 0xe7a418

    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x779d20)
    // particle.h:24
    virtual ~CParticleEffect(void) {}                         // 1 (??_G 0x779de0, dtor 0x779d30)
    virtual void OnPreLoadInit(void);                         // 2 (0x778cb0)
    virtual void OnInit(void);                                // 4 (0x778350)
    virtual void OnProcess(float elapsed);                    // 6 (0x778360)
    virtual void OnDestroy(void);                             // 8 (0x778c80)
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x778d70)
    virtual void DisplayShadow(void);                         // CRenderFuncPtr 0 (0x7767c0)
    virtual void Display(void);                               // CRenderFuncPtr 1 (0x777d10)

    // 0x777cd0, no caller found (name invented): reads m_fx's pointer.
    FxInterpreter* GetFxInterpreter(void) const;

protected:
    CParticleEffect(void);

    void Clear(void);                                         // 0x7782e0

    WList<CParticleRecv*> m_recvList;                         // 0x1c
    CParticleManager* m_pManager;                             // 0x3c
    PADDING(0x40, 0x54);                                      // KR: sRecv m_recv
    WList<CBgEffect*> m_bgEffectList;                         // 0x54
    CLightColumn* m_pParticle;                                // 0x74
    std::tr1::shared_ptr<FxInterpreter> m_fx;                 // 0x78, JP only (released by the destructor)
};

BEGIN_LAYOUT_CHECK(CParticleEffect)
    CHECK_FIELD(CParticleEffect, m_recvList, 0x1c);
    CHECK_FIELD(CParticleEffect, m_pManager, 0x3c);
    CHECK_FIELD(CParticleEffect, m_bgEffectList, 0x54);
    CHECK_FIELD(CParticleEffect, m_pParticle, 0x74);
    CHECK_FIELD(CParticleEffect, m_fx, 0x78);
END_LAYOUT_CHECK
CHECK_SIZE(CParticleEffect, 0x80);

#endif // PG_JP983_CLIENT_PROJECTG_PARTICLE_H
