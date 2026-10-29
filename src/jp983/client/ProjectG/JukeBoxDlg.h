// Original: d:\build\custom\temp\code\client\projectg\jukeboxdlg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_JUKEBOXDLG_H
#define PG_JP983_CLIENT_PROJECTG_JUKEBOXDLG_H

#include <windows.h>
#include <vector>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/Wangreal/include/bitmap.h"
#include "jp983/client/Wangreal/include/wtypes.h"
#include "client/FreshNext/include/frcmdtarget.h"
#include "client/FreshNext/include/fresh.h"
#include "client/FreshNext/include/frwndmanager.h"
#include "client/FreshNext/include/frgraphicinterface.h"
#include "client/FreshNext/include/frlistbox.h"
#include "client/FreshNext/include/frbutton.h"

// The BGM playlist player (JP only, class name unknown): a function-local
// static (0xe73e24) behind the accessor 0x483df0. Only what this unit calls.
class CBGMPlaylist {
public:
    static CBGMPlaylist* GetInstance(void);                   // 0x483df0
    void Clear(void);                                         // 0x483d60
    void Play(void);                                          // 0x4835d0
    void AddTrack(const char* file);                          // 0x483ef0
    void PlayTrack(const char* file);                         // 0x483fc0

    PADDING(0x00, 0x18);
    bool m_random;                // 0x18 random play (the "(Random)" row)
};


IObject* FrJukeBoxDlgMakeInstance(void);

// The lounge's jukebox dialog (RTTI FrJukeBoxDlg : FrForm : FrWnd (IObject,
// FrCmdTarget) and FrModalRenderer at +8; vtables 0xd26b5c, 0xd26b4c,
// 0xd26b44). Size 0x170 (the `new` of FrJukeBoxDlgMakeInstance 0x7bb120).
// FrForm and FrWnd are not modelled in the jp983 tree: their members are
// padding, the two vtable-bearing bases at 0 and 4 are kept.
class FrJukeBoxDlg : public IObject, public FrCmdTarget
{
    LAYOUT_CHECK_FRIEND;
    friend IObject* FrJukeBoxDlgMakeInstance(void);

protected:
    FrJukeBoxDlg(void);                                       // 0x7ba760

    // 0x7bad60 (JP only): places the "jukebox_light" overlay at the
    // dialog's position (+117.5, -144.5), the bitmap's size.
    void SetLightRect(void);
    void OnChangePlayPauseButton(void);                       // 0x7bac60
    // 0x7bb400 (JP only): shuffles every track into the BGM playlist and
    // plays it.
    static void PlayShuffledBGM(void);
    // 0x7badd0 / 0x7baed0 (JP only): the marks drawn at both ends of the
    // playing row and of the selected row.
    void DrawPlayingRowMarks(FrListItem* pItem);
    void DrawSelectedRowMarks(FrListItem* pItem);

private:
    PADDING(0x008, 0x034);
    float m_posX;                 // 0x34 FrWnd's position (KR m_rect)
    float m_posY;                 // 0x38
    PADDING(0x03c, 0x110);
    FrListBox* m_pList;           // 0x110 ("jukeboxlist")
    float m_playTime;             // 0x114 advanced by OnProc while playing
    PADDING(0x118, 0x128);
    WRect m_lightRect;            // 0x128 the "jukebox_light" overlay
    const Bitmap* m_pPlayingMarkL;   // 0x138 the playing row's marks
    const Bitmap* m_pPlayingMarkR;   // 0x13c
    const Bitmap* m_pSelectedMarkL;  // 0x140 the selected row's marks
    const Bitmap* m_pSelectedMarkR;  // 0x144
    PADDING(0x148, 0x150);
    bool m_isPlaying;             // 0x150
    PADDING(0x151, 0x160);
    FrButton* m_pPlay;            // 0x160 ("jukeboxplay")
    PADDING(0x164, 0x170);
};

CHECK_SIZE(FrJukeBoxDlg, 0x170);
BEGIN_LAYOUT_CHECK(FrJukeBoxDlg)
    CHECK_FIELD(FrJukeBoxDlg, m_posX, 0x34);
    CHECK_FIELD(FrJukeBoxDlg, m_pList, 0x110);
    CHECK_FIELD(FrJukeBoxDlg, m_playTime, 0x114);
    CHECK_FIELD(FrJukeBoxDlg, m_lightRect, 0x128);
    CHECK_FIELD(FrJukeBoxDlg, m_pPlayingMarkL, 0x138);
    CHECK_FIELD(FrJukeBoxDlg, m_pSelectedMarkL, 0x140);
    CHECK_FIELD(FrJukeBoxDlg, m_isPlaying, 0x150);
    CHECK_FIELD(FrJukeBoxDlg, m_pPlay, 0x160);
END_LAYOUT_CHECK

// One jukebox track (KR sJukeBoxBGM, 8-byte rows): the BGM file and title.
struct sJukeBoxBGM {
    const char* file;    // 0x0
    const char* title;   // 0x4
};

// The track list read from BGMlist.lua (0xe7b0e0, no symbol) and the current
// track (KR FrJukeBoxDlg::m_curBGM; 0xe7b0d0, no symbol).
extern "C" std::vector<sJukeBoxBGM> data_e7b0e0;
extern "C" int data_e7b0d0;
// The number of tracks (BGMlist.lua's max_count; 0xe7b0cc, no symbol).
extern "C" int data_e7b0cc;

#endif // PG_JP983_CLIENT_PROJECTG_JUKEBOXDLG_H
