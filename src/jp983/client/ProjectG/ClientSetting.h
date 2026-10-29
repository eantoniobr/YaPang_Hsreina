// Original: d:\build\custom\temp\code\client\projectg\clientsetting.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_CLIENTSETTING_H
#define PG_JP983_CLIENT_PROJECTG_CLIENTSETTING_H

#include "defines.h"
#include "padding.h"

// The video, audio and game options. Only the members the JP unit defines so
// far are declared; the JP layout is not modelled yet.
struct sOption {
	~sOption();
};

// The options singleton (KR COption : WSingleton<COption>). Only the fields
// the JP bodies read are declared; the base and the rest of the layout are
// not modelled. KR keeps the volumes in m_option (sOption at 0xcc, volumes
// at 0x80/0x84 in it); the JP offsets are 0x20 further.
class COption
{
    LAYOUT_CHECK_FRIEND;
public:
    // WSingleton<COption>::Instance(): the instance pointer at 0xe73e90 (no
    // symbol in the JP exe, so the original object's name).
    static COption* Instance(void);

    bool IsBgmOn(void) const;                                         // 0x492480
    float aGetSfxVolume(void) const { return m_sfxVolume; }
    float aGetBgmVolume(void) const { return m_bgmVolume; }

private:
    PADDING(0x000, 0x14c);
    int m_bgmOn;                   // 0x14c, nonzero: BGM enabled (IsBgmOn)
    PADDING(0x150, 0x16c);
    float m_sfxVolume;             // 0x16c
    float m_bgmVolume;             // 0x170
};

BEGIN_LAYOUT_CHECK(COption)
    CHECK_FIELD(COption, m_bgmOn, 0x14c);
    CHECK_FIELD(COption, m_sfxVolume, 0x16c);
    CHECK_FIELD(COption, m_bgmVolume, 0x170);
END_LAYOUT_CHECK

extern "C" COption* data_e73e90;

inline COption* COption::Instance(void)
{
    return data_e73e90;
}

#endif // PG_JP983_CLIENT_PROJECTG_CLIENTSETTING_H
