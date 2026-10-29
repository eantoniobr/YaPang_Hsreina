// Original: client/ProjectG/SharedDoc.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_SHAREDDOC_H
#define PG_JP983_CLIENT_PROJECTG_SHAREDDOC_H

#include <list>

#include "defines.h"
#include "padding.h"

#include "jp983/shared/globalgamedefine.h"
#include "jp983/shared/ItemManager.h"

class CGolfDoc;

// The shared document (KR CSharedDoc : WSingleton<CSharedDoc>). The base
// and the rest of the layout are not modelled; only the members the JP units
// use are declared, at their JP offsets.
class CSharedDoc {
public:
	PADDING(0x00000, 0x0020c);
	CItemManager m_itemManager;   // 0x20c (ItemManager(); IsSameClothes 0x7e95d0)
	PADDING(0x00740, 0x037ec);
	// The period cards in use, by kind (KR 0x1248; [0] read by
	// FrCardRemove::BuildCurPartCardList 0x8001e0; the count 4 is KR's).
	std::list<sSCardAvilityPeriodInfo> m_cardPeriodList[4]; // 0x37ec
	PADDING(0x0381c, 0x03878);
	std::list<sItemInfo> m_myItemList;      // 0x3878 (KR 0x12a0; CUccManager::FindClothes 0x7edb00, GetMyItemInfo 0x7e9f80)
	std::list<sItemInfo> m_myAuxItemList;   // 0x3884 (KR 0x12ac; GetMyItemInfo 0x7e9f80)
	PADDING(0x03890, 0x10588);
	bool m_10588;         // 0x10588, set when the hole-in-one ready step ends
	PADDING(0x10589, 0x106a4);
	int m_106a4;          // 0x106a4, returned by gui_control 0x74bdb0
	PADDING(0x106a8, 0x10704);
	bool m_10704;         // 0x10704, cleared by the hole-in-one ready step
	PADDING(0x10705, 0x11024);
	CGolfDoc *m_pGolfDoc; // 0x11024 (KR 0x5040)
};

BEGIN_LAYOUT_CHECK(CSharedDoc)
	CHECK_FIELD(CSharedDoc, m_itemManager, 0x20c);
	CHECK_FIELD(CSharedDoc, m_cardPeriodList, 0x37ec);
	CHECK_FIELD(CSharedDoc, m_myItemList, 0x3878);
	CHECK_FIELD(CSharedDoc, m_myAuxItemList, 0x3884);
	CHECK_FIELD(CSharedDoc, m_10588, 0x10588);
	CHECK_FIELD(CSharedDoc, m_106a4, 0x106a4);
	CHECK_FIELD(CSharedDoc, m_10704, 0x10704);
	CHECK_FIELD(CSharedDoc, m_pGolfDoc, 0x11024);
END_LAYOUT_CHECK

// WSingleton<CSharedDoc>::m_pInstance of the JP exe (0xe47dbc).
extern "C" CSharedDoc *data_e47dbc;

#include "jp983/client/ProjectG/SharedDoc.inl"

#endif // PG_JP983_CLIENT_PROJECTG_SHAREDDOC_H
