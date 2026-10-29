// Original: d:\build\custom\temp\code\client\projectg\jukeboxdlg.cpp (JP 983 exe)
#include "JukeBoxDlg.h"

#include <stdlib.h>
#include <algorithm>

#include "ObjectFactory.h"
#include "SoundManager.h"
#include "commonutil.h"

// The constructor (0x7ba760) is declared only: cl would inline it into the
// factory function, which the original calls out of line.

// 0x7bac60
void FrJukeBoxDlg::OnChangePlayPauseButton(void)
{
    bool isPlaying = data_f023f4->IsPlaying(data_e7b0e0[data_e7b0d0].file);

    if (m_pPlay) {
        const char* name;

        if (isPlaying) {
            name = "btn_pause";
        } else {
            name = "btn_play";
        }
        m_pPlay->SetButtonImg(MakeStr("%s_n", name), FrButton::NORMAL);
        m_pPlay->SetButtonImg(MakeStr("%s_o", name), FrButton::OVER);
        m_pPlay->SetButtonImg(MakeStr("%s_o", name), FrButton::PRESSED);
    }
}

// 0x7bad60
void FrJukeBoxDlg::SetLightRect(void)
{
    const Bitmap* bitmap = data_f022d0->GetBitmap("jukebox_light");
    m_lightRect.x = m_posX + 117.5;
    m_lightRect.y = m_posY - 144.5;
    m_lightRect.w = (float)bitmap->Width();
    m_lightRect.h = (float)bitmap->Height();
}

// 0x7badd0
void FrJukeBoxDlg::DrawPlayingRowMarks(FrListItem* pItem)
{
    WRect left(pItem->pos.x - 15.0, pItem->pos.y + 1.0, m_pPlayingMarkL->Width(), m_pPlayingMarkL->Height());
    data_f022d0->GetManager()->GetGDI()->DrawTexture(m_pPlayingMarkL, left, 0xffffffff, 0);
    WRect right(pItem->pos.x + 241.0, pItem->pos.y + 1.0, m_pPlayingMarkR->Width(), m_pPlayingMarkR->Height());
    data_f022d0->GetManager()->GetGDI()->DrawTexture(m_pPlayingMarkR, right, 0xffffffff, 0);
}

// 0x7baed0
void FrJukeBoxDlg::DrawSelectedRowMarks(FrListItem* pItem)
{
    WRect left(pItem->pos.x - 15.0, pItem->pos.y + 1.0, m_pSelectedMarkL->Width(), m_pSelectedMarkL->Height());
    data_f022d0->GetManager()->GetGDI()->DrawTexture(m_pSelectedMarkL, left, 0xffffffff, 0);
    WRect right(pItem->pos.x + 241.0, pItem->pos.y + 1.0, m_pSelectedMarkR->Width(), m_pSelectedMarkR->Height());
    data_f022d0->GetManager()->GetGDI()->DrawTexture(m_pSelectedMarkR, right, 0xffffffff, 0);
}

// 0x7bb400
void FrJukeBoxDlg::PlayShuffledBGM(void)
{
    int* order = new int[data_e7b0cc];
    for (int i = 0; i < data_e7b0cc; i++) {
        order[i] = i;
    }
    for (int i = 0; i < data_e7b0cc; i++) {
        int pick = rand() % data_e7b0cc;
        std::swap(order[i], order[pick]);
        data_e7b0d0 = pick;
    }
    CBGMPlaylist::GetInstance()->Clear();
    for (int i = 0; i < data_e7b0cc; i++) {
        const sJukeBoxBGM& bgm = data_e7b0e0[order[i]];
        CBGMPlaylist::GetInstance()->AddTrack(bgm.file);
    }
    CBGMPlaylist::GetInstance()->Play();
    if (order) {
        delete[] order;
    }
}

// 0x7bb120
IObject* FrJukeBoxDlgMakeInstance(void)
{
    return new FrJukeBoxDlg;
}

struct __sFrJukeBoxDlg {
    // 0x7bb190
    __sFrJukeBoxDlg(void)
    {
        ObjectFactory().AddObjectFunctor(FrJukeBoxDlgMakeInstance, "FrJukeBoxDlg");
    }
};
static __sFrJukeBoxDlg s_registerFrJukeBoxDlg;
