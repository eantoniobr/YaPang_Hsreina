// Original: d:\build\custom\temp\code\client\projectg\magiccarpet.cpp (JP 983 exe)
#include "magiccarpet.h"

#include <stdlib.h>

#include "ObjectFactory.h"
#include "ClientSetting.h"
#include "SoundManager.h"
#include "commonutil.h"

// The constructor (0x761540, unplaced in the pairing) is declared only:
// cl would inline it into the factory function, which the original calls
// out of line. The destructor emits the vtable.

// 0x761560
const WRTTI* CMagicCarpetHelper::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x761570
void CMagicCarpetHelper::OnInit(void)
{
}

// 0x761580
void CMagicCarpetHelper::OnLoad(void)
{
}

// 0x761590
void CMagicCarpetHelper::OnDisplay(void)
{
}

// 0x7615a0
void CMagicCarpetHelper::PlaySfxMagicCarpetBoundSound(void)
{
    int first = rand() % 5 + 1;
    data_f023f4->PlaySfx(MakeStr("magic_melody%d", first), NULL, 0, NULL, NULL, 0.5f, data_d00d90);

    int second = rand() % 5 + 1;
    if (second != first) {
        data_f023f4->PlaySfx(MakeStr("magic_melody%d", second), NULL, 0, NULL, NULL, 0.5f, data_d00d90);

        int third = rand() % 5 + 1;
        if (third != first && third != second) {
            data_f023f4->PlaySfx(MakeStr("magic_melody%d", third), NULL, 0, NULL, NULL, 0.5f, data_d00d90);
        }
    } else {
        data_f023f4->PlaySfx("magic_bounce", NULL, 0, NULL, NULL, 0.5f, data_d00d90);
    }

    bool playing[3];
    playing[0] = data_f023f4->IsPlaying("magicharp_goal_long1");
    playing[1] = data_f023f4->IsPlaying("magicharp_goal_short1");
    playing[2] = data_f023f4->IsPlaying("magicharp_goal_short2");

    if (!playing[0] && !playing[1] && !playing[2]) {
        int chance = rand() % 50;
        if (chance == 1) {
            data_f023f4->PlaySfx("magicharp_goal_long1", NULL, 0, NULL, NULL, 0.5f, data_d00d90);
        } else if (chance == 2) {
            data_f023f4->PlaySfx("magicharp_goal_short1", NULL, 0, NULL, NULL, 0.5f, data_d00d90);
        } else if (chance == 3) {
            data_f023f4->PlaySfx("magicharp_goal_short2", NULL, 0, NULL, NULL, 0.5f, data_d00d90);
        }
    }
}

// 0x7617d0: the factory function registered under "CMagicCarpetHelper".
IObject* CMagicCarpetHelperMakeInstance(void)
{
    return new CMagicCarpetHelper;
}

// 0x761840 (and its static instance's initializer)
struct __impCMagicCarpetHelper
{
    __impCMagicCarpetHelper(void)
    {
        ObjectFactory().AddObjectFunctor(CMagicCarpetHelperMakeInstance, "CMagicCarpetHelper");
        ActorFactory().AddActorClass("CMagicCarpetHelper");
    }
};
static __impCMagicCarpetHelper s_impCMagicCarpetHelper;

// 0x761870
void CMagicCarpetHelper::HandleMsg(const MsgObject& msg)
{
    switch (msg.m_msg) {
    case 0x2fc:
        PlaySfxMagicCarpetBoundSound();
        break;
    case 0x2fa:
        m_bAutoVolume = true;
        m_bVolumeDown = true;
        break;
    case 0x2fb:
        m_bVolumeDown = false;
        break;
    }
}

// 0x7618b0
void CMagicCarpetHelper::SetBgmVolume(const float& volume)
{
    if (COption::Instance()->IsBgmOn()) {
        data_f023f4->SetBGMVolume(volume);
    } else if (COption::Instance()->aGetBgmVolume() > 0.0f) {
        data_f023f4->SetBGMVolume(0.0f);
    }
}

// 0x761910
CMagicCarpetHelper::~CMagicCarpetHelper(void)
{
    SetBgmVolume(COption::Instance()->aGetBgmVolume());
}

// 0x761980
void CMagicCarpetHelper::AutoVolumeAdjustProcess(const float& elapsed)
{
    if (m_bVolumeDown) {
        if (data_f023f4->GetBGMVolume() > COption::Instance()->aGetSfxVolume() * 0.5) {
            float volume = (float)(data_f023f4->GetBGMVolume() - elapsed * 0.25);
            if (!(volume > 0.0f)) {
                volume = 0.0f;
            }
            if (volume > COption::Instance()->aGetBgmVolume() * 0.5) {
                SetBgmVolume(volume);
            }
        } else {
            SetBgmVolume((float)(COption::Instance()->aGetSfxVolume() * 0.5));
        }
    } else {
        if (data_f023f4->GetBGMVolume() < COption::Instance()->aGetBgmVolume()) {
            float volume = (float)(data_f023f4->GetBGMVolume() + elapsed * 0.25);
            if (volume > 1.0f) {
                volume = 1.0f;
            }
            SetBgmVolume(volume);
        } else {
            m_bAutoVolume = false;
            SetBgmVolume(COption::Instance()->aGetBgmVolume());
        }
    }
}

// 0x761b10
void CMagicCarpetHelper::OnProcess(float elapsed)
{
    if (m_bAutoVolume) {
        AutoVolumeAdjustProcess(elapsed);
    }
}
