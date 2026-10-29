// Original: d:\build\custom\temp\code\client\projectg\uccmanager.cpp (JP 983 exe)
#include <string.h>

#include "jp983/client/ProjectG/UccManager.h"
#include "jp983/client/ProjectG/Packet.h"
#include "jp983/shared/packet.h"

// The UCC texture downloader (KR NetResourceManager.h); no jp983 header
// declares it yet. Instance data_e74c78.
class NetResourceManager {
public:
	static NetResourceManager* Instance(void);
	void DownloadUccClothes(unsigned long typeId, const char* uccKey, unsigned short slot, bool force);  // 0x9ab5e0
};

extern "C" NetResourceManager* data_e74c78;

// KR ucclibrary.h; the shared jp983 UccLibrary.h does not declare it yet.
bool IsSameClothes(unsigned long typeId, unsigned long otherTypeId);  // 0x7e95d0

inline NetResourceManager* NetResourceManager::Instance(void)
{
	return data_e74c78;
}

// 0x7eb630
bool CUccManager::IsDownloadComplete(sUccClothes* clothes)
{
	if (clothes && clothes->m_downloadCount == 1) {
		return true;
	}

	return false;
}

// 0x7eb650
bool CUccManager::IsDownloadComplete(sUccAztec* aztec)
{
	if (aztec && aztec->m_downloadCount == 1) {
		return true;
	}

	return false;
}

// 0x7eb670
bool CUccManager::SetDownloadComplete(sUccAztec* aztec)
{
	if (aztec) {
		aztec->m_downloadCount++;
		return IsDownloadComplete(aztec);
	}

	return false;
}

// 0x7eb690
void CUccManager::RequestAztec(unsigned long typeId, const char* uccKey, bool force)
{
}

// 0x7eb6a0
bool CUccManager::IsDisplayUccClothes(const IFF_ITEM_COMMON* item)
{
	return _stricmp(item->m_icon, "UCCDISPLAY") == 0;
}

// 0x7ebfb0
void CUccManager::RequestClothes(unsigned long typeId, const char* uccKey, bool force)
{
	NetResourceManager::Instance()->DownloadUccClothes(typeId, uccKey, force, false);
}

// 0x7ebfe0
void CUccManager::BuildDisplayClothesSet(void)
{
}

// 0x7ed3c0
sUccClothes* CUccManager::FindClothes(unsigned long typeId, const char* uccKey)
{
	std::list<sUccClothes>::iterator it;

	for (it = m_clothesList.begin(); it != m_clothesList.end(); ++it) {
		sUccClothes* clothes = &(*it);
		if (clothes->m_typeId == typeId && strcmp(clothes->m_uccKey, uccKey) == 0) {
			return clothes;
		}
	}

	for (it = m_clothesList.begin(); it != m_clothesList.end(); ++it) {
		sUccClothes* clothes = &(*it);
		if (strcmp(clothes->m_uccKey, uccKey) == 0 && IsSameClothes(typeId, clothes->m_typeId)) {
			return clothes;
		}
	}

	return NULL;
}

// 0x7ed480
sUccAztec* CUccManager::FindAztec(unsigned long typeId, const char* uccKey)
{
	for (std::list<sUccAztec>::iterator it = m_aztecList.begin(); it != m_aztecList.end(); ++it) {
		sUccAztec* aztec = &(*it);
		if (aztec->m_typeId == typeId && strcmp(aztec->m_uccKey, uccKey) == 0) {
			return aztec;
		}
	}

	return NULL;
}

// 0x7ed4e0
sUccClothes* CUccManager::_GetClothes(unsigned long serial)
{
	for (std::list<sUccClothes>::iterator it = m_clothesList.begin(); it != m_clothesList.end(); ++it) {
		sUccClothes* entry = &(*it);
		if (entry->m_serial == serial) {
			return entry;
		}
	}

	return NULL;
}

// 0x7ed510
sUccAztec* CUccManager::_GetAztec(unsigned long serial)
{
	for (std::list<sUccAztec>::iterator it = m_aztecList.begin(); it != m_aztecList.end(); ++it) {
		sUccAztec* entry = &(*it);
		if (entry->m_serial == serial) {
			return entry;
		}
	}

	return NULL;
}

// 0x7ed540
bool CUccManager::IsDownloadComplete(unsigned long typeId, const char* uccKey)
{
	sUccClothes* clothes = FindClothes(typeId, uccKey);
	sUccAztec* aztec = FindAztec(typeId, uccKey);

	if (clothes) {
		return IsDownloadComplete(clothes);
	}

	if (aztec) {
		return IsDownloadComplete(aztec);
	}

	return false;
}

// 0x7ed5a0
bool CUccManager::SetDownloadComplete(sUccClothes* clothes)
{
	if (clothes) {
		clothes->m_downloadCount++;
		if (IsDownloadComplete(clothes)) {
			for (std::list<sUccClothes>::iterator it = m_clothesList.begin(); it != m_clothesList.end(); ++it) {
				if (IsSameClothes(clothes->m_typeId, (*it).m_typeId) && _stricmp(clothes->m_uccKey, (*it).m_uccKey) == 0) {
					(*it).m_downloadCount = clothes->m_downloadCount;
					(*it).m_pIcon = clothes->m_pIcon;
					strncpy((*it).m_uccName, clothes->m_uccName, 0x29);
				}
			}

			return true;
		}
	}

	return false;
}

// 0x7edcc0
bool CUccManager::SetDownloadComplete(unsigned long typeId, const char* uccKey)
{
	sUccClothes* clothes = FindClothes(typeId, uccKey);
	sUccAztec* aztec = FindAztec(typeId, uccKey);

	if (clothes) {
		return SetDownloadComplete(clothes);
	}

	if (aztec) {
		return SetDownloadComplete(aztec);
	}

	return false;
}

// 0x7ee1e0
bool CUccManager::GetRefreshItem(sUccRefreshItem& item)
{
	EnterCriticalSection(&m_refreshLock);

	int count = m_refreshList.size();

	if (count > 0) {
		item = m_refreshList.front();
		m_refreshList.pop_front();
	}

	LeaveCriticalSection(&m_refreshLock);

	return count > 0;
}

// 0x7ee460
void CUccManager::AddClothes(unsigned char slot, sUccClothes& clothes, bool send, bool request)
{
	sUccClothes* found = FindClothes(clothes.m_typeId, clothes.m_uccKey);
	if (found == NULL) {
		m_clothesList.push_back(clothes);

		if (clothes.m_downloadCount == 0) {
			RequestClothes(clothes.m_typeId, clothes.m_uccKey, request);
		}
	} else {
		if (clothes.m_serial != 0xFFFFFFFF) {
			if (FindClothes(clothes.m_serial) == NULL) {
				sUccClothes copy = *found;
				copy.m_typeId = clothes.m_typeId;
				copy.m_serial = clothes.m_serial;
				m_clothesList.push_back(copy);

				AddRefreshItem(copy.m_typeId, copy.m_uccKey);
			}
		}
	}

	if (send) {
		// KR GCT_UCC_INFO_REQUEST (0xB1 in KR); the shared jp983 packet.h
		// does not list the JP value yet.
		WSendPacket packet(static_cast<enumClientPacket>(0xB9));
		packet.Encode1(1);
		packet.Encode4(clothes.m_serial);
		packet.Encode1(slot);
		packet.Send(SEND_TO_DEFAULT);
	}
}

// 0x7ef6b0
CUccManager* UccManager(void)
{
	static CUccManager s_uccManager;
	return &s_uccManager;
}
