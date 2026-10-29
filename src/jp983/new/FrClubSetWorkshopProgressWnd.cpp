// Original: unknown, JP-only RTTI class FrClubSetWorkshopProgressWnd (JP 983 exe)
#include "FrClubSetWorkshopProgressWnd.h"

// 0x49eaa0 (the split places it in client/ProjectG/GolfDoc)
FrClubSetWorkshopProgressWnd::~FrClubSetWorkshopProgressWnd(void) {
	data_00e74218 = 0;
	if (m_pHelper) {
		delete m_pHelper;
		m_pHelper = 0;
	}
}

// 0x49eb90
void ClubSetWorkshopChildWndBase::OnChildEvent(int nEvent) {
}

// 0x49eba0
void ClubSetWorkshopChildWndBase::OnChildUpdate(void) {
}

// 0x49ebb0
void ClubSetWorkshopChildWndBase::OnChildNotify(int nNotify) {
}

// 0x49ebc0
void ClubSetWorkshopChildWndBase::OnChildRefresh(void) {
}

// 0x4ca6c0
void ClubSetWorkshopChildWndBase::OnBeginWork(void) {
	if (data_00e74c68)
		data_00e74c68->DisableTabButtons();
}

// 0x4ca6d0
void ClubSetWorkshopChildWndBase::OnEndWork(void) {
	if (data_00e74c68)
		data_00e74c68->EnableTabButtons();
}
