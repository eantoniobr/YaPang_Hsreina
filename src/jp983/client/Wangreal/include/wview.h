// Original: d:\build\custom\temp\code\client\wangreal\include\wview.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_WANGREAL_INCLUDE_WVIEW_H
#define PG_JP983_CLIENT_WANGREAL_INCLUDE_WVIEW_H

#include "defines.h"
#include "padding.h"

// The camera and viewport of a scene (KR wview.h). Only the members the JP
// units read are declared, at their JP offsets; the vtable pointer (KR:
// WResource base and virtual members) is inside the first PADDING.
class WView {
	LAYOUT_CHECK_FRIEND;
public:
	enum PROJECTION_MODE {
		PERSPECTIVE = 0,
		PARALLEL = 1,
		NUM_PROJECTION_MODE = 2
	};

	float GetClipFarValue(void) const { return clip_far; }
	float GetScale(void) const { return m_scale; }
	PROJECTION_MODE GetProjectionMode(void) const { return m_projMode; }

private:
	PADDING(0x0, 0x190);
	float clip_far;              // 0x190
	PADDING(0x194, 0x1AB4);
	PROJECTION_MODE m_projMode;  // 0x1ab4
	float m_scale;               // 0x1ab8
};
BEGIN_LAYOUT_CHECK(WView)
	CHECK_FIELD(WView, clip_far, 0x190);
	CHECK_FIELD(WView, m_projMode, 0x1AB4);
	CHECK_FIELD(WView, m_scale, 0x1AB8);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_WANGREAL_INCLUDE_WVIEW_H
