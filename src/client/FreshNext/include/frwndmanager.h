// Original: client/Fresh/include/frwndmanager.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRWNDMANAGER_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRWNDMANAGER_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/Wangreal/include/wtypes.h"

class FrGraphicInterface;

// Fresh's window manager (KR frwndmanager.h): only the members JP bodies
// read, at their JP offsets: the GDI at 0x84 (JukeBoxDlg through
// Fresh::GetManager) and the mouse position at 0x18 (KR m_istate.mousePos,
// the same offset: m_istate 0x10 + mousePos 0x8; worker-reported from a JP
// call site, not re-verified). The FrInputState around it is not modelled.
class FrWndManager {
	LAYOUT_CHECK_FRIEND;
public:
	const WPoint& GetMousePos(void) const { return m_mousePos; }
	FrGraphicInterface* GetGDI(void) { return m_pGDI; }

private:
	PADDING(0x00, 0x18);
	WPoint m_mousePos;            // 0x18
	PADDING(0x20, 0x84);
	FrGraphicInterface* m_pGDI;   // 0x84
};

BEGIN_LAYOUT_CHECK(FrWndManager)
	CHECK_FIELD(FrWndManager, m_mousePos, 0x18);
	CHECK_FIELD(FrWndManager, m_pGDI, 0x84);
END_LAYOUT_CHECK

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRWNDMANAGER_H
