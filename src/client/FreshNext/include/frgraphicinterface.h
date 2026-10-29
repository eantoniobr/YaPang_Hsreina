// Original: client/Fresh/include/frgraphicinterface.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRGRAPHICINTERFACE_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRGRAPHICINTERFACE_H

#include "defines.h"

class Bitmap;
class WPoint;
class WRect;

// Fresh's drawing interface (KR frgraphicinterface.h): only the members JP
// bodies call, KR signatures, JP addresses. Layout not modelled.
class FrGraphicInterface {
public:
	void DrawTexture(const Bitmap* pBitmap, const WRect& dest, unsigned long diffuse, int type) const;   // 0xbec640
	void SetTextColor(unsigned long color, unsigned long outlineColor);                              // 0xbec440
	void SetTextStyle(unsigned long textStyle);                                                      // 0xbec460
	float PrintText(const WPoint& pos, unsigned long align, const char* text, Bitmap* pBitmap);       // 0xbec860
};

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRGRAPHICINTERFACE_H
