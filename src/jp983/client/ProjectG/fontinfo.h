// Original: d:\build\custom\temp\code\client\projectg\fontinfo.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_FONTINFO_H
#define PG_JP983_CLIENT_PROJECTG_FONTINFO_H

#include "defines.h"

// The base of the on-screen info panels. Only the vtable slots up to the
// ones the JP unit defines are declared (KR order, the RTTI names the class
// of slot 2); the JP layout is not modelled yet.
class CFontInfo {
public:
	virtual ~CFontInfo();                   // 0
	virtual void Process(float fDelta);     // 1
	virtual void Display(void);             // 2 (0x5272c0, empty)
};

// A float wrapped in a small JP-only type: CCalipers holds two of them
// (0x52c, the cursor position, and 0x530) and reads them through Get()
// (0x526e40, not inlined) and copies them with an assignment (0x526e50).
// Its real name is unknown.
struct WrappedFloat {
	float m_value;  // 0x0

	float &Get(void);
};

CHECK_SIZE(WrappedFloat, 0x4);

#endif // PG_JP983_CLIENT_PROJECTG_FONTINFO_H
