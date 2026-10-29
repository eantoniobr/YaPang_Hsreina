// Original: client/ProjectG/particleparty.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_PARTICLEPARTY_H
#define PG_JP983_CLIENT_PROJECTG_PARTICLEPARTY_H

#include "defines.h"
#include "padding.h"
#include "jp983/client/Wangreal/include/wmath.h"

class W3dAniSpr;
class W3dSpr;
class IActor;
class CPetBody;

// One of the four vertex buffers a CParticle points into. JP: 0x58 bytes
// (KR 0x28): CParticle's constructor 0x6eb4b0 points m_pBuffer0..3 at
// 0x44, 0x9c, 0x14c and 0xf4. Only the position is known.
struct sParticleBuffer {
	WVector m_vPos;     // 0x0
	PADDING(0xC, 0x58);     // members not transcribed yet
};
CHECK_SIZE(sParticleBuffer, 0x58);
CHECK_FIELD(sParticleBuffer, m_vPos, 0x0);

// JP vtable 0xd1b3f0, 9 slots as in KR. Size 0x1A4 (the derived classes'
// first members start there: CShotParticle::MakeParticle 0x6eb570 reads
// m_pPieces at 0x1a4).
class CParticle {
	LAYOUT_CHECK_FRIEND;

public:
	CParticle(void);     // 0x6eb4b0
	virtual ~CParticle(void);     // 0 (0x6e8450, not in this unit)
	virtual void Process(float fElapsed) = 0;     // 1
	virtual void Display(void) = 0;     // 2
	virtual void DisplayShadow(void);     // 3 (0x6e8490)
	virtual void MakeParticle(void) = 0;     // 4
	int GetTexHandle(void) { return m_texHandle; }
	void LoadTexture(int handle) { m_texHandle = handle; }
	virtual void SetActive(bool bActive) { m_bActive = bActive; }     // 5 (0x6e84a0)
	void SetCenter(WVector const& vCenter);     // 0x6e8c40
	bool IsActive(void);     // 0x6e8b00, called out of line by CCoin
	virtual void SetNormal(WVector const& vNormal);     // 6 (0x6e84b0)

protected:
	virtual void Generate(void);     // 7 (0x6e84c0)
	virtual void BlowAway(float fPower, int nIndex);     // 8 (0x6e84d0)

protected:
	int m_nCount;     // 0x4

public:
	WVector m_vCenter;     // 0x8

protected:
	int m_texHandle;     // 0x14, WResourceManager texture handle
	bool m_bActive;     // 0x18
	W3dAniSpr* m_pAniSpr;     // 0x1C
	W3dSpr* m_pSpr;     // 0x20
	float m_fGenTime;     // 0x24
	float m_fRate;     // 0x28

private:
	PADDING(0x2C, 0x30);     // members not transcribed yet

protected:
	sParticleBuffer* m_pBuffer0;     // 0x30
	sParticleBuffer* m_pBuffer1;     // 0x34
	sParticleBuffer* m_pBuffer2;     // 0x38
	sParticleBuffer* m_pBuffer3;     // 0x3C
	sParticleBuffer* m_pBufferEnd;   // 0x40
	sParticleBuffer m_buffers[4];     // 0x44 (m_pBuffer2 -> [3], m_pBuffer3 -> [2])
};
CHECK_SIZE(CParticle, 0x1A4);
BEGIN_LAYOUT_CHECK(CParticle)
	CHECK_FIELD(CParticle, m_nCount, 0x4);
	CHECK_FIELD(CParticle, m_vCenter, 0x8);
	CHECK_FIELD(CParticle, m_texHandle, 0x14);
	CHECK_FIELD(CParticle, m_bActive, 0x18);
	CHECK_FIELD(CParticle, m_pAniSpr, 0x1C);
	CHECK_FIELD(CParticle, m_pSpr, 0x20);
	CHECK_FIELD(CParticle, m_fGenTime, 0x24);
	CHECK_FIELD(CParticle, m_fRate, 0x28);
	CHECK_FIELD(CParticle, m_pBuffer0, 0x30);
	CHECK_FIELD(CParticle, m_pBuffer3, 0x3C);
	CHECK_FIELD(CParticle, m_pBufferEnd, 0x40);
	CHECK_FIELD(CParticle, m_buffers, 0x44);
END_LAYOUT_CHECK

// The derived classes' members are the KR ones moved by CParticle's growth
// (KR 0xE4 -> JP 0x1A4); verified only where a comment says so. The nested
// structs keep their KR layouts (not verified in JP). Each one has an
// out-of-line empty constructor in ParticleParty.cpp (the JP exe keeps one
// right after its class's scalar deleting destructor).

// JP vtable 0xd1b418.
class CShotParticle : public CParticle {
public:
	struct sPiece {
		sPiece(void);     // 0x6e8d30

		bool m_bAlive;     // 0x0
		WVector m_vPos;     // 0x4
		WVector m_vVelocity;     // 0x10
		float m_fLife;     // 0x1C
		float m_fLength;     // 0x20
		float m_fSlowTime;     // 0x24
	};

	CShotParticle(void);
	virtual ~CShotParticle(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

private:
	sPiece* m_pPieces;     // 0x1A4 (MakeParticle 0x6eb570)
	int m_nPieces;     // 0x1A8 (MakeParticle 0x6eb570)
};

// JP vtable 0xd1b490.
class CDust : public CParticle {
public:
	struct sParticle {
		sParticle(void);     // 0x6e91e0

		WVector m_vPos;     // 0x0
		float m_fAngle;     // 0xC
		float m_fStartSize;     // 0x10
		float m_fEndSize;     // 0x14
	};

	CDust(int nCount);
	virtual ~CDust(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

private:
	sParticle* m_pParticles;     // 0x1A4
	int m_nParticles;     // 0x1A8
	float m_fDuration;     // 0x1AC
	float m_fRemain;     // 0x1B0
};

// JP vtable 0xd1b4b8.
class CGrassParticle : public CParticle {
public:
	struct sGrass {
		sGrass(void);     // 0x6e9320

		int m_nFrame;     // 0x0
		float m_fAlpha;     // 0x4
		float m_fAngle;     // 0x8
		float m_fAngularSpeed;     // 0xC
		WVector m_vPos;     // 0x10
		WVector m_vVelocity;     // 0x1C
		bool m_bAlive;     // 0x28
		PADDING(0x29, 0x2C);
		float m_fFadeTime;     // 0x2C
	};

	CGrassParticle(int nCount, WVector const& vCenter);
	virtual ~CGrassParticle(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

private:
	sGrass* m_pGrass;     // 0x1A4
	int m_nGrass;     // 0x1A8
	WVector m_vOrigin;     // 0x1AC
};

// JP vtable 0xd1b4e0.
class CBunkerShotParticle : public CParticle {
public:
	struct sSmoke {
		sSmoke(void);     // 0x6e9520

		WVector m_vPos;     // 0x0
		WVector m_vVelocity;     // 0xC
	};

	struct sParticle {
		sParticle(void);     // 0x6e9530

		bool m_bAlive;     // 0x0
		WVector m_vPos;     // 0x4
		WVector m_vVelocity;     // 0x10
		float m_fLength;     // 0x1C
		float m_fLife;     // 0x20
		float m_fMaxLife;     // 0x24
	};

	CBunkerShotParticle(int nSmoke, int nParticle);
	virtual ~CBunkerShotParticle(void);
	virtual void MakeParticle(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);

protected:
	virtual void Generate(void);

private:
	sSmoke* m_pSmokes;     // 0x1A4
	sParticle* m_pParticles;     // 0x1A8
	int m_nSmokes;     // 0x1AC
	int m_nParticles;     // 0x1B0
	float m_fDuration;     // 0x1B4
	float m_fRemain;     // 0x1B8
	unsigned long m_dwColor;     // 0x1BC
};

// JP vtable 0xd1b440.
class CPowerShot : public CParticle {
public:
	CPowerShot(void);
	virtual ~CPowerShot(void);     // 0x6e8510
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

private:
	float m_fSize;     // 0x1A4
	float m_fWidth;     // 0x1A8
	int m_nSegments;     // 0x1AC
	int m_nAlpha;     // 0x1B0
	float m_fLife;     // 0x1B4
	float m_fTime;     // 0x1B8
	float m_fSpeed;     // 0x1BC
	float m_fDistance;     // 0x1C0
};

// JP vtable 0xd1b468. Size 0x1D8 (new CLightColumn, ctor 0x6eb8a0): the KR
// members moved by 0xC0 (m_hEffectTex and m_hScreenTex verified by the
// destructor 0x6e8520), then 8 bytes not known yet.
class CLightColumn : public CParticle {
	LAYOUT_CHECK_FRIEND;

public:
	CLightColumn(void);     // 0x6eb8a0
	virtual ~CLightColumn(void);     // 0x6e8520
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);
	void FadeIn(void);
	void FadeOut(void);

private:
	int m_nFade;     // 0x1A4
	float m_fHeight;     // 0x1A8
	float m_fDistance;     // 0x1AC
	unsigned char m_byAlpha;     // 0x1B0
	unsigned char m_byTargetAlpha;     // 0x1B1
	PADDING(0x1B2, 0x1B4);
	int m_hEffectTex[5];     // 0x1B4, hole_ef_nomal_10..14
	int m_hScreenTex;     // 0x1C8, hole_scr01
	float m_fFrame;     // 0x1CC
	int m_nJpUnknown[2];     // 0x1D0, JP only, zeroed by the constructor
};
CHECK_SIZE(CLightColumn, 0x1D8);
BEGIN_LAYOUT_CHECK(CLightColumn)
	CHECK_FIELD(CLightColumn, m_nFade, 0x1A4);
	CHECK_FIELD(CLightColumn, m_byAlpha, 0x1B0);
	CHECK_FIELD(CLightColumn, m_hEffectTex, 0x1B4);
	CHECK_FIELD(CLightColumn, m_hScreenTex, 0x1C8);
	CHECK_FIELD(CLightColumn, m_fFrame, 0x1CC);
	CHECK_FIELD(CLightColumn, m_nJpUnknown, 0x1D0);
END_LAYOUT_CHECK

// JP vtable 0xd1b508.
class CBunkerParticle : public CParticle {
public:
	CBunkerParticle(void);     // 0x6ec380
	virtual ~CBunkerParticle(void);     // 0x6e86e0
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

private:
	int m_nAlpha;     // 0x1A4
	float m_fRemain;     // 0x1A8
	PADDING(0x1AC, 0x1B0);
	float m_fSize;     // 0x1B0
	float m_fDuration;     // 0x1B4
};

// JP vtable 0xd1b530.
class CFragment : public CParticle {
public:
	struct sFrag {
		sFrag(void);     // 0x6e9ac0

		WVector m_vPos;     // 0x0
		WVector m_vVelocity;     // 0xC
	};

	CFragment(void);
	virtual ~CFragment(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);
	virtual void SetNormal(WVector const& vNormal);

private:
	sFrag* m_pFrags;     // 0x1A4
	int m_nFrags;     // 0x1A8
	PADDING(0x1AC, 0x1B4);
	float m_fAlpha;     // 0x1B4
	WVector m_vNormal;     // 0x1B8
};

// JP vtable 0xd1b580.
class CRipple : public CParticle {
public:
	struct sRipple {
		float m_fRadius;     // 0x0
		float m_fPrevX;     // 0x4
		float m_fX;     // 0x8
		float m_fZ;     // 0xC
		float m_fSize;     // 0x10
		bool m_bAlive;     // 0x14
		float m_fDelay;     // 0x18
		float m_fWait;     // 0x1C
	};

	CRipple(void);
	virtual ~CRipple(void);
	void Init(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

protected:
	void AddRipple(float fSize, float fDelay, float fX, float fZ);

private:
	sRipple* m_pRipples;     // 0x1A4
	int m_nRipples;     // 0x1A8
	CParticle* m_pSubParticle;     // 0x1AC
};

// JP vtable 0xd1b5f8.
class CStarDust : public CParticle {
public:
	struct sParticle {
		sParticle(void);     // 0x6eb140

		bool m_bAlive;     // 0x0
		float m_fRadius;     // 0x4
		WVector m_vPos;     // 0x8
		WVector m_vAxisX;     // 0x14
		WVector m_vAxisY;     // 0x20
		PADDING(0x2C, 0x38);
		WVector m_vOrigin;     // 0x38
		float m_fAngle;     // 0x44
		float m_fAngularSpeed;     // 0x48
		float m_fLife;     // 0x4C
	};

	CStarDust(void);
	virtual ~CStarDust(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

protected:
	virtual void Generate(void);
	virtual void BlowAway(float fPower, int nIndex);

private:
	sParticle* m_pParticles;     // 0x1A4
	int m_nParticles;     // 0x1A8
	int m_nGenerated;     // 0x1AC
	float m_fFade;     // 0x1B0
	float m_fAlpha;     // 0x1B4
};

// JP vtable 0xd1b5d0.
class CEnergyCenter : public CParticle {
public:
	struct sSpark {
		sSpark(void);     // 0x6eab70

		bool m_bAlive;     // 0x0
		WVector m_vPos;     // 0x4
		WVector m_vDir;     // 0x10
		float m_fAlpha;     // 0x1C
	};

	CEnergyCenter(int nCount, WVector const& vCenter, float fRadius);
	virtual ~CEnergyCenter(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

protected:
	void Generate(float fElapsed);

private:
	sSpark* m_pSparks;     // 0x1A4
	float m_fRadius;     // 0x1A8
	int m_nGenerated;     // 0x1AC
	int m_nSparks;     // 0x1B0
	WVector m_vOrigin;     // 0x1B4
	float m_fLife;     // 0x1C0
	float m_fTime;     // 0x1C4
	float m_fAlpha;     // 0x1C8
	float m_fMaxAlpha;     // 0x1CC
	IActor* m_pGolfBg;     // 0x1D0
};

// JP vtable 0xd1b620.
class CStarDust2 : public CParticle {
public:
	struct sParticle {
		sParticle(void);     // 0x6eb3b0

		bool m_bAlive;     // 0x0
		float m_fRadius;     // 0x4
		WVector m_vPos;     // 0x8
		WVector m_vAxisX;     // 0x14
		WVector m_vAxisY;     // 0x20
		PADDING(0x2C, 0x38);
		WVector m_vOrigin;     // 0x38
		float m_fAngle;     // 0x44
		float m_fAngularSpeed;     // 0x48
		float m_fLife;     // 0x4C
	};

	CStarDust2(void);
	virtual ~CStarDust2(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

protected:
	virtual void Generate(void);

private:
	sParticle* m_pParticles;     // 0x1A4
	int m_nParticles;     // 0x1A8
	int m_nGenerated;     // 0x1AC
	float m_fFade;     // 0x1B0
	float m_fAlpha;     // 0x1B4
};

// JP vtable 0xd1b558.
class CDroplet : public CParticle {
public:
	struct sDroplet {
		sDroplet(void);     // 0x6e9c30

		WVector m_vPos;     // 0x0
		WVector m_vVelocity;     // 0xC
		UNKNOWN(0x18, 0x1C);
	};

	CDroplet(void);
	virtual ~CDroplet(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void MakeParticle(void);

private:
	sDroplet* m_pDroplets;     // 0x1A4
	int m_nDroplets;     // 0x1A8
	float m_fDuration;     // 0x1AC
	float m_fAlpha;     // 0x1B0
};

// JP vtable 0xd1b5a8.
class CCoin : public CParticle {
public:
	struct sCoin {
		sCoin(void);     // 0x6e8cc0

		CPetBody* m_pBody;     // 0x0
		float m_fSpin;     // 0x4
		WVector m_vVelocity;     // 0x8
		float m_fBounceSpeed;     // 0x14
	};

	struct sSpark {
		sSpark(void);     // 0x6ea010

		bool m_bAlive;     // 0x0
		WVector m_vPos;     // 0x4
		WVector m_vVelocity;     // 0x10
		float m_fAlpha;     // 0x1C
		float m_fLife;     // 0x20
		float m_fSlowTime;     // 0x24
	};

	CCoin(int nCount, WVector const& vCenter);
	virtual ~CCoin(void);
	virtual void MakeParticle(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	virtual void DisplayShadow(void);
	virtual void SetActive(bool bActive);     // 5 (0x6e8b10)

protected:
	bool ShouldDisplay(void);
	virtual void Generate(void);

private:
	sCoin* m_pCoins;     // 0x1A4
	sSpark* m_pSparks;     // 0x1A8
	int m_nCoins;     // 0x1AC
	int m_nSparks;     // 0x1B0
	WVector m_vOrigin;     // 0x1B4
	float m_fDuration;     // 0x1C0
	float m_fRemain;     // 0x1C4
	int m_nDropSounds;     // 0x1C8
};

#endif
