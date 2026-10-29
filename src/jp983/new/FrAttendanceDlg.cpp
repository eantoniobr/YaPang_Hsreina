// Original: unknown, JP-only RTTI class FrAttendanceDlg (JP 983 exe)
#include "FrAttendanceDlg.h"

// 0x47c9f0
const WRTTI* FrAttendanceDlg::GetRTTI(void) const {
	return &m_RTTI;
}

// 0x47ccf0
void FrAttendanceDlg::OnResize(void) {
}

// 0x47cd00
bool FrAttendanceDlg::OnRButtonUp(const WPoint& pt) {
	return false;
}

// 0x47cd10
bool FrAttendanceDlg::OnRButtonDown(const WPoint& pt) {
	return false;
}

// 0x47cd20
void FrAttendanceDlg::OnDblClick(const WPoint& pt) {
}

// 0x47cd30
void FrAttendanceDlg::OnWheel(FrInputState& input) {
}

// 0x47cd40
const char* FrAttendanceDlg::OnSelectText(const FrInputState* pInput) {
	return 0;
}

// 0x47cd50
void FrAttendanceDlg::OnKeyFocus(CChatMsg* pMsg) {
}

// 0x47cd60
void FrAttendanceDlg::EnableKeyFocus(FrInputState& input) {
	m_nFlags |= 0x10;
}
