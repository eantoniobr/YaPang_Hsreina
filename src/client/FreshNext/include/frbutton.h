// Original: client/Fresh/include/frbutton.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRBUTTON_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRBUTTON_H

#include "client/FreshNext/include/frwnd.h"

// A Fresh button (KR frbutton.h, FrButton : FrWnd): only what JP bodies call.
// m_RTTI: its initializer 0xcf7980 builds ("FrButton", &FrWnd::m_RTTI) there.
class FrButton : public FrWnd {
public:
	enum eButMode {
		NORMAL = 0,
		OVER = 1,
		PRESSED = 2,
		BLINK = 3
	};

	static const WRTTI m_RTTI;                            // 0xf1ab38

	void SetButtonImg(const char* name, eButMode mode);   // 0xbf5710
	void SetStatus(eButMode status);                      // 0xbf4fb0
	// KR frbutton.h:49. JP callers pass a constant, which cl folds: e.g.
	// FrItemStorageAccessPanel::OnInitNumberSlot0 0x7fa7bd stores 0.1f
	// (data_d05a2c) to 0x104 and 0.2f (data_d097cc) to 0x108.
	void SetPushDelay(float delay) {
		m_pushDelay = delay;
		m_pushedTime = delay + 0.1f;
	}

protected:
	PADDING(0x044, 0x104);
	float m_pushDelay;                                    // 0x104 (KR 0x108)
	float m_pushedTime;                                   // 0x108 (KR 0x10c)

	LAYOUT_CHECK_FRIEND;
};

BEGIN_LAYOUT_CHECK(FrButton)
	CHECK_FIELD(FrButton, m_pushDelay, 0x104);
	CHECK_FIELD(FrButton, m_pushedTime, 0x108);
END_LAYOUT_CHECK

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRBUTTON_H
