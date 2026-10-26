// The JP 983 chat motion table: the words that make a character play a
// motion when typed after a '/' in the chat (ChatManager::GetMotionName,
// JP 0x9a3990). The KR table (hatManager.cpp's data_00a9e9d8, static data)
// has 10 character types of 15 motions with Korean words; the JP one has 15
// character types of 19 motions, and its static initializer 0xce6b10 (in
// the CRT initializer table at 0xcfdb00) translates the Korean words
// through Jp_LookupText at start-up. The motion names stay the Korean
// animation names.
// From the JP exe's bodies (node scripts/disasm.ts --jp 0x<va>).
#ifndef PG_JP_JPMOTIONTABLE_H
#define PG_JP_JPMOTIONTABLE_H

#include "defines.h"

// One motion: the animation name and up to seven command words, laid out
// as hatManager.cpp's sMotionText (0x20 bytes).
struct sJpMotionText {
	const char* m_name;          // 0x00
	const char* m_command[7];    // 0x04
};
CHECK_SIZE(sJpMotionText, 0x20);

// 0xe2dd08: per character type (type & 0x3FFFFFF), 19 motions (0x260
// bytes a type); the unused motions are zero (memset by 0xce6b10).
enum { JP_MOTION_TYPE_COUNT = 15, JP_MOTION_COUNT = 19 };
extern sJpMotionText g_jpMotionTable[JP_MOTION_TYPE_COUNT][JP_MOTION_COUNT];

#endif
