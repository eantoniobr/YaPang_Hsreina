// The JP 983 add-on parts (AddonPart.iff): extra mesh pets the JP CPetFrame
// attaches for a character or a worn part, besides the part's own model
// (Erika R's lace parasols 0x8320800-0x8320802 add "FF_UM_02" and
// "FF_flower" to the "FF_Earing" part model; Max's racket, Kooh's cannon,
// Erika R's "FF_excalibur" are character add-ons). Their bones are hidden by
// the motions' "*hidebone" and shown by the item motions the parts'
// "*playif" switch to (the flower entrance motion). The KR CPetFrame has
// none of it: its JP_PAKS blocks call the functions below.
//
// From the JP exe's bodies (node scripts/disasm.ts --jp 0x<va>):
// CItemManager::Load reads the table (0xa3bef0, into a map at +0x474 keyed
// by the character index); the JP CPetFrame::SetPartPets 0x8b1ce0 calls
// 0x8b1bc0 for the character's tid and then for each slot's part tid, which
// looks the records up (0x8b1840), loads their textures (0x8acbc0) and
// attaches each "<model>.mpet" (0x8af370, the SetPartPets slot body) into
// the frame's add-on map (+0x334, the second container CPetFrame::HasMPet
// 0x8af620 searches).
#ifndef PG_JP_JPADDONPART_H
#define PG_JP_JPADDONPART_H

#include "defines.h"
#include "padding.h"

class WPuppet;
class CPetFrame;

// One AddonPart.iff record, 0x120 bytes (0xa3bef0 copies them whole).
struct sJpAddonPart {
	unsigned char m_active;                // 0x0, 0: skipped
	PADDING(0x1, 0x4);
	unsigned int m_tid;                    // 0x4, a character (tid >> 26 == 1) or part (2) tid
	char m_model[0x28];                    // 0x8, the mesh pet, without ".mpet"
	char m_texture[3][0x28];               // 0x30, replacing m_orgTexture (when both are set)
	char m_orgTexture[3][0x28];            // 0xa8, the model's own texture
};

CHECK_SIZE(sJpAddonPart, 0x120);
CHECK_FIELD(sJpAddonPart, m_tid, 0x4);
CHECK_FIELD(sJpAddonPart, m_model, 0x8);
CHECK_FIELD(sJpAddonPart, m_texture, 0x30);
CHECK_FIELD(sJpAddonPart, m_orgTexture, 0xa8);

// Ours: reads AddonPart.iff from pangya_jp.iff once (0xa3bef0's filter: a
// character tid, or a part tid without 0x600); false when it has none.
bool Jp_AddonParts_Load();
// The JP CPetFrame's add-ons, which the KR CPetFrame's JP_PAKS blocks
// (PartsInfo.cpp) call; kept here by frame, the KR class having no room for
// the JP +0x334 container.
// 0x8b1bc0: replaces the add-ons of a slot (-1: the character) with those of
// tid (0: none), attached to the frame's bone pet. SetPartPets calls it for
// the character tid (a full rebuild) and for each slot it sets.
void Jp_PetFrame_SetAddonPets(const CPetFrame* frame, WPuppet* bonePet, int slot, unsigned int tid);
// 0x8b0e50 / 0x8b1aa0: releases every add-on of the frame (detached from
// bonePet when they are on it).
void Jp_PetFrame_ReleaseAddonPets(const CPetFrame* frame, WPuppet* bonePet);
// 0x8af2d0: whether an add-on of the frame is named so (HasMPet's second half).
bool Jp_PetFrame_HasAddonPet(const CPetFrame* frame, const char* name);

#endif // PG_JP_JPADDONPART_H
