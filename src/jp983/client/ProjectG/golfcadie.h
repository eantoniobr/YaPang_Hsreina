// Original: client/ProjectG/golfcadie.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_GOLFCADIE_H
#define PG_JP983_CLIENT_PROJECTG_GOLFCADIE_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/actor.h"
#include "wmath.h"
#include "jp983/client/ProjectG/scenemanager.h"

class CPetBody;
class WRTTI;

// The caddie actor (RTTI CGolfCaddie; bases IActor, IObject,
// CRenderFuncPtr), vtable 0xd201a4, CRenderFuncPtr's vtable 0xd20190 at
// +0x18. Only the slots and members this unit's bodies use are declared.
class CGolfCaddie : public IActor, public CRenderFuncPtr
{
    LAYOUT_CHECK_FRIEND;
public:
    // One loaded caddie; only the body pointer is modelled.
    struct sCaddie {
        CPetBody* m_pBody;                                    // 0x0
    };

    static const WRTTI m_RTTI;                                // 0xe79f2c

    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x739c10)
    virtual void OnPreLoadInit(void);                         // 2 (0x731e20)

    virtual void DisplayShadow(void);                         // CRenderFuncPtr 0 (0x732ca0)
    virtual void Display(void);                               // CRenderFuncPtr 1 (0x732c60)

protected:
    void ResetTalk(void);                                     // 0x730e40
    void DontLookUp(void);                                    // 0x730f00
    char* GetBehaviorEndToken(char* token, char* src);        // 0x732020
    bool ShouldDisplay(void);                                 // 0x732080

private:
    sCaddie* m_pCaddie;                                       // 0x1c, the caddie in use
    PADDING(0x20, 0x38);
    WVector m_position;                                       // 0x38, where the caddie stands
    PADDING(0x44, 0x59);
    bool m_visible;                                           // 0x59, the caddie is shown
    PADDING(0x5a, 0x7c);
    unsigned char m_bubbleTalkType;                           // 0x7c, talk type shown in the bubble
    bool m_talked[36];                                        // 0x7d, per talk type: already said
    bool m_talkFlag;                                          // 0xa1, cleared with the talk state
    unsigned long m_talkResetTime;                            // 0xa4, g_CurrentTime of the last ResetTalk
};

BEGIN_LAYOUT_CHECK(CGolfCaddie)
    CHECK_FIELD(CGolfCaddie, m_pCaddie, 0x1c);
    CHECK_FIELD(CGolfCaddie, m_position, 0x38);
    CHECK_FIELD(CGolfCaddie, m_visible, 0x59);
    CHECK_FIELD(CGolfCaddie, m_bubbleTalkType, 0x7c);
    CHECK_FIELD(CGolfCaddie, m_talked, 0x7d);
    CHECK_FIELD(CGolfCaddie, m_talkFlag, 0xa1);
    CHECK_FIELD(CGolfCaddie, m_talkResetTime, 0xa4);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_GOLFCADIE_H
