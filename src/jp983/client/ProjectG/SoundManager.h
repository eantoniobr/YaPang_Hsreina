// Original: d:\build\custom\temp\code\client\projectg\soundmanager.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_SOUNDMANAGER_H
#define PG_JP983_CLIENT_PROJECTG_SOUNDMANAGER_H

#include "defines.h"

class WView;
class WVector;
class CSoundObject;
struct _SFX_INFO;

// The game's sound manager. Only what the JP bodies call so far is declared;
// the virtual slots follow KR soundmanager.h (PlaySfx is slot 3 in the JP
// calls too).
class CSoundManager
{
public:
    virtual ~CSoundManager(void);                                       // 0
    virtual void Process(float fDelta, WView* pView);                   // 1
    virtual _SFX_INFO* LoadSfx(const char* name, const WVector* pPos, unsigned long flags, const char* alias, const CSoundObject* pOwner, float volume, float range); // 2
    virtual void PlaySfx(const char* name, const WVector* pPos, unsigned long flags, const char* alias, const CSoundObject* pOwner, float volume, float range); // 3

    float GetBGMVolume(void) const;                                     // 0x9b5a80
    void SetBGMVolume(float volume);                                    // 0x9b5a20
    bool IsPlaying(const char* alias);                                  // 0x9b6890
};

// g_audio (KR name); the JP exe has no symbol for it, so it keeps the
// original object's name for the pointer at 0xf023f4.
extern "C" CSoundManager* data_f023f4;

// 200.0f, the range every JP PlaySfx call passes where KR wrote the literal:
// a float variable at 0xd00d90 (no symbol in the JP exe).
extern "C" const float data_d00d90;

#endif // PG_JP983_CLIENT_PROJECTG_SOUNDMANAGER_H
