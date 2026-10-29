// Original: d:\build\custom\temp\code\client\projectg\fxspray.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_FXSPRAY_H
#define PG_JP983_CLIENT_PROJECTG_FXSPRAY_H

#include "defines.h"
#include "padding.h"
#include "wmath.h"

// A particle emitter (RTTI .?AVCFxSpray@@, vtable 0xd3d3cc, one slot: the
// scalar deleting destructor 0x986850). Only the members the JP callers use
// are declared; m_pos is at its KR offset in the JP code (CFx callers).
class CFxSpray {
	LAYOUT_CHECK_FRIEND;
public:
	virtual ~CFxSpray(void);                                  // 0

	void SetActive(bool bActive);   // KR fxspray.inl:63; JP field not verified, declared only
	WVector& Pos(void);

	UNKNOWN(0x4, 0x1138);
	WVector m_pos;                  // 0x1138, Pos
};

BEGIN_LAYOUT_CHECK(CFxSpray)
	CHECK_FIELD(CFxSpray, m_pos, 0x1138);
END_LAYOUT_CHECK

#include "fxspray.inl"

#endif // PG_JP983_CLIENT_PROJECTG_FXSPRAY_H
