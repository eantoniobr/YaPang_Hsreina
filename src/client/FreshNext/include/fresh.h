// Original: client/Fresh/include/fresh.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRESH_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRESH_H

#include "defines.h"
#include "padding.h"

class Bitmap;
class FrWndManager;

// The Fresh library's root object (KR fresh.h). Only the members JP bodies
// call; m_pWndManager is at 0x40 in JP (KR 0x3c), read by JukeBoxDlg.
class Fresh {
	LAYOUT_CHECK_FRIEND;
public:
	const Bitmap* RegisterBitmap(const char* bitmap);   // 0xbe9b70
	const Bitmap* GetBitmap(const char* bitmap);        // 0xbe9b90
	FrWndManager* GetManager(void) const { return m_pWndManager; }

private:
	PADDING(0x00, 0x40);
	FrWndManager* m_pWndManager;   // 0x40
};

BEGIN_LAYOUT_CHECK(Fresh)
	CHECK_FIELD(Fresh, m_pWndManager, 0x40);
END_LAYOUT_CHECK

// KR g_pFresh: the pointer at 0xf022d0 (no symbol in the JP exe).
extern "C" Fresh* data_f022d0;

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRESH_H
