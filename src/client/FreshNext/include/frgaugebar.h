// Original: client/Fresh/include/frgaugebar.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRGAUGEBAR_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRGAUGEBAR_H

#include "client/FreshNext/include/frwnd.h"

// A Fresh gauge bar (KR frgaugebar.h, FrGaugeBar : FrWnd): only what JP
// bodies call. m_RTTI: its initializer 0xcf7ca0 builds ("FrGaugeBar",
// &FrWnd::m_RTTI) there.
class FrGaugeBar : public FrWnd {
public:
	static const WRTTI m_RTTI;                          // 0xf1ab88

	void SetRange(int lower, int upper, int origin);   // 0xc02c20
};

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRGAUGEBAR_H
