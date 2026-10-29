// Original: d:\build\custom\temp\code\client\wangreal\include\wtypes.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_WANGREAL_INCLUDE_WTYPES_H
#define PG_JP983_CLIENT_WANGREAL_INCLUDE_WTYPES_H

// The name clashes with the Platform SDK's wtypes.h: include this one by its
// path from src/, #include "jp983/client/Wangreal/include/wtypes.h".

#include "defines.h"

// KR wtypes.h's inlines the JP exe emits out of line in exactly one unit:
// that unit defines the macro empty before its first include
// (docs/tough_problems/011).
#ifndef UCCDRAWDLG_WTYPES_INLINE
#define UCCDRAWDLG_WTYPES_INLINE inline
#endif

// Layouts from KR wtypes.h; JP-verified: WPoint x/y (UccCopyDlg, JukeBoxDlg
// FrListItem::pos), WRect x/y/w/h, its (x, y, w, h) template constructor and
// its member-wise copy constructor (UccCopyDlg, JukeBoxDlg), WPoint::operator-=
// and WRect::operator-(const WPoint&) (UccDrawDlg's out-of-line copies,
// 0x7e25e0 / 0x7e2600). The other members are KR copies.

typedef struct _WPOINT {
	float x;   // 0x0
	float y;   // 0x4
} WPOINT;
CHECK_SIZE(_WPOINT, 0x8);

typedef struct _WSIZE {
	float w;   // 0x0
	float h;   // 0x4
} WSIZE;
CHECK_SIZE(_WSIZE, 0x8);

typedef struct _WRECT {
	float x;   // 0x0
	float y;   // 0x4
	float w;   // 0x8
	float h;   // 0xc
} WRECT;
CHECK_SIZE(_WRECT, 0x10);

class WPoint : public _WPOINT {
public:
	WPoint(void) {}
	WPoint(float px, float py) { x = px; y = py; }
	WPoint(const WPoint& pt) { x = pt.x; y = pt.y; }

	void operator-=(const WPoint& pt);
	WPoint operator+(const WPoint& pt) const { return WPoint(pt.x + x, pt.y + y); }
	WPoint operator-(const WPoint& pt) const { return WPoint(x - pt.x, y - pt.y); }
};
CHECK_SIZE(WPoint, 0x8);

// 0x7e25e0 (UccDrawDlg's copy)
UCCDRAWDLG_WTYPES_INLINE void WPoint::operator-=(const WPoint& pt)
{
	x -= pt.x;
	y -= pt.y;
}

class WSize : public _WSIZE {
public:
	WSize(void) {}
	WSize(float sw, float sh) { w = sw; h = sh; }
};
CHECK_SIZE(WSize, 0x8);

class WRect : public _WRECT {
public:
	WRect(void) {}
	template <class TW, class TH> WRect(float rx, float ry, TW rw, TH rh) { x = rx; y = ry; w = (float)rw; h = (float)rh; }
	WRect(const WRect& rc) { x = rc.x; y = rc.y; w = rc.w; h = rc.h; }
	WRect(const _WRECT& rc) { x = rc.x; y = rc.y; w = rc.w; h = rc.h; }

	WRect operator-(const WPoint& pt) const;
	float Right(void) const { return w + x; }
	float Bottom(void) const { return h + y; }
};
CHECK_SIZE(WRect, 0x10);

// 0x7e2600 (UccDrawDlg's copy)
UCCDRAWDLG_WTYPES_INLINE WRect WRect::operator-(const WPoint& pt) const
{
	return WRect(x - pt.x, y - pt.y, w, h);
}

#endif // PG_JP983_CLIENT_WANGREAL_INCLUDE_WTYPES_H
