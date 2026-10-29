// Original: client/Fresh/include/frarea.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRAREA_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRAREA_H

#include "client/FreshNext/include/frwnd.h"

class Bitmap;

// A Fresh area (KR frarea.h, FrArea : FrWnd): only what JP bodies call.
// m_RTTI: its initializer 0xcf7850 builds ("FrArea", &FrWnd::m_RTTI) there.
class FrArea : public FrWnd {
public:
	static const WRTTI m_RTTI;              // 0xf1aad4

	bool SetBgImg(const Bitmap* pBitmap);   // 0xbea420
};

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRAREA_H
