// Original: d:\build\custom\temp\code\client\projectg\mousecursor.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_MOUSECURSOR_H
#define PG_JP983_CLIENT_PROJECTG_MOUSECURSOR_H

#include "defines.h"
#include "padding.h"

class CMouseCursor;
class WRect;

// KR WSingleton<CMouseCursor>'s instance pointer; the JP exe has no symbol
// for it (0xe73e0c: `mov eax,ds:[0E73E0Ch]` before every access, e.g.
// CHoleCupInfo::Display 0x529ae0).
extern "C" CMouseCursor* data_e73e0c;

// The game's mouse cursor (KR CMouseCursor : WSingleton<CMouseCursor>). The
// base and most of the layout are not modelled; the enable flags other
// units write keep their KR offsets in JP: m_trainingOptionEnable 0xfd
// (cleared at 0x753674) and m_uiEnable[] at 0x100 (0x6ef290 sets [0],
// 0x74b4c0 writes [0] and [1]).
class CMouseCursor {
	LAYOUT_CHECK_FRIEND;
public:
	// KR WSingleton<CMouseCursor>::Instance().
	static CMouseCursor* Instance(void) { return data_e73e0c; }

	bool InArea(const WRect& rect);         // 0x891480

private:
	PADDING(0x000, 0x0fd);
public:
	bool m_trainingOptionEnable;            // 0xfd, cursor area 0x24
private:
	PADDING(0x0fe, 0x100);
public:
	bool m_uiEnable[6];                     // 0x100
};

BEGIN_LAYOUT_CHECK(CMouseCursor)
	CHECK_FIELD(CMouseCursor, m_trainingOptionEnable, 0xfd);
	CHECK_FIELD(CMouseCursor, m_uiEnable, 0x100);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_MOUSECURSOR_H
