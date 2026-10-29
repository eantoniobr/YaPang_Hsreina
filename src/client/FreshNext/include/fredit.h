// Original: client/Fresh/include/fredit.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FREDIT_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FREDIT_H

#include "client/FreshNext/include/frwnd.h"

// A Fresh edit box (KR fredit.h, FrEdit : FrWnd): only what JP bodies call,
// KR signatures at the JP addresses the split pairs them with. m_RTTI: its
// initializer 0xcf7a00 builds ("FrEdit", &FrWnd::m_RTTI) there. Layout not
// modelled.
class FrEdit : public FrWnd {
public:
	static const WRTTI m_RTTI;                                                         // 0xf1ab50

	const char* AddLine(const char* text, unsigned long color, bool marginAlign);      // 0xbfac70
	const char* GetLine(int line, bool makeNewLine);                                   // 0xbfb050
	int GetLineNum(void);                                                              // 0xbf79f0
	void ClearLine(void);                                                              // 0xbf8b00
	void SetCharLimit(int limit, bool getMinValue);                                    // 0xbf7a90
};

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FREDIT_H
