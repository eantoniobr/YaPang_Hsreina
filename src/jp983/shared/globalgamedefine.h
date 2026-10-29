// Original: shared/globalgamedefine.h (JP 983 exe)
#ifndef PG_JP983_SHARED_GLOBALGAMEDEFINE_H
#define PG_JP983_SHARED_GLOBALGAMEDEFINE_H

#include "defines.h"
#include "padding.h"

// An item of the player's inventory (KR globalgamedefine.h sItemInfo, KR size
// 0xa8). Only the members JP code is seen to read, at their JP offsets (the
// same as KR's): GetMyItemInfo 0x7e9f80 compares the serial (list node +8),
// CUccManager::FindClothes(serial) 0x7edb00 the type id (+4) and the UCC key
// (+0x52), ??0sWarpItem 0x8d6dd0 the count (+0xc). The JP size is not
// verified, so the struct ends after m_uccKey; the KR constructor is not
// modelled.
struct sItemInfo {
	unsigned long m_serial;       // 0x00
	unsigned long m_typeId;       // 0x04
	PADDING(0x08, 0x0c);
	short m_count;                // 0x0c, how many of a stackable item the player holds
	PADDING(0x0e, 0x52);
	char m_uccKey[9];             // 0x52
};

BEGIN_LAYOUT_CHECK(sItemInfo)
	CHECK_FIELD(sItemInfo, m_serial, 0x00);
	CHECK_FIELD(sItemInfo, m_typeId, 0x04);
	CHECK_FIELD(sItemInfo, m_count, 0x0c);
	CHECK_FIELD(sItemInfo, m_uccKey, 0x52);
END_LAYOUT_CHECK

// A period card in use (KR globalgamedefine.h, packed, KR size 0x41).
// FrCardRemove::BuildCurPartCardList 0x8001e0 reads partsId (list node
// +0x14) and pushes typeId (node +0xc). The JP size is not verified, so only
// the leading members are modelled.
#pragma pack(push, 1)
struct sSCardAvilityPeriodInfo {
	unsigned long id;               // 0x00
	unsigned long typeId;           // 0x04, the card's type id
	unsigned long partsTypeId;      // 0x08, the character / caddie type id it is put on (0: none)
	unsigned long partsId;          // 0x0c, the character / caddie id
};
#pragma pack(pop)

BEGIN_LAYOUT_CHECK(sSCardAvilityPeriodInfo)
	CHECK_FIELD(sSCardAvilityPeriodInfo, typeId, 0x04);
	CHECK_FIELD(sSCardAvilityPeriodInfo, partsId, 0x0c);
END_LAYOUT_CHECK

#endif // PG_JP983_SHARED_GLOBALGAMEDEFINE_H
