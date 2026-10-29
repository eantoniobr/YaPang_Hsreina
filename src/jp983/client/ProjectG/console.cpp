// Original: client/ProjectG/console.cpp (JP 983 exe)
#include "jp983/client/ProjectG/console.h"

// 0x71e6d0
// KR: an inline of console.h (CConsole::Print); the JP exe emits it out of
// line. Instance pointer: WSingleton<CConsole>::m_pInstance.
void CConsole::Print(const char *text) {
	if (data_e79ee8 != 0) {
		data_e79ee8->AddText(text);
	}
}

// The real constructor and destructor (0x71cd40) are compiled elsewhere in
// this unit; this empty constructor only makes the compiler emit the vtable
// and the scalar deleting destructor (0x71e6f0).
CConsole::CConsole(void) {
}
