// Original: unknown, JP-only RTTI class CAutoMiracleSignController (JP 983 exe)
#ifndef PG_JP983_NEW_CAUTOMIRACLESIGNCONTROLLER_H
#define PG_JP983_NEW_CAUTOMIRACLESIGNCONTROLLER_H

#include "defines.h"

#include "IController.h"

class WRTTI;

// JP-only controller (RTTI name CAutoMiracleSignController), vtable at
// 0xcfea98, IController's 14 slots. Slots 2-6 and 8-13 hold IController's
// own bodies (the same VAs as IController's vtable 0xd0230c); the split
// assigned those shared bodies to this unit, so they are written here as
// overrides with IController's code.
class CAutoMiracleSignController : public IController
{
public:
    static const WRTTI m_RTTI;                                // 0xe73e00

    CAutoMiracleSignController(void);

    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x47db30)
    virtual ~CAutoMiracleSignController(void);                // 1 (??_G 0x47dc00; ~ 0x47db40, not split)
    virtual bool Reset(void);                                 // 2 (0x4b4f90)
    virtual bool IsReady(void);                               // 3 (0x4b4fa0)
    virtual bool CheckEnabled4(void);                         // 4 (0x4b4fb0)
    virtual bool CheckEnabled5(void);                         // 5 (0x4b4fc0)
    virtual bool CheckEnabled6(int arg);                      // 6 (0x4b4fd0)
    virtual bool CheckPlayer(unsigned char playerIndex);      // 7 (0x47de80)
    virtual bool CheckEnabled8(void);                         // 8 (0x4b4ff0)
    virtual bool CheckEnabled9(void);                         // 9 (0x4b5000)
    virtual bool CheckEnabled10(int arg);                     // 10 (0x4b5010)
    virtual bool CheckEnabled11(void);                        // 11 (0x4b5020)
    virtual bool CheckEnabled12(void);                        // 12 (0x4b5030)
    virtual bool CheckEnabled13(void);                        // 13 (0x4b5040)

    // 0x47dde0 (not split): the auto-miracle sign condition for a player.
    bool CanShowForPlayer(unsigned char playerIndex);
};

#endif // PG_JP983_NEW_CAUTOMIRACLESIGNCONTROLLER_H
