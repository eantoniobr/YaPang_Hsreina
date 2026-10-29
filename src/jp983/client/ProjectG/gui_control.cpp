// Original: d:\build\custom\temp\code\client\projectg\gui_control.cpp (JP 983 exe)
#include "gui_control.h"

#include "SoundManager.h"

// 0x74a880
bool CAuxMenuUI::OnChatFuncDlgResult(int ret, FrForm* pForm) {
	m_pChatFuncDlg = NULL;
	return true;
}

// 0x74a930
const sFRESH_MSGMAP* FrChatFuncDlg::GetMessageMap(void) const {
	return &FrChatFuncDlg::_MsgMap;
}

// 0x74a990
const WRTTI* FrChatFuncDlg::GetRTTI(void) const {
	return &m_RTTI;
}

// 0x74a9c0
bool FrChatFuncDlg::OnReportDlgResult(int ret, FrForm* pForm) {
	Close(1, true);

	m_pReportDlg = NULL;
	return true;
}

// 0x74a9e0
void FrChatFuncDlg::OnBtnCloseDlgUp(void) {
	Close(1, true);
}

// 0x74aa40
void CScreen::SetUnknown4D5(bool flag) {
	m_unknown4D5 = flag;
}

// 0x74aa50
bool CScreen::GetUnknown4D5(void) {
	return m_unknown4D5;
}

// 0x74aa60
void CScreenState250::Reset(void) {
	m_active = false;
}

// 0x74aa70: no reference found (calls or data).
void UnreferencedEmpty_0074aa70(void) {
}

// 0x74aa80: no reference found (calls or data).
void UnreferencedEmpty_0074aa80(void) {
}

// 0x74aa90: no reference found (calls or data).
void UnreferencedEmpty_0074aa90(void) {
}

// 0x74aaa0
void CScreenFlags260::Reset(void) {
	m_flags[0] = false;
	m_flags[1] = false;
	m_flags[2] = false;
	m_flags[3] = false;
}

// 0x74aab0
void CScreenFlags260::SetFirstFlag(bool flag) {
	m_flags[0] = flag;
}

// 0x74acf0
CRecoverPangyaShotEffect::~CRecoverPangyaShotEffect(void) {
}

// 0x74ad00
void CRecoverPangyaShotEffect::Reset(void) {
	m_active = false;
	m_time = 0.0f;
	m_frame = 1;
}

// 0x74ad20
CRecoverPangyaShotRingEffect::~CRecoverPangyaShotRingEffect(void) {
}

// 0x74ad30
void CRecoverPangyaShotRingEffect::Reset(void) {
	m_active = false;
	m_time = 0.0f;
	m_frame = 1;
}

// 0x74af80: no reference found (calls or data).
unsigned char UnreferencedMin_0074af80(unsigned char a, unsigned char b) {
	return a > b ? b : a;
}

// 0x74b5e0
CScreenState250::CScreenState250(void) {
	Reset();
}

// 0x74b5f0: no reference found (calls or data).
void UnreferencedEmpty_0074b5f0(void) {
}

// 0x74b600
CScreenFlags260::CScreenFlags260(void) {
	Reset();
}

// 0x74b6e0
CRecoverPangyaShotEffect::CRecoverPangyaShotEffect(void)
	: m_period(data_d05a2c)
	, m_frameCount(4) {
	Reset();
}

// 0x74b730
void CRecoverPangyaShotEffect::Process(float elapsed) {
	if (!m_active)
		return;

	m_time += elapsed;
	if (m_time < m_period)
		return;

	if (m_frame < m_frameCount) {
		m_time = 0.0f;
		++m_frame;
	}
	else {
		Reset();
	}
}

// 0x74b780
CRecoverPangyaShotRingEffect::CRecoverPangyaShotRingEffect(void)
	: m_period(data_d05a2c)
	, m_frameCount(4)
	, m_printFrame(4) {
	Reset();
}

// 0x74b7e0
void CRecoverPangyaShotRingEffect::Process(float elapsed) {
	if (!m_active)
		return;

	m_time += elapsed;
	if (m_time < m_period)
		return;

	m_time = 0.0f;
	if (m_frame < m_frameCount + m_printFrame) {
		++m_frame;
		if (m_frame == m_printFrame)
			data_f023f4->PlaySfx("luck_rainbow_print", NULL, 0, NULL, NULL, 0.5f, data_d00d90);
	}
	else {
		Reset();
	}
}

// 0x74e160
void CScreen::DrawLimitedTimeRule(void) {
	DrawLimitedTime();
}

// 0x7516a0
const WRTTI* CScreen::GetRTTI(void) const {
	return &m_RTTI;
}
