// Original: d:\build\custom\temp\code\client\projectg\ghostgamedlg.cpp (JP 983 exe)
#include <string.h>

#include "GhostGameDlg.h"

#include "client/FreshNext/include/frgraphicinterface.h"
#include "jp983/client/Wangreal/include/wfont.h"
#include "jp983/client/Wangreal/include/wresrcmng.h"

// The title fonts' texture file name tables (char* tables in .data, no
// symbol): FrRecentMatch's and FrGhostAward's.
extern "C" char* data_e1ece0[];
extern "C" char* data_e1ed00[];

// 0x818a20
const sFRESH_MSGMAP* FrRecentMatch::GetMessageMap(void) const
{
	return &FrRecentMatch::_MsgMap;
}

// 0x818aa0
const sFRESH_MSGMAP* FrGhostGameMapDlg::GetMessageMap(void) const
{
	return &FrGhostGameMapDlg::_MsgMap;
}

// 0x818b90
void FrGhostGameMapDlg::sImgTag::Reset(void)
{
	m_alphaEnd = 0.0f;
	m_alpha = 0.0f;
	m_current = 800.0f;
}

// 0x818bb0
void FrGhostGameMapDlg::sImgInfo::AnimateLock(float dt)
{
	if (m_flag12) {
		if (!m_flag10) {
			if (m_lockOffset < 200.0f) {
				m_lockOffset += dt * 200.0f * 2.0f;
				if (m_lockOffset > 200.0f)
					m_lockOffset = 200.0f;
			}
		}
	}
}

// 0x818c10 (no reference found; the message maps' entries are zero in the
// file, so it may be an empty handler)
void UnreferencedEmpty_00818c10(void)
{
}

// 0x818f50
const sFRESH_MSGMAP* FrGhostAward::GetMessageMap(void) const
{
	return &FrGhostAward::_MsgMap;
}

// 0x818f60 (no reference; KR source order puts cPangFx's empty destructor
// between GetMessageMap and IsAlive)
FrGhostAward::cPangFx::~cPangFx(void)
{
}

// 0x818f70
bool FrGhostAward::cPangFx::IsAlive(void)
{
	return m_rect.y <= m_targetY;
}

// 0x818f90
void FrGhostAward::cPangFx::Proc(float dt)
{
	if (m_alpha < 255.0f) {
		m_alpha += dt * 255.0f * 4.0f;
		if (m_alpha >= 255.0f)
			m_alpha = 255.0f;
	}

	if (m_rect.y < m_targetY)
		m_rect.y += dt * 30.0f * m_speed;
}

// 0x819010
void FrGhostAward::cPangFx::Render(FrGraphicInterface* pGI)
{
	if (m_pBitmap)
		pGI->DrawTexture(m_pBitmap, m_rect, ((unsigned char)m_alpha << 24) | 0xffffff, 0);
}

// 0x819060
bool FrGhostAward::IsFinishCalcBonus(void)
{
	return m_calcBonusTime > 4.0f;
}

// 0x819d00 (no reference found)
void* UnreferencedReturnThis_00819d00(void* p, int, int)
{
	return p;
}

// 0x819d10 (no reference found)
void UnreferencedEmpty_00819d10(void)
{
}

// 0x819e80 (no reference found)
void* UnreferencedReturnThis_00819e80(void* p)
{
	return p;
}

// 0x81a780 (no reference found)
void* UnreferencedReturnThis_0081a780(void* p)
{
	return p;
}

// 0x81b410 (no reference found)
void UnreferencedEmpty_0081b410(int, int, int)
{
}

// 0x81e050
FrRecentMatch::FrRecentMatch(void)
	: m_pCourseImg(0), m_pItemImg(0), m_number1(0), m_number2(0), m_pHistoryList(0),
	m_pBgArea(0), m_pStaticText1(0), m_pTitleFont(0)
{
	tagWTITLEFONT info;
	memset(&info, 0, sizeof(info));
	info.filename = data_e1ece0;
	info.fontw = 16;
	info.fonth = 16;
	info.numPages = 1;
	info.texw = 128;
	info.texh = 64;
	info.pCharSet = "1234567890ymP-.?/:";
	m_pTitleFont = data_f023f0->GetTitleFont();
	m_pTitleFont->Create(&info);
}

// 0x81e320
FrGhostAward::FrGhostAward(void)
	: m_pTimeBar(0), m_pPouchArea(0), m_pExpGauge(0), m_pDescText(0), m_pGaugeText(0),
	m_calcBonusTime(0), m_clickCount(0), m_autoBonus(0), m_clickBonus(10), m_basePang(0),
	m_shownBasePang(0), m_gainExp(0), m_remainExp(0)
{
	tagWTITLEFONT info;
	memset(&info, 0, sizeof(info));
	info.filename = data_e1ed00;
	info.fontw = 16;
	info.fonth = 16;
	info.numPages = 1;
	info.texw = 128;
	info.texh = 64;
	info.pCharSet = "1234567890ym%-.?/:,";
	m_pTitleFont = data_f023f0->GetTitleFont();
	m_pTitleFont->Create(&info);
}

// 0x81f090
IObject* FrRecentMatchMakeInstance(void)
{
	return new FrRecentMatch;
}

struct __sFrRecentMatch {
	// 0x81f100
	__sFrRecentMatch(void)
	{
		ObjectFactory().AddObjectFunctor(FrRecentMatchMakeInstance, "FrRecentMatch");
	}
};
static __sFrRecentMatch s_registerFrRecentMatch;

// 0x81f4e0
IObject* FrGhostAwardMakeInstance(void)
{
	return new FrGhostAward;
}

struct __sFrGhostAward {
	// 0x81f550
	__sFrGhostAward(void)
	{
		ObjectFactory().AddObjectFunctor(FrGhostAwardMakeInstance, "FrGhostAward");
	}
};
static __sFrGhostAward s_registerFrGhostAward;

// 0x8202c0
IObject* FrGhostGameMapDlgMakeInstance(void)
{
	return new FrGhostGameMapDlg;
}

struct __sFrGhostGameMapDlg {
	// 0x820330
	__sFrGhostGameMapDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrGhostGameMapDlgMakeInstance, "FrGhostGameMapDlg");
	}
};
static __sFrGhostGameMapDlg s_registerFrGhostGameMapDlg;

// 0xcdb3b0 (dynamic initializer)
const WRTTI FrRecentMatch::m_RTTI("FrRecentMatch", &FrForm::m_RTTI);

// 0xcdb4b0 (dynamic initializer)
const WRTTI FrGhostGameMapDlg::m_RTTI("FrGhostGameMapDlg", &FrForm::m_RTTI);

// 0xcdb770 (dynamic initializer)
const WRTTI FrGhostAward::m_RTTI("FrGhostAward", &FrForm::m_RTTI);
