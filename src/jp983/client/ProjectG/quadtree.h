// Original: d:\build\custom\temp\code\client\projectg\quadtree.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_QUADTREE_H
#define PG_JP983_CLIENT_PROJECTG_QUADTREE_H

#include "defines.h"
#include "wmath.h"

// The blend mode of a decal's polygons (DrawDecal).
enum enumPolyBlend {
	W_POLY_BLEND_NORMAL = 0,
	W_POLY_BLEND_ADD = 0x800000,
	W_POLY_BLEND_MULTIPLY = 0x1000000,
	W_POLY_BLEND_INVMULTIPLY = 0x1800000,
	W_POLY_BLEND_FORCE_DWORD = 0x7fffffff
};

// The course's quad tree (KR quadtree.h). Only the members the JP units call
// are declared; the layout is not modelled.
class CQuadTree {
public:
	WVector GetGroundPoint(WVector, bool, int *, bool);     // 0x94f660
	void DrawDecal(int texture, const WVector &pos, const WVector &normal, const WVector &tangent, float size, float alpha, enumPolyBlend blend, bool bAll);     // 0x957340
};

CQuadTree &GetPVS(void);     // 0x965250

#endif // PG_JP983_CLIENT_PROJECTG_QUADTREE_H
