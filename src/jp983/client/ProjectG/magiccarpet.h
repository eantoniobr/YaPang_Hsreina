// Original: d:\build\custom\temp\code\client\projectg\magiccarpet.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_MAGICCARPET_H
#define PG_JP983_CLIENT_PROJECTG_MAGICCARPET_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/actor.h"

class WRTTI;
class IObject;

IObject* CMagicCarpetHelperMakeInstance(void);

// Lowers the BGM while the magic carpet effect plays and raises it back
// afterwards, and plays the carpet's bounce sounds (RTTI name
// CMagicCarpetHelper, vtable 0xd2219c, IActor's 15 slots). Size 0x1c (the
// `new` of the factory function 0x7617d0).
class CMagicCarpetHelper : public IActor
{
    LAYOUT_CHECK_FRIEND;
    friend IObject* CMagicCarpetHelperMakeInstance(void);
public:
    static const WRTTI m_RTTI;                                // 0xe79fec

protected:
    CMagicCarpetHelper(void);                                 // 0x761540
public:
    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x761560)
    virtual ~CMagicCarpetHelper(void);                        // 1 (0x761910, ??_G 0x761ae0)
    virtual void OnLoad(void);                                // 3 (0x761580)
    virtual void OnInit(void);                                // 4 (0x761570)
    virtual void OnProcess(float elapsed);                    // 6 (0x761b10)
    virtual void OnDisplay(void);                             // 7 (0x761590)
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x761870)

private:
    void PlaySfxMagicCarpetBoundSound(void);                  // 0x7615a0
    // 0x7618b0 (JP only): sets the BGM volume when the BGM option is on,
    // otherwise silences it.
    void SetBgmVolume(const float& volume);
    void AutoVolumeAdjustProcess(const float& elapsed);       // 0x761980

    bool m_bVolumeDown;     // 0x18 BGM fading down (true) or back up (false)
    bool m_bAutoVolume;     // 0x19 volume adjustment running
    PADDING(0x1a, 0x1c);
};

CHECK_SIZE(CMagicCarpetHelper, 0x1c);
BEGIN_LAYOUT_CHECK(CMagicCarpetHelper)
    CHECK_FIELD(CMagicCarpetHelper, m_bVolumeDown, 0x18);
    CHECK_FIELD(CMagicCarpetHelper, m_bAutoVolume, 0x19);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_MAGICCARPET_H
