// Original: d:\build\custom\temp\code\client\projectg\golfball.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_GOLFBALL_H
#define PG_JP983_CLIENT_PROJECTG_GOLFBALL_H

#include "defines.h"
#include "padding.h"

// The golf ball (KR golfball.h). Only the members the JP units read are
// declared; the singleton GolfBall() is at 0xe47dc0 (guard 0xe73dc4,
// constructor 0x6b1030), m_preDataIndex at 0xe47e28.
class CGolfBall {
	LAYOUT_CHECK_FRIEND;
public:
	CGolfBall(void);     // 0x6b1030
	~CGolfBall(void);

	UNKNOWN(0x0, 0x59);
	unsigned char m_groundType;  // 0x59 (KR 0x59), ground type at the ball (guideline 0x75b478 compares 2)
	UNKNOWN(0x5a, 0x64);
	int m_preDataCount;     // 0x64, last valid index of PreData, negative when none
	int m_preDataIndex;     // 0x68, the PreData index of the ball's current point
};
BEGIN_LAYOUT_CHECK(CGolfBall)
	CHECK_FIELD(CGolfBall, m_groundType, 0x59);
	CHECK_FIELD(CGolfBall, m_preDataCount, 0x64);
	CHECK_FIELD(CGolfBall, m_preDataIndex, 0x68);
END_LAYOUT_CHECK

// golfball.inl: the ball singleton.
inline CGolfBall &GolfBall(void) {
	static CGolfBall me;
	return me;
}

#endif // PG_JP983_CLIENT_PROJECTG_GOLFBALL_H
