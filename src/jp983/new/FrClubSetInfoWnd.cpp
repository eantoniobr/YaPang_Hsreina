// Original: unknown, JP-only RTTI class FrClubSetInfoWnd (JP 983 exe)
#include "FrClubSetInfoWnd.h"

// The real constructor and destructor (0x4be7e0) are elsewhere; this empty
// one only makes the vtables and the scalar deleting destructor emitted.
FrClubSetInfoWnd::FrClubSetInfoWnd(void) {
}

// 0x4bd8e0
bool FrClubSetInfoWnd::IsReady(void) {
	return true;
}

// 0x4bd8f0
void FrClubSetInfoWnd::OnUpdate(float dt) {
	if (m_nWorking == 0) {
		if (m_pPending != 0 && *m_pPending != 0) {
			if (!m_bBlinkOn) {
				m_bBlinkOn = true;
				SetEntryFlag(m_nBlinkEntry, true);
			}
			return;
		}
		m_fBlinkTime += dt;
		if (m_fBlinkTime > 0.5f) {
			SetEntryFlag(m_nBlinkEntry, m_bBlinkOn);
			m_fBlinkTime = 0.0f;
			m_bBlinkOn = !m_bBlinkOn;
		}
	} else if (m_bBlinkOn) {
		m_bBlinkOn = false;
		SetEntryFlag(m_nBlinkEntry, false);
	}
}

// 0x4bd9b0
void FrClubSetInfoWnd::SetChildrenEnable(bool bEnable) {
	ClubSetWorkshopChildWndBase::SetChildrenEnable(bEnable);
}
