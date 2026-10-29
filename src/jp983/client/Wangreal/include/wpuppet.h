// Original: client/Wangreal/include/wpuppet.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_WANGREAL_INCLUDE_WPUPPET_H
#define PG_JP983_CLIENT_WANGREAL_INCLUDE_WPUPPET_H

#include "defines.h"
#include "padding.h"
#include "wmath.h"

class WBone;
class WView;

// KR layout (PDB), size 0x24; JP reads only s and e so far.
struct w_motion_data {
	float s;            // 0x0
	float e;            // 0x4
	float end;          // 0x8
	int option1;        // 0xc
	float option2;      // 0x10
	char* applybone;    // 0x14
	char* name;         // 0x18
	char* nextmotion;   // 0x1c
	char ptr[1];        // 0x20
};
CHECK_SIZE(w_motion_data, 0x24);
CHECK_FIELD(w_motion_data, s, 0x0);
CHECK_FIELD(w_motion_data, e, 0x4);

// Wangreal's puppet (JP 983): only the members the jp983 units use. The
// layout is known only as far as m_mat (0x94, as in KR).
class WPuppet {
	LAYOUT_CHECK_FRIEND;
public:
	void Transform(WView* view, float alpha, int flag);             // 0xb698d0
	void UpdateBSphere();                                            // 0xb69c50
	WBone* FindBoneByTail(const char* name);                         // 0xb69ac0
	w_motion_data* FindMotionData(const char* name);                 // 0xb73670
	WVector GetDeltaVec(char* animName, float from, float to);       // 0xb738c0
	WVector GetPivot(const char* boneName);                          // 0xb785b0
	// JP replacement of KR's ApplyBones(GetBones(name, time, loop, bone,
	// optimize), matrix): samples the motion and applies it to the bones with
	// the matrix SetMatrix stored. The first argument is new in JP.
	void* AnimateBones(void* unknown, const char* name, float time, int loop, char* bone, bool optimize);   // 0xb86c10
	WMatrix& GetMatrix() { return m_mat; }
	// Not in KR (inline or new in JP; 0x4d18f0, out of line).
	void SetMatrix(const WMatrix& mat);                              // 0x4d18f0

private:
	PADDING(0x0, 0x94);    // not modelled yet
	WMatrix m_mat;          // 0x94
};
BEGIN_LAYOUT_CHECK(WPuppet)
	CHECK_FIELD(WPuppet, m_mat, 0x94);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_WANGREAL_INCLUDE_WPUPPET_H
