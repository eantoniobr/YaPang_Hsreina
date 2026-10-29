// Original: shared/globalnetworkdefine.h (JP 983 exe)
#ifndef PG_JP983_SHARED_GLOBALNETWORKDEFINE_H
#define PG_JP983_SHARED_GLOBALNETWORKDEFINE_H

#include "defines.h"
#include "padding.h"

// KR packs the whole header (pack(push, 1)).
#pragma pack(push, 1)

// A traded item (KR sTradeItem, KR size 0xaa). JP layout from the
// constructor 0x5a7400: KR's up to the card data (0x37-0x67); the card slot
// counts keep KR's offsets but two more uncleared bytes follow them, so
// uccName moves to 0x6d and uccCopierNick to 0x96 (KR 0x6b, 0x94); size
// 0xac. The constructor is out of line in JP (KR defines it inline).
struct sTradeItem {
	sTradeItem(void);                       // 0x5a7400

	unsigned long index;                    // 0x00
	unsigned long typeId;                   // 0x04
	unsigned long guid;                     // 0x08
	int count;                              // 0x0c
	unsigned char kind;                     // 0x10
	unsigned short flag;                    // 0x11
	__int64 price;                          // 0x13
	unsigned long period;                   // 0x1b
	unsigned short stats[5];                // 0x1f
	unsigned short statFlag;                // 0x29
	char uccIdx[9];                         // 0x2b
	unsigned short uccSeq;                  // 0x34
	unsigned char uccStatus;                // 0x36
	union {                                 // 0x37
		char uccData[0x30];
		unsigned long m_cardTypeIds[12];
	};
	unsigned short m_charCardSlotCount;     // 0x67 (not cleared by the constructor)
	unsigned short m_caddieCardSlotCount;   // 0x69 (not cleared by the constructor)
	UNKNOWN(0x6b, 0x6d);                    // JP only, not cleared by the constructor
	char uccName[0x29];                     // 0x6d
	char uccCopierNick[0x16];               // 0x96
};

CHECK_SIZE(sTradeItem, 0xac);
BEGIN_LAYOUT_CHECK(sTradeItem)
	CHECK_FIELD(sTradeItem, index, 0x00);
	CHECK_FIELD(sTradeItem, typeId, 0x04);
	CHECK_FIELD(sTradeItem, guid, 0x08);
	CHECK_FIELD(sTradeItem, count, 0x0c);
	CHECK_FIELD(sTradeItem, kind, 0x10);
	CHECK_FIELD(sTradeItem, flag, 0x11);
	CHECK_FIELD(sTradeItem, price, 0x13);
	CHECK_FIELD(sTradeItem, period, 0x1b);
	CHECK_FIELD(sTradeItem, stats, 0x1f);
	CHECK_FIELD(sTradeItem, statFlag, 0x29);
	CHECK_FIELD(sTradeItem, uccIdx, 0x2b);
	CHECK_FIELD(sTradeItem, uccSeq, 0x34);
	CHECK_FIELD(sTradeItem, uccStatus, 0x36);
	CHECK_FIELD(sTradeItem, uccData, 0x37);
	CHECK_FIELD(sTradeItem, m_charCardSlotCount, 0x67);
	CHECK_FIELD(sTradeItem, m_caddieCardSlotCount, 0x69);
	CHECK_FIELD(sTradeItem, uccName, 0x6d);
	CHECK_FIELD(sTradeItem, uccCopierNick, 0x96);
END_LAYOUT_CHECK

// A stored item (KR sStoredItemInfo, KR size 0xae); JP size 0xb0 (the
// memset of FrItemCounter's constructor). KR defines the accessors in the
// class body; their JP copies are out of line in ItemStorage's object
// (0x7f8060-0x7f8090), which defines them.
struct sStoredItemInfo {
	void SetTypeID(unsigned long typeId);   // 0x7f8060
	void SetGuid(unsigned long guid);       // 0x7f8070
	unsigned long GetCount(void) const;     // 0x7f8080
	void SetCount(unsigned long count);     // 0x7f8090

	unsigned long slot;                     // 0x00
	sTradeItem item;                        // 0x04
};

CHECK_SIZE(sStoredItemInfo, 0xb0);
BEGIN_LAYOUT_CHECK(sStoredItemInfo)
	CHECK_FIELD(sStoredItemInfo, slot, 0x00);
	CHECK_FIELD(sStoredItemInfo, item, 0x04);
END_LAYOUT_CHECK

#pragma pack(pop)

#endif // PG_JP983_SHARED_GLOBALNETWORKDEFINE_H
