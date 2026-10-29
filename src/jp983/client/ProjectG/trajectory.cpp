// Original: client/ProjectG/trajectory.cpp (JP 983 exe)
#include "jp983/client/ProjectG/trajectory.h"
#include <new>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include "wresrcmng.h"
#include "jp983/client/ProjectG/golfball.h"
#include "jp983/client/ProjectG/quadtree.h"

extern "C" CSceneManager* data_e741c0;

// 0x79b9b0: no reference found (no call, vtable slot or pointer); a JP-only
// test of a ball id with its high 6 bits masked off.
bool IsNotBallId0xCC(int ballId)
{
	if ((ballId & 0x3FFFFFF) != 0xCC) {
		return true;
	}
	return false;
}

// 0x79b9c0
CBallTrack::~CBallTrack(void)
{
	if (m_hTexture != 0) {
		data_f023f0->Release(m_hTexture);
		m_hTexture = 0;
	}
	if (m_pPoint != NULL) { delete[] m_pPoint; m_pPoint = NULL; }
	if (data_f023f0 != NULL && m_hRainbowTexture != 0) { data_f023f0->Release(m_hRainbowTexture); m_hRainbowTexture = 0; }
	if (m_pPoint != NULL) { delete[] m_pPoint; m_pPoint = NULL; }
	if (m_pPointEx != NULL) { delete[] m_pPointEx; m_pPointEx = NULL; }
}

// 0x79ba90
CSkidMark::~CSkidMark(void)
{
	if (m_hTexture != 0) {
		data_f023f0->Release(m_hTexture);
		m_hTexture = 0;
	}

	if (m_pPoint != NULL) {
		delete[] m_pPoint;
		m_pPoint = NULL;
	}
	m_nPoint = 0;
	m_nCurPoint = 0;
}

// 0x79bb20
CBallWindTrack::~CBallWindTrack(void)
{
	if (m_pLineEffect != NULL) {
		delete[] m_pLineEffect;
		m_pLineEffect = NULL;
	}
}

// 0x79bba0
void CBallWindTrack::Init(void)
{
	m_ballTrack.Init();

	m_bActive = true;

	for (int i = 0; i < MAX_LINE_EFFECT; i++) {
		m_pLineEffect[i].m_bActive = false;
	}
}

// 0x79bbe0
CComet::~CComet(void)
{
	if (m_hTailTexture != 0) {
		data_f023f0->Release(m_hTailTexture);
		m_hTailTexture = 0;
	}
}

// 0x79bc50
CDoughnut::~CDoughnut(void)
{
	if (m_pParticle != NULL) {
		delete[] m_pParticle;
		m_pParticle = NULL;
	}
	if (m_hTexture != 0) {
		data_f023f0->Release(m_hTexture);
		m_hTexture = 0;
	}
}

// 0x79bce0
void CDoughnut::Init(void)
{
	for (int i = 0; i < m_nCount; i++) {
		m_pParticle[i].m_bActive = false;
	}
	m_fTimer = 0.0f;
	m_nHead = 0;
	m_bActive = true;
}

// 0x79bd20
CPuttLine::~CPuttLine(void)
{
	if (m_pPoint != NULL) {
		delete[] m_pPoint;
		m_pPoint = NULL;
	}
}

// 0x79bd50
bool CPuttLine::IsKeep(void)
{
	int i;
	for (i = 0; i <= m_nLastPoint; i++) {
		if (m_pPoint[i].m_nAlpha == 0x100) {
			break;
		}
	}
	return i != m_nLastPoint ? true : false;
}

// 0x79bd80
int CPuttLine::HowOldAreYou(void)
{
	return timeGetTime() - m_dwStartTime;
}

// 0x79bda0
void CPuttLine::RemoveUnkeptAlpha(void)
{
	for (int i = 0; i <= m_nLastPoint; i++) {
		if (m_pPoint[i].m_nAlpha != 0x100) {
			m_pPoint[i].m_nAlpha = 0;
		}
	}
}

// 0x79bde0
ntSkidMark_Cobra::~ntSkidMark_Cobra(void)
{
	if (m_pPoint != NULL) {
		delete[] m_pPoint;
		m_pPoint = NULL;
	}

	if (m_hTexture != 0) {
		data_f023f0->Release(m_hTexture);
		m_hTexture = 0;
	}
	m_nPoint = 0;
	m_nCurPoint = 0;
}

// 0x79be70
ntExplodeMark::~ntExplodeMark(void)
{
	if (m_hTexture != 0) {
		data_f023f0->Release(m_hTexture);
		m_hTexture = 0;
	}
}

// 0x79be90
void ntExplodeMark::Uninit(void)
{
	m_bActive = false;
}

// 0x79bea0
void ntExplodeMark::Process(void)
{
}

// 0x79beb0
CBallTrack::sPoint::sPoint()
{
	m_fAlpha = 1.0f;
}

// 0x79bec0
CTrajectory::CTrajectory(void) : m_pComet(NULL), m_pDoughnut(NULL), m_pPuttLine(NULL), m_pBallTrack(NULL), m_pSkidMark(NULL), m_pBallWindTrack(NULL)
{
	for (int i = 0; i < 3; i++) m_pActiveTrace[i] = NULL;

	m_pCurPuttLine = NULL;

	for (int j = 0; j < 32; j++) {
		m_pEffectTrace[j] = NULL;
	}

	m_pCobraSkidMark = NULL;
	m_pExplodeMark = NULL;
	AddSkipList(0x8C342);

	m_priority = 1;
}

// 0x79bff0
const WRTTI* CTrajectory::GetRTTI(void) const
{
	return &m_RTTI;
}

// 0x79c000
CTrajectory::~CTrajectory(void)
{
}

// 0x79c080
void CTrajectory::OnPreLoadInit(void)
{
	data_e741c0->RegisterElement((eObjType)5, 0, this, "±ËÀû", 0, 0);
}

// 0x79c0e0
CBallTrack::sPointEx::sPointEx()
{
}

// 0x79c260
CSkidMark::sPoint::sPoint()
{
}

// 0x79c3d0
CBallWindTrack::sLineEffect::sLineEffect()
{
}

// 0x79c820
CDoughnut::sParticle::sParticle()
{
}

// 0x79ca80
CPuttLine::sPoint::sPoint()
{
}

// 0x79cc50
ntSkidMark_Cobra::sPoint::sPoint()
{
}

// 0x79cd90
ntExplodeMark::ntExplodeMark(void) : m_bActive(false)
{
	m_hTexture = data_f023f0->LoadTexture("[_boom.jpg", 0, 0, NULL);
}

// 0x79cdc0
void ntExplodeMark::Init(const WVector &pos)
{
	m_bActive = true;
	memcpy(&m_vPos, &pos, sizeof(WVector));
}

// 0x79cde0
void ntExplodeMark::Display(void)
{
	if (m_bActive) {
		GetPVS().DrawDecal(m_hTexture, GetPVS().GetGroundPoint(m_vPos, false, 0, false), WVector(15.0f, 0.0f, 0.0f), WVector(0.0f, 0.0f, 15.0f), 1.0f, 1.0f, W_POLY_BLEND_NORMAL, false);
	}
}

// 0x79ce70
IObject* CTrajectoryMakeInstance(void)
{
	return new CTrajectory;
}

// 0x79cee0 (the constructor of the static registration instance)
struct __impCTrajectory {
	__impCTrajectory(void)
	{
		ObjectFactory().AddObjectFunctor(CTrajectoryMakeInstance, "CTrajectory");
		ActorFactory().AddActorClass("CTrajectory");
	}
};
static __impCTrajectory s_impCTrajectory;

// 0x79cf10
void CTrajectory::OnDestroy(void)
{
	if (m_pComet != NULL) { delete m_pComet; m_pComet = NULL; }
	if (m_pDoughnut != NULL) { delete m_pDoughnut; m_pDoughnut = NULL; }
	if (m_pBallTrack != NULL) { delete m_pBallTrack; m_pBallTrack = NULL; }
	if (m_pSkidMark != NULL) { delete m_pSkidMark; m_pSkidMark = NULL; }
	if (m_pBallWindTrack != NULL) { delete m_pBallWindTrack; m_pBallWindTrack = NULL; }
	if (m_pPuttLine != NULL) { delete m_pPuttLine; m_pPuttLine = NULL; }

	for (int i = 0; i < 32; i++) {
		if (m_pEffectTrace[i] != NULL) { delete m_pEffectTrace[i]; m_pEffectTrace[i] = NULL; }
	}

	if (m_pCobraSkidMark != NULL) { delete m_pCobraSkidMark; m_pCobraSkidMark = NULL; }
	if (m_pExplodeMark != NULL) { delete m_pExplodeMark; m_pExplodeMark = NULL; }
}

// 0x79cff0
void CTrajectory::OnProcess(float fElapsed)
{
	if (GolfBall().m_preDataIndex < 0) {
		return;
	}

	for (int i = 0; i < 3; i++) {
		if (m_pActiveTrace[i] != NULL) {
			m_pActiveTrace[i]->Process(fElapsed);
		}
	}
}

// 0x79d090
void CTrajectory::Display(void)
{
	for (int i = 0; i < 32; i++) {
		if (m_pEffectTrace[i] != NULL) {
			m_pEffectTrace[i]->Display();
		}
	}

	if (!Skipped() && GolfBall().m_preDataIndex >= 0) {
		for (int i = 0; i < 3; i++) {
			if (m_pActiveTrace[i] != NULL) {
				m_pActiveTrace[i]->Display();
			}
		}

		m_pExplodeMark->Display();
	}
}

// 0x79d1b0
CBallTrack::CBallTrack(void) : m_pPoint(NULL), m_bRainbow(false), m_pPointEx(NULL), m_hRainbowTexture(0)
{
	m_hTexture = data_f023f0->LoadTexture("[swingtale01.jpg", 0, 0, NULL);
}

// 0x79e430
CSkidMark::CSkidMark(void)
{
	m_pPoint = NULL;
	m_nStartFrame = -1;
	m_nEndFrame = -1;
	m_nPoint = 0;
	m_nCurPoint = 0;
	m_hTexture = data_f023f0->LoadTexture("~skidmark01.jpg", 0, 0, NULL);
}

// 0x79ee10
CBallWindTrack::CBallWindTrack(void) : m_pLineEffect(NULL)
{
	m_vLastEyePos.Reset();
	m_vEyeMove.Reset();

	m_pLineEffect = new sLineEffect[MAX_LINE_EFFECT];
}

// 0x79f590
CComet::CComet(void)
{
	m_hTailTexture = data_f023f0->LoadTexture("~ball_straight.jpg", 0, 0, NULL);
	m_fInterval = 0.1f;
	m_nCount = 20;

	for (int i = 0; i < 4; i++) {
		m_vertex[i].diffuse = 0xFFFFFFFF;
	}
}

// 0x79fed0
CDoughnut::CDoughnut(void)
{
	m_nCount = 10;
	m_pParticle = new sParticle[m_nCount];
	m_hTexture = data_f023f0->LoadTexture("~ball_circle01.jpg", 0, 0, NULL);

	m_fInterval = 0.1f;
}

// 0x7a0250
CPuttLine::CPuttLine(void) : m_pPoint(NULL)
{
}

// 0x7a0990
ntSkidMark_Cobra::ntSkidMark_Cobra(void)
{
	m_pPoint = NULL;
	m_nStartFrame = -1;
	m_nEndFrame = -1;
	m_nPoint = 0;
	m_nCurPoint = 0;
	m_hTexture = data_f023f0->LoadTexture("[_cobra_ef.jpg", 0, 0, NULL);
}
