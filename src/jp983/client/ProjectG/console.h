// Original: client/ProjectG/console.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_CONSOLE_H
#define PG_JP983_CLIENT_PROJECTG_CONSOLE_H

#include "defines.h"
#include "padding.h"

// The in-game developer console (RTTI .?AVCConsole@@, bases
// WSingleton<CConsole> and BaseObject; vtable 0xd1f394, one slot: the
// scalar deleting destructor). Only what the bodies of console.cpp need is
// declared: the bases and the JP layout are not modelled yet.
class CConsole {
public:
	static void Print(const char *text);

	CConsole(void);
	virtual ~CConsole(void);

protected:
	void AddText(const char *text);
};

// WSingleton<CConsole>::m_pInstance (no symbol in the JP exe).
extern "C" CConsole *data_e79ee8;

#endif
