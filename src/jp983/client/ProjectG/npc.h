// Original: d:\build\custom\temp\code\client\projectg\npc.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_NPC_H
#define PG_JP983_CLIENT_PROJECTG_NPC_H

#include "defines.h"
#include "padding.h"

#include <vector>

#include "jp983/client/ProjectG/scenemanager.h"
#include "jp983/client/Wangreal/include/wmath.h"

class WPuppet;

// A scripted puppet moving in the scene (birds, mascots; KR npc.h). JP
// vtable 0xd223b4: CRenderFuncPtr's three slots (Display 0x766b80), the
// destructor (??_G 0x762f30), Process (0x76af10), SetArea (0x773090,
// 0x763d90), PlayEvent (0x766cf0) and CheckTarget (0x76cd10). cl gives
// overloaded virtuals slots in reverse declaration order, so the Waabb
// SetArea is declared first. Only the members the JP units built so far use
// are declared; the derived CCameraBird's first member is at 0x120.
class CCreature : public CRenderFuncPtr
{
    LAYOUT_CHECK_FRIEND;
public:
    virtual void Display(void);                               // 1 (0x766b80)
    virtual ~CCreature(void);                                 // 3 (0x76cb00, ??_G 0x762f30)
    virtual void Process(float dt);                           // 4 (0x76af10)
    virtual void SetArea(const Waabb& area, unsigned long flags);                                  // 5
    virtual void SetArea(const std::vector<WVector>& points, float radius, unsigned long flags);   // 6
    virtual void PlayEvent(void);                             // 7 (0x766cf0)
    virtual void CheckTarget(float dt);                       // 8 (0x76cd10)

protected:
    CCreature(void);                                          // 0x762e40 (KR inline in npc.h)

    void Init(const char* name, unsigned long flags);         // 0x76c3e0

    PADDING(0x04, 0x20);
    WPuppet* m_pPet;            // 0x20
    PADDING(0x24, 0x74);
    float m_unk74;              // 0x74, 0.5 for the camera birds (the speed of the creatures)
    PADDING(0x78, 0x120);
};

CHECK_SIZE(CCreature, 0x120);
BEGIN_LAYOUT_CHECK(CCreature)
    CHECK_FIELD(CCreature, m_pPet, 0x20);
    CHECK_FIELD(CCreature, m_unk74, 0x74);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_NPC_H
