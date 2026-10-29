// Original: d:\build\custom\temp\code\client\projectg\uccmanager.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_UCCMANAGER_H
#define PG_JP983_CLIENT_PROJECTG_UCCMANAGER_H

#include <windows.h>
#include <string.h>
#include <list>
#include <map>
#include <string>

#include "defines.h"
#include "padding.h"

// The common head of every IFF item record (KR keeps it in uccmanager.h; its
// original header is not identified). JP moved the icon name from KR's 0x31
// to 0x49 (IsDisplayUccClothes 0x7eb6a0); only that member is declared.
struct IFF_ITEM_COMMON {
	PADDING(0x00, 0x49);
	char m_icon[0x28];              // 0x49, length from KR, not verified in JP
};

BEGIN_LAYOUT_CHECK(IFF_ITEM_COMMON)
	CHECK_FIELD(IFF_ITEM_COMMON, m_icon, 0x49);
END_LAYOUT_CHECK

// A UCC (user-created) texture set owned by an item (KR sUccItem). Laid out
// as in KR; JP-verified: m_uccName 0x14 (UccCopyDlg), m_downloadCount 0x60
// (IsDownloadComplete 0x7eb630). The size is KR's, not verified in JP.
struct sUccItem {
	unsigned long m_serial;         // 0x00, item serial (-1: none)
	char m_uccKey[9];               // 0x04
	PADDING(0x0D, 0x10);
	unsigned long m_typeId;         // 0x10
	char m_uccName[0x29];           // 0x14
	PADDING(0x3D, 0x40);
	unsigned long m_texture[3];     // 0x40
	unsigned long m_period[4];      // 0x4C
	const void* m_pIcon;            // 0x5C, a Bitmap in KR
	unsigned char m_downloadCount;  // 0x60
	PADDING(0x61, 0x64);
};

CHECK_SIZE(sUccItem, 0x64);
BEGIN_LAYOUT_CHECK(sUccItem)
	CHECK_FIELD(sUccItem, m_uccKey, 0x04);
	CHECK_FIELD(sUccItem, m_typeId, 0x10);
	CHECK_FIELD(sUccItem, m_uccName, 0x14);
	CHECK_FIELD(sUccItem, m_downloadCount, 0x60);
END_LAYOUT_CHECK

// A UCC clothes texture set.
struct sUccClothes : sUccItem {
};

CHECK_SIZE(sUccClothes, 0x64);

// A UCC aztec texture, same head as sUccClothes (KR layout; JP-verified:
// m_downloadCount 0x60, IsDownloadComplete 0x7eb650).
struct sUccAztec {
	unsigned long m_serial;         // 0x00
	char m_uccKey[9];               // 0x04
	PADDING(0x0D, 0x10);
	unsigned long m_typeId;         // 0x10
	UNKNOWN(0x14, 0x5C);
	const void* m_pIcon;            // 0x5C, a Bitmap in KR
	unsigned char m_downloadCount;  // 0x60
	PADDING(0x61, 0x64);
};

CHECK_SIZE(sUccAztec, 0x64);
BEGIN_LAYOUT_CHECK(sUccAztec)
	CHECK_FIELD(sUccAztec, m_typeId, 0x10);
	CHECK_FIELD(sUccAztec, m_downloadCount, 0x60);
END_LAYOUT_CHECK

class Bitmap;
struct sUccTempClothes;
struct sDisplayUccClothes;

// An item whose UCC texture must be refreshed (KR layout; JP-verified by the
// 0x10-byte copy of GetRefreshItem 0x7ee1e0).
struct sUccRefreshItem {
	unsigned long m_typeId;         // 0x00
	char m_uccKey[9];               // 0x04
	PADDING(0x0D, 0x10);
};

CHECK_SIZE(sUccRefreshItem, 0x10);
BEGIN_LAYOUT_CHECK(sUccRefreshItem)
	CHECK_FIELD(sUccRefreshItem, m_typeId, 0x00);
	CHECK_FIELD(sUccRefreshItem, m_uccKey, 0x04);
END_LAYOUT_CHECK

// The UCC texture manager (KR uccmanager.h CUccManager, the UccManager()
// singleton 0x7ef6b0). Only the members the JP bodies decompiled so far use
// are declared. KR members; VS 2010 std::list is 0xc bytes and std::map 0x10,
// so everything after m_iconMap is 4 bytes later than in KR (JP-verified:
// m_aztecList 0xc by _GetAztec 0x7ed510, m_refreshList 0x40 and
// m_refreshLock 0x4c by GetRefreshItem 0x7ee1e0). sUccTempClothes and
// sDisplayUccClothes are not modelled yet.
class CUccManager {
public:
	CUccManager(void);   // 0x7ef4a0
	~CUccManager(void);

	void AddClothes(unsigned char slot, sUccClothes& clothes, bool send, bool request);  // 0x7ee460
	sUccClothes* FindClothes(unsigned long typeId, const char* uccKey);  // 0x7ed3c0
	sUccClothes* FindClothes(unsigned long serial);                      // 0x7edb00
	void AddRefreshItem(unsigned long typeId, const char* uccKey);       // 0x7ee020
	sUccAztec* FindAztec(unsigned long typeId, const char* uccKey);      // 0x7ed480
	bool IsDownloadComplete(unsigned long typeId, const char* uccKey);   // 0x7ed540
	bool IsDownloadComplete(sUccClothes* clothes);                       // 0x7eb630
	bool IsDownloadComplete(sUccAztec* aztec);                           // 0x7eb650
	bool SetDownloadComplete(sUccAztec* aztec);                          // 0x7eb670
	bool SetDownloadComplete(sUccClothes* clothes);                      // 0x7ed5a0
	bool SetDownloadComplete(unsigned long typeId, const char* uccKey);  // 0x7edcc0
	void BuildDisplayClothesSet(void);                                   // 0x7ebfe0
	bool GetRefreshItem(sUccRefreshItem& item);                          // 0x7ee1e0
	bool IsDisplayUccClothes(const IFF_ITEM_COMMON* item);               // 0x7eb6a0

private:
	void RequestClothes(unsigned long typeId, const char* uccKey, bool force);  // 0x7ebfb0
	void RequestAztec(unsigned long typeId, const char* uccKey, bool force);    // 0x7eb690
	sUccClothes* _GetClothes(unsigned long serial);                             // 0x7ed4e0
	sUccAztec* _GetAztec(unsigned long serial);                                 // 0x7ed510

	LAYOUT_CHECK_FRIEND;
	std::list<sUccClothes> m_clothesList;  // 0x00
	std::list<sUccAztec> m_aztecList;      // 0x0C
	std::map<std::string, Bitmap*> m_iconMap;             // 0x18
	std::list<sUccTempClothes> m_tempClothesList;         // 0x28
	std::list<sDisplayUccClothes> m_displayClothesList;   // 0x34
	std::list<sUccRefreshItem> m_refreshList;             // 0x40
	CRITICAL_SECTION m_refreshLock;                       // 0x4C
};

CHECK_SIZE(CUccManager, 0x64);

BEGIN_LAYOUT_CHECK(CUccManager)
	CHECK_FIELD(CUccManager, m_clothesList, 0x00);
	CHECK_FIELD(CUccManager, m_aztecList, 0x0C);
	CHECK_FIELD(CUccManager, m_iconMap, 0x18);
	CHECK_FIELD(CUccManager, m_tempClothesList, 0x28);
	CHECK_FIELD(CUccManager, m_displayClothesList, 0x34);
	CHECK_FIELD(CUccManager, m_refreshList, 0x40);
	CHECK_FIELD(CUccManager, m_refreshLock, 0x4C);
END_LAYOUT_CHECK

CUccManager* UccManager(void);  // 0x7ef6b0

#endif // PG_JP983_CLIENT_PROJECTG_UCCMANAGER_H
