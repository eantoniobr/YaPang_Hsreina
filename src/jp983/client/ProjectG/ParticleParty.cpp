// Original: client/ProjectG/ParticleParty.cpp (JP 983 exe)
#include "jp983/client/ProjectG/particleparty.h"

#include <new>

#include "jp983/client/Wangreal/include/wresrcmng.h"

// 0x6e8490
void CParticle::DisplayShadow(void)
{
}

// 0x6e84b0
void CParticle::SetNormal(WVector const& vNormal)
{
}

// 0x6e84c0
void CParticle::Generate(void)
{
}

// 0x6e84d0
void CParticle::BlowAway(float fPower, int nIndex)
{
}

// 0x6e84e0
CShotParticle::~CShotParticle(void)
{
	if (m_pPieces) {
		delete[] m_pPieces;
		m_pPieces = NULL;
	}
}

// 0x6e8510
CPowerShot::~CPowerShot(void)
{
}

// 0x6e8520
CLightColumn::~CLightColumn(void)
{
	for (int i = 0; i < 5; i++) {
		if (data_f023f0 && m_hEffectTex[i]) {
			data_f023f0->Release(m_hEffectTex[i]);
			m_hEffectTex[i] = 0;
		}
	}
	if (data_f023f0 && m_hScreenTex) {
		data_f023f0->Release(m_hScreenTex);
		m_hScreenTex = 0;
	}
}

// 0x6e85d0
CDust::~CDust(void)
{
	if (m_pParticles) {
		delete[] m_pParticles;
		m_pParticles = NULL;
	}
}

// 0x6e8600
void CDust::Process(float fElapsed)
{
	if (!m_bActive) {
		return;
	}

	m_fRemain -= fElapsed / m_fDuration;
	if (m_fRemain < 0.0f) {
		m_fRemain = 1.0f;
		m_bActive = false;
	}
}

// 0x6e8650
CGrassParticle::~CGrassParticle(void)
{
	if (m_pGrass) {
		delete[] m_pGrass;
		m_pGrass = NULL;
	}
}

// 0x6e8680
CBunkerShotParticle::~CBunkerShotParticle(void)
{
	if (m_pSmokes) {
		delete[] m_pSmokes;
		m_pSmokes = NULL;
	}
	if (m_pParticles) {
		delete[] m_pParticles;
		m_pParticles = NULL;
	}
	m_nSmokes = 0;
	m_nParticles = 0;
}

// 0x6e86e0
CBunkerParticle::~CBunkerParticle(void)
{
}

// 0x6e86f0
void CBunkerParticle::Process(float fElapsed)
{
	if (!m_bActive) {
		return;
	}

	m_fRemain -= fElapsed / m_fDuration;

	if (m_fRemain < 0.0f) {
		m_bActive = false;
	}
}

// 0x6e8730
CFragment::~CFragment(void)
{
	if (m_pFrags) {
		delete[] m_pFrags;
		m_pFrags = NULL;
	}
}

// 0x6e87f0
CRipple::~CRipple(void)
{
	if (m_pRipples) {
		delete[] m_pRipples;
		m_pRipples = NULL;
	}
	if (m_pSubParticle) {
		delete m_pSubParticle;
		m_pSubParticle = NULL;
	}
}

// 0x6e8880
void CRipple::Init(void)
{
	for (int i = 0; i < m_nRipples; i++) {
		m_pRipples[i].m_bAlive = false;
		m_pRipples[i].m_fRadius = 0.0f;
		m_pRipples[i].m_fPrevX = m_pRipples[i].m_fX;
		m_pRipples[i].m_fWait = 0.0f;
	}

	m_nCount = m_nRipples;
}

// 0x6e88e0
void CRipple::AddRipple(float fSize, float fDelay, float fX, float fZ)
{
	m_pRipples[m_nRipples].m_fSize = fSize;
	m_pRipples[m_nRipples].m_fDelay = fDelay;
	m_pRipples[m_nRipples].m_fX = fX;
	m_pRipples[m_nRipples].m_fZ = fZ;
	m_nRipples++;
}

// 0x6e8b00
bool CParticle::IsActive(void)
{
	return m_bActive;
}

// 0x6e8b10
void CCoin::SetActive(bool bActive)
{
	m_bActive = bActive;
}

// 0x6e8b20
CEnergyCenter::~CEnergyCenter(void)
{
	if (m_pSparks) {
		delete[] m_pSparks;
		m_pSparks = NULL;
	}
	m_nSparks = 0;
}

// 0x6e8b60
CStarDust::~CStarDust(void)
{
	if (m_pParticles) {
		delete[] m_pParticles;
		m_pParticles = NULL;
	}
	m_nParticles = 0;
}

// 0x6e8ba0
CStarDust2::~CStarDust2(void)
{
	if (m_pParticles) {
		delete[] m_pParticles;
		m_pParticles = NULL;
	}
	m_nParticles = 0;
}

// 0x6e8c10: no reference found (jp_xrefs, code and data); reads a bool at
// 0x160 of an object whose class is not known.
bool UnreferencedGetFlag_006e8c10(const bool* pObject)
{
	return pObject[0x160];
}

// 0x6e8c20: no reference found (jp_xrefs, code and data).
float UnreferencedScale_006e8c20(float fValue)
{
	return (float)(fValue * 3.0 * 2);
}

// 0x6e8c40
void CParticle::SetCenter(WVector const& vCenter)
{
	m_vCenter = vCenter;
}

// 0x6e8c90
void CFragment::SetNormal(WVector const& vNormal)
{
	m_vNormal = vNormal;
}

// 0x6e8cc0
CCoin::sCoin::sCoin(void) : m_pBody(NULL)
{
}

// 0x6e8d30
CShotParticle::sPiece::sPiece(void)
{
}

// 0x6e91e0
CDust::sParticle::sParticle(void)
{
}

// 0x6e9320
CGrassParticle::sGrass::sGrass(void)
{
}

// 0x6e9520
CBunkerShotParticle::sSmoke::sSmoke(void)
{
}

// 0x6e9530
CBunkerShotParticle::sParticle::sParticle(void)
{
}

// 0x6e9ac0
CFragment::sFrag::sFrag(void)
{
}

// 0x6e9c30
CDroplet::sDroplet::sDroplet(void)
{
}

// 0x6e9dd0
void CRipple::MakeParticle(void)
{
	Init();

	for (int i = 0; i < m_nRipples; i++) {
		m_pRipples[i].m_fWait = m_pRipples[i].m_fDelay;
	}

	m_bActive = true;
	m_pSubParticle->m_vCenter = m_vCenter;
	m_pSubParticle->MakeParticle();
}

// 0x6ea010
CCoin::sSpark::sSpark(void)
{
}

// 0x6eab70
CEnergyCenter::sSpark::sSpark(void)
{
}

// 0x6eb140
CStarDust::sParticle::sParticle(void)
{
}

// 0x6eb3b0
CStarDust2::sParticle::sParticle(void)
{
}

// 0x6eb4b0
CParticle::CParticle(void) : m_texHandle(0), m_bActive(false), m_pAniSpr(NULL), m_pSpr(NULL)
{
	m_pBuffer0 = &m_buffers[0];
	m_pBuffer1 = &m_buffers[1];
	m_pBuffer2 = &m_buffers[3];
	m_pBuffer3 = &m_buffers[2];
	m_pBufferEnd = NULL;
}

// 0x6eb8a0
CLightColumn::CLightColumn(void) : m_hScreenTex(0)
{
	for (int i = 0; i < 5; i++) m_hEffectTex[i] = 0;
	m_nJpUnknown[0] = 0;
	m_nJpUnknown[1] = 0;
}

// 0x6ec380
CBunkerParticle::CBunkerParticle(void)
{
}
