// Original: client/ProjectG/GolfDoc.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_GOLFDOC_H
#define PG_JP983_CLIENT_PROJECTG_GOLFDOC_H

#include "defines.h"
#include "padding.h"

// A player of the round (KR GolfDoc.h). Only the members the JP units read
// are declared, at their JP offsets (KR +0x10); the size is not known yet.
struct sPlayerData {
	PADDING(0x000, 0x4db);
	unsigned char m_numTimeout; // 0x4db (KR 0x4cb), the shots the player let the clock run out
};

BEGIN_LAYOUT_CHECK(sPlayerData)
	CHECK_FIELD(sPlayerData, m_numTimeout, 0x4db);
END_LAYOUT_CHECK

// The golf document (KR CGolfDoc : CTaskDoc). The base and the rest of the
// layout are not modelled; only the members the JP units use are declared.
class CGolfDoc {
public:
	struct sPlayerData *GetPlayer(unsigned char index); // 0x663800

	PADDING(0x000, 0x088);
	int m_gameState;               // 0x088 (KR 0x78), the round progress (guideline 0x75b436 tests >= 15)
	PADDING(0x08c, 0x0d5);
	unsigned char m_playerNum;     // 0x0d5 (KR 0xc5)
	PADDING(0x0d6, 0x158);
	unsigned long m_gameMode;      // 0x158 (KR 0x148), flag bits (tested with 0x23001)
	PADDING(0x15c, 0x189);
	unsigned char m_myPlayerIndex; // 0x189 (KR 0x175), this client's player
};

BEGIN_LAYOUT_CHECK(CGolfDoc)
	CHECK_FIELD(CGolfDoc, m_gameState, 0x088);
	CHECK_FIELD(CGolfDoc, m_playerNum, 0x0d5);
	CHECK_FIELD(CGolfDoc, m_gameMode, 0x158);
	CHECK_FIELD(CGolfDoc, m_myPlayerIndex, 0x189);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_GOLFDOC_H
