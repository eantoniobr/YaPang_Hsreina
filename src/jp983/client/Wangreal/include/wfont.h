// Original: d:\build\custom\temp\code\client\wangreal\include\wfont.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_WANGREAL_INCLUDE_WFONT_H
#define PG_JP983_CLIENT_WANGREAL_INCLUDE_WFONT_H

#include "defines.h"

// Description of a bitmap title font (KR wfont.h). JP-verified size: Create
// 0xb5fe00 copies it with `rep movsd` of 8 dwords and reads pCharSet (0x1c).
struct tagWTITLEFONT {
	char** filename;    // 0x0
	int numPages;       // 0x4
	int fontw;          // 0x8
	int fonth;          // 0xc
	int texw;           // 0x10
	int texh;           // 0x14
	int flag;           // 0x18
	char* pCharSet;     // 0x1c
};

CHECK_SIZE(tagWTITLEFONT, 0x20);
BEGIN_LAYOUT_CHECK(tagWTITLEFONT)
	CHECK_FIELD(tagWTITLEFONT, numPages, 0x4);
	CHECK_FIELD(tagWTITLEFONT, fontw, 0x8);
	CHECK_FIELD(tagWTITLEFONT, fonth, 0xc);
	CHECK_FIELD(tagWTITLEFONT, texw, 0x10);
	CHECK_FIELD(tagWTITLEFONT, texh, 0x14);
	CHECK_FIELD(tagWTITLEFONT, flag, 0x18);
	CHECK_FIELD(tagWTITLEFONT, pCharSet, 0x1c);
END_LAYOUT_CHECK

// The title font (KR wfont.h, WTitleFont : WFont): only the members JP
// bodies call; bases, vtable and layout not modelled (Create copies the
// description to +0xb0, after KR WFont's 0xb0 bytes).
class WTitleFont {
public:
	void Erase(void);                        // 0xb5dec0
	void Create(tagWTITLEFONT* desc);        // 0xb5fe00
};

#endif // PG_JP983_CLIENT_WANGREAL_INCLUDE_WFONT_H
