// The JP 983 add-on parts (JpAddonPart.h): the AddonPart.iff table and the
// add-on mesh pets of each CPetFrame.
#include "JpAddonPart.h"

#include <stdio.h>
#include <string.h>

#include <list>
#include <map>

#include "commonutil.h"
#include "wpuppet.h"
#include "wresrcmng.h"
#include "client/Wangreal/source/XUnzip.h"
#include "client/Wangreal/source/XZip.h"

namespace {

// The records by tid (0xa3bef0 keys a map by character index, then by tid).
typedef std::multimap<unsigned int, sJpAddonPart> AddonMap;
AddonMap s_addons;
bool s_loaded = false;

// 0xa3bef0's filter: a character tid, or a part tid without 0x600.
bool IsAddonTid(unsigned int tid) {
	unsigned int type = tid >> 26;
	if (type == 1)
		return true;
	return type == 2 && (tid & 0x600) == 0;
}

} // namespace

// Ours (CItemManager::Load reads it with the other tables, 0xa3ead0).
bool Jp_AddonParts_Load() {
	if (s_loaded)
		return !s_addons.empty();
	s_loaded = true;

	WFile file("pangya_jp.iff");
	int length = file.Length();
	if (length <= 0)
		return false;
	char* data = new char[length];
	file.Read(data, length);
	file.Close();

	HZIP zip = OpenZipU(data, length, ZIP_MEMORY);
	if (!zip) {
		delete[] data;
		return false;
	}
	ZIPENTRY entry;
	GetZipItemA(zip, -1, &entry);
	int count = entry.index;
	for (int i = 0; i < count; i++) {
		GetZipItemA(zip, i, &entry);
		if (_stricmp(entry.name, "AddonPart.iff") != 0)
			continue;
		char* item = new char[entry.unc_size];
		UnzipItem(zip, i, item, entry.unc_size, ZIP_MEMORY);
		// The 8-byte head (count, binding id, version), then the records.
		unsigned short records = *(unsigned short*)item;
		if (entry.unc_size >= 8 + (long)records * (long)sizeof(sJpAddonPart)) {
			for (int r = 0; r < records; r++) {
				const sJpAddonPart* record = (const sJpAddonPart*)(item + 8 + r * sizeof(sJpAddonPart));
				if (record->m_active == 0 || !IsAddonTid(record->m_tid))
					continue;
				s_addons.insert(AddonMap::value_type(record->m_tid, *record));
			}
		}
		delete[] item;
		break;
	}
	CloseZipU(zip);
	delete[] data;
	printf("[JP] AddonPart.iff: %d add-on pet(s)\n", (int)s_addons.size());
	fflush(stdout);
	return !s_addons.empty();
}

namespace {

// One attached add-on: what 0x8af370 keeps in the frame's +0x334 map (the
// pet at +0x14, the texture handles at +0x18), with the slot it came from
// (-1: the character's) and the bone pet it was attached to.
struct sAddonPet {
	int m_slot;
	WPuppet* m_bonePet;
	WPuppet* m_pet;
	int m_tex[3];
};
typedef std::list<sAddonPet> AddonPetList;
// The JP CPetFrame's +0x334 container, kept beside the KR frame (which has no
// room for it), by frame.
std::map<const CPetFrame*, AddonPetList> s_framePets;

void ReleaseAddonPet(sAddonPet& addon, WPuppet* bonePet) {
	if (bonePet != NULL && addon.m_bonePet == bonePet)
		bonePet->ReplaceMeshBones(addon.m_pet, NULL, 0, 0);
	if (g_resrcmng != NULL) {
		g_resrcmng->Release(addon.m_pet, false);
		for (int i = 0; i < 3; i++) {
			if (addon.m_tex[i] != 0)
				g_resrcmng->Release(addon.m_tex[i]);
		}
	}
}

} // namespace

// 0x8b1bc0: the slot's previous add-ons out, then each record of tid as
// 0x8acbc0 (textures) and 0x8af370 (the mesh, as a SetPartPets slot) do.
void Jp_PetFrame_SetAddonPets(const CPetFrame* frame, WPuppet* bonePet, int slot, unsigned int tid) {
	std::map<const CPetFrame*, AddonPetList>::iterator found = s_framePets.find(frame);
	if (found != s_framePets.end()) {
		AddonPetList& pets = found->second;
		for (AddonPetList::iterator it = pets.begin(); it != pets.end();) {
			if (it->m_slot == slot) {
				ReleaseAddonPet(*it, bonePet);
				it = pets.erase(it);
			} else {
				++it;
			}
		}
	}
	if (bonePet == NULL || tid == 0 || !Jp_AddonParts_Load())
		return;

	std::pair<AddonMap::iterator, AddonMap::iterator> range = s_addons.equal_range(tid);
	for (AddonMap::iterator it = range.first; it != range.second; ++it) {
		const sJpAddonPart& record = it->second;
		char name[0x40];
		_snprintf(name, sizeof(name) - 1, "%s.mpet", record.m_model);
		name[sizeof(name) - 1] = '\0';

		// 0x8acbc0
		int texA[3] = { 0, 0, 0 };
		int texB[3] = { 0, 0, 0 };
		for (int i = 0; i < 3; i++) {
			if (record.m_texture[i][0] != '\0' && record.m_orgTexture[i][0] != '\0') {
				texA[i] = g_resrcmng->LoadTexture(record.m_texture[i], 0, 0, 0);
				texB[i] = g_resrcmng->LoadTexture(record.m_orgTexture[i], 0, 0, 0);
			}
		}

		// 0x8af370
		WPuppet* pet = g_resrcmng->GetPuppet(name, false, true, false);
		if (pet != NULL) {
			bonePet->ReplaceMeshBones(NULL, pet, texA[0], texB[0]);
			for (int i = 1; i < 3; i++) {
				if (texA[i] != 0 && texB[i] != 0)
					bonePet->ChangeTextureByHandle(texA[i], texB[i], pet);
			}
			sAddonPet addon;
			addon.m_slot = slot;
			addon.m_bonePet = bonePet;
			addon.m_pet = pet;
			for (int i = 0; i < 3; i++)
				addon.m_tex[i] = texA[i];
			s_framePets[frame].push_back(addon);
		} else {
			for (int i = 0; i < 3; i++) {
				if (texA[i] != 0)
					g_resrcmng->Release(texA[i]);
			}
		}
		for (int i = 0; i < 3; i++) {
			if (texB[i] != 0)
				g_resrcmng->Release(texB[i]);
		}
	}
}

// 0x8b0e50 / the destructor 0x8b1aa0: every add-on of the frame out.
void Jp_PetFrame_ReleaseAddonPets(const CPetFrame* frame, WPuppet* bonePet) {
	std::map<const CPetFrame*, AddonPetList>::iterator found = s_framePets.find(frame);
	if (found == s_framePets.end())
		return;
	for (AddonPetList::iterator it = found->second.begin(); it != found->second.end(); ++it)
		ReleaseAddonPet(*it, bonePet);
	s_framePets.erase(found);
}

// 0x8af2d0: whether one of the frame's add-ons is the pet so named
// (case-insensitive), the second half of HasMPet 0x8af620.
bool Jp_PetFrame_HasAddonPet(const CPetFrame* frame, const char* name) {
	std::map<const CPetFrame*, AddonPetList>::const_iterator found = s_framePets.find(frame);
	if (found == s_framePets.end())
		return false;
	for (AddonPetList::const_iterator it = found->second.begin(); it != found->second.end(); ++it) {
		if (it->m_pet != NULL && _stricmp(it->m_pet->GetPuppetName(), name) == 0)
			return true;
	}
	return false;
}
