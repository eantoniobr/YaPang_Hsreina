// Original: d:\build\custom\temp\code\client\projectg\fxsequence.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_FXSEQUENCE_H
#define PG_JP983_CLIENT_PROJECTG_FXSEQUENCE_H

#include <map>

#include "defines.h"
#include "padding.h"
#include "wmath.h"

class CFxSpray;

// A running effect sequence (RTTI .?AVCFxSequence@@, vtable 0xd3d2c4, one
// slot: the scalar deleting destructor 0x976b20, destructor 0x9757d0). Only
// the members the JP code uses are declared, at their JP offsets: m_sprays
// from the destructor; m_bActive, m_pos and m_delay from the inlined
// SetActive, Pos and SetDelay of CGuideLine::SetPoint (0x75b700) and
// CExtendedEffect::Update (0x6de650). From m_bActive on, the JP fields sit
// 4 bytes after their KR offsets (VS 2010 std::map is 0x10 bytes, KR 0xC).
class CFxSequence {
	LAYOUT_CHECK_FRIEND;
public:
	virtual ~CFxSequence(void);                               // 0

	void SetActive(bool bActive, bool bChildren);
	WVector& Pos(void);
	std::map<CFxSpray*, CFxSpray*>& GetSprayList(void);
	void SetDelay(float delay);

	UNKNOWN(0x4, 0x20);
	std::map<CFxSpray*, CFxSpray*> m_sprays;   // 0x20, GetSprayList
	UNKNOWN(0x30, 0x1108);
	bool m_bActive;                 // 0x1108, SetActive
	PADDING(0x1109, 0x110C);
	WVector m_pos;                  // 0x110C, Pos
	UNKNOWN(0x1118, 0x112C);
	float m_delay;                  // 0x112C, seconds before the sequence starts
	UNKNOWN(0x1130, 0x1244);
	// 0x1244: the script lines (std::list), 0x1254: the name (std::string).
};

BEGIN_LAYOUT_CHECK(CFxSequence)
	CHECK_FIELD(CFxSequence, m_sprays, 0x20);
	CHECK_FIELD(CFxSequence, m_bActive, 0x1108);
	CHECK_FIELD(CFxSequence, m_pos, 0x110C);
	CHECK_FIELD(CFxSequence, m_delay, 0x112C);
END_LAYOUT_CHECK

#include "fxsequence.inl"

#endif // PG_JP983_CLIENT_PROJECTG_FXSEQUENCE_H
