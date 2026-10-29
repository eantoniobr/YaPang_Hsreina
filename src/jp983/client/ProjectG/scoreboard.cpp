// Original: client/ProjectG/scoreboard.cpp (JP 983 exe)
#include "scoreboard.h"

// 0x77bae0
void FrRankForm3::SetScore(int score, int remain) {
	m_score = score;
	m_scoreRemain = remain;

	int pos = score + 1;

	m_pScoreGauge->SetRange(0, pos + remain + 1, pos);
}

// 0x77bb10
const sFRESH_MSGMAP* FrRankFormEx::GetMessageMap(void) const {
	return &FrRankFormEx::_MsgMap;
}

// 0x77bb50: a lone `ret`. Nothing in the readable code of the exe calls or
// references it (no call, no vtable slot, no function pointer), so its class
// and name are unknown.
void UnreferencedEmpty_0077bb50(void) {
}

// 0x77bcd0
const WRTTI* FrRankFormEx::GetRTTI(void) const {
	return &m_RTTI;
}

// 0x77c090
const sFRESH_MSGMAP* FrAwardForm::GetMessageMap(void) const {
	return &FrAwardForm::_MsgMap;
}

// 0x77c240
const WRTTI* FrAwardForm::GetRTTI(void) const {
	return &m_RTTI;
}

// 0x77c2d0
void cAquireItem::OnProc(float dt) {
	if (m_value < m_maxValue) {
		m_value += dt * 20.0;
	}
}

// 0x77c310
const sFRESH_MSGMAP* FrScoreForm::GetMessageMap(void) const {
	return &FrScoreForm::_MsgMap;
}

// 0x77c3f0
void FrScoreForm::SetTypeBtn(void) {
	m_typeTime = 0.0f;

	for (int i = 0; i < 6; i++) {
		if (m_pTypeBtn[i]) {
			m_pTypeBtn[i]->SetStatus(m_scoreType == i ? FrButton::PRESSED : FrButton::NORMAL);
		}
	}
}

// 0x77c4f0
const sFRESH_MSGMAP* FrMatchItems::GetMessageMap(void) const {
	return &FrMatchItems::_MsgMap;
}

// 0x77c500
const sFRESH_MSGMAP* CScore::GetMessageMap(void) const {
	return &CScore::_MsgMap;
}

// 0x77d4c0: a lone `ret`, unreferenced like 0x77bb50.
void UnreferencedEmpty_0077d4c0(void) {
}

// 0x781530
const WRTTI* FrRankForm::GetRTTI(void) const {
	return &m_RTTI;
}

// 0x785220
const WRTTI* FrRankForm3::GetRTTI(void) const {
	return &m_RTTI;
}

// 0x788d70
void FrScoreForm::ChangeTurn(void) {
	UpdatePang();
}

// 0x78b3a0
const WRTTI* FrMatchItems::GetRTTI(void) const {
	return &m_RTTI;
}

// 0x791400
const WRTTI* FrScoreForm::GetRTTI(void) const {
	return &m_RTTI;
}

// 0x792730
void CRankExData::OnProc(float dt) {
	m_motionTime += dt;

	if (m_leader == -1) {
		SetLeader();
	} else if (m_showLeader != -1) {
		ShowLeader();
	} else if (m_pExhibition) {
		m_pExhibition->Process(dt, false);
	}
}

// 0x792780
void CRankExData::SetActive(bool bActive) {
	m_showLeader = -1;
	m_leader = -1;
	m_motionLength = 3.0f;
	m_motionTime = 0;
	if (bActive) {
		SetLeader();
	}
}

// 0x7927b0
void FrRankFormEx::SetActive(bool bActive) {
	m_rankEx.SetActive(bActive);
	Enable(bActive);
	SetVisible(bActive);
}

// 0x79a020
const WRTTI* CScore::GetRTTI(void) const {
	return &m_RTTI;
}
