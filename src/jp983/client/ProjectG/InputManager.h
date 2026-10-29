// Original: d:\build\custom\temp\code\client\projectg\inputmanager.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_INPUTMANAGER_H
#define PG_JP983_CLIENT_PROJECTG_INPUTMANAGER_H

#include "defines.h"

// The mouse buttons (KR InputManager.h, a global enum). LEFT and RIGHT trade
// places when the buttons are swapped.
PG_ENUM_DEF(eButton)
	LEFT_BUTTON,                   // 0
	RIGHT_BUTTON,                  // 1
	MIDDLE_BUTTON                  // 2
};

class CInputManager;

// KR g_input (WSingleton<CInputManager>'s instance pointer); the JP exe has
// no symbol for it (0xf00510: `mov ecx,ds:[0F00510h]` before every
// CInputManager call, e.g. sub_490430).
extern "C" CInputManager* data_f00510;

// The game's input (key binding) manager (KR CInputManager :
// WSingleton<CInputManager>). The base and the layout are not modelled; only
// the members the JP units call are declared, KR signatures at the JP
// addresses. GetButton 0x9a63f0 is KR's body (m_active 0xe8, m_swapButton
// 0xe9, m_button[3] at 0x64 of 0x28 bytes: KR offsets).
class CInputManager {
public:
	// KR WSingleton<CInputManager>::Instance() / g_input.
	static CInputManager* Instance(void) { return data_f00510; }

	int GetButton(eButton button);                  // 0x9a63f0
	int Get(const char* key, bool consume);         // 0x9a6c50
	int GetDown(const char* key, bool consume);     // 0x9a6ce0
};

#endif // PG_JP983_CLIENT_PROJECTG_INPUTMANAGER_H
