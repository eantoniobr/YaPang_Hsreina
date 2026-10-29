// Original: client/ProjectG/fx.cpp (JP 983 exe)
#include "jp983/client/ProjectG/fx.h"
#include "fxsequence.h"
#include "fxspray.h"
#include "wview.h"

// g_view: the scene's view (unnamed in the JP exe).
extern "C" WView* data_f023e8;

// 0x879040
void CFx::Display(void) {
	if (m_bActive) {
		m_fxBox.Display(data_f023e8);
	}
}

// 0x879060
CFxSequence* CFx::OpenSequence(const char* name, bool bOriginal) {
	CFxSequence* pSequence = m_fxBox.LoadSequence(name, bOriginal, 0);
	if (pSequence) {
		m_fxBox.AddSequence(pSequence);
	}

	return pSequence;
}

// 0x879090
void CFx::CloseSequence(CFxSequence* pSequence, bool bImmediate) {
	m_fxBox.DeleteSequence(pSequence, bImmediate);
}

// 0x8790a0
CFxSpray* CFx::OpenSpray(const char* name) {
	CFxSpray* pSpray = m_fxBox.LoadSpray(name, 0);
	if (pSpray) {
		m_fxBox.AddSpray(pSpray);
	}

	return pSpray;
}

// 0x8790d0
void CFx::CloseSpray(CFxSpray* pSpray) {
	m_fxBox.DeleteSpray(pSpray);
}

// 0x8790e0
void CFx::AddFxKeeper(sFxKeeper& keeper) {
	m_fxBox.AddFxKeeper(keeper);
}

// 0x8790f0
void CFx::EraseFxKeeper(CFxKeeper* pKeeper) {
	m_fxBox.EraseFxKeeper(pKeeper);
}

// 0x879100
void CFx::ClearFxKeeper(void) {
	m_fxBox.ClearFxKeeper();
}

// 0x8791d0
void CFx::SetActive(bool bActive) {
	m_bActive = bActive;
}

// 0x879570
CFxPowerSpin::~CFxPowerSpin(void) {
}

// 0x879580
CFxShotImpact::~CFxShotImpact(void) {
}

// 0x879590
CFxClubImpact::~CFxClubImpact(void) {
}

// 0x8795a0
bool CFxClubImpact::Process(float fDelta) {
	return false;
}

// 0x8796d0
CFxPowerShot2::CFxPowerShot2(CPvsFxBox& box, CGolfBall& ball) : m_box(box), m_ball(ball) {
	m_serial = data_e7d5c0++;

	m_bDone = false;
}

// 0x879700
CFxPowerShot2::~CFxPowerShot2(void) {
}

// 0x87caa0
void CFx::Process(float fDelta) {
	if (!m_bActive) {
		return;
	}

	m_fxBox.ProcessAttacher(fDelta);

	std::map<int, CFxControl*>::iterator it = m_controls.begin();
	while (it != m_controls.end()) {
		CFxControl* pControl = it->second;

		if (!pControl->Process(fDelta)) {
			m_controls.erase(it++);
			delete pControl;
		} else {
			++it;
		}
	}

	m_fxBox.Process(fDelta * 1000.0f);
}

// 0x87cbd0
CFxSpray* CFx::GetSpray(int index) {
	return m_fxBox.GetSpray(index);
}

// 0x87e4c0
void CFx::ClearAll(bool bKeepActive) {
	ClearControl();
	m_fxBox.ClearAll(bKeepActive);
}
