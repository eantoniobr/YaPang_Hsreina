// Original: unknown, JP-only RTTI class IController (JP 983 exe)
#ifndef PG_JP983_NEW_ICONTROLLER_H
#define PG_JP983_NEW_ICONTROLLER_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"

class WRTTI;

// Base of the JP sign controllers (RTTI name IController : IObject), vtable
// 0xd0230c, 14 slots. Slots 2-13 hold its own bodies, which the derived
// controllers that do not override them share: slot 2 clears m_state and
// returns true, slot 3 returns true, the others return m_enabled. The slot
// names are descriptive guesses; the layout is known only as far as those
// bodies read it.
class IController : public IObject
{
    LAYOUT_CHECK_FRIEND;
public:
    static const WRTTI m_RTTI;                                // 0xe74c44

    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x4b4f70)
    virtual ~IController(void);                               // 1 (??_G 0x4b50e0; ~ 0x4b4f80)
    virtual bool Reset(void);                                 // 2 (0x4b4f90)
    virtual bool IsReady(void);                               // 3 (0x4b4fa0)
    virtual bool CheckEnabled4(void);                         // 4 (0x4b4fb0)
    virtual bool CheckEnabled5(void);                         // 5 (0x4b4fc0)
    virtual bool CheckEnabled6(int arg);                      // 6 (0x4b4fd0)
    virtual bool CheckPlayer(unsigned char playerIndex);      // 7 (0x4b4fe0)
    virtual bool CheckEnabled8(void);                         // 8 (0x4b4ff0)
    virtual bool CheckEnabled9(void);                         // 9 (0x4b5000)
    virtual bool CheckEnabled10(int arg);                     // 10 (0x4b5010)
    virtual bool CheckEnabled11(void);                        // 11 (0x4b5020)
    virtual bool CheckEnabled12(void);                        // 12 (0x4b5030)
    virtual bool CheckEnabled13(void);                        // 13 (0x4b5040)

protected:
    IController(void);

    PADDING(0x4, 0x8);
    bool m_enabled;                                           // 0x8
    PADDING(0x9, 0xc);
    int m_state;                                              // 0xc
};

BEGIN_LAYOUT_CHECK(IController)
    CHECK_FIELD(IController, m_enabled, 0x8);
    CHECK_FIELD(IController, m_state, 0xc);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_ICONTROLLER_H
