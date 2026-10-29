// Original: d:\build\custom\temp\code\client\projectg\trajectory.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_TRAJECTORY_H
#define PG_JP983_CLIENT_PROJECTG_TRAJECTORY_H

#include "defines.h"
#include "padding.h"
#include "wmath.h"
#include "wvideo.h"
#include "jp983/client/ProjectG/actor.h"
#include "jp983/client/ProjectG/scenemanager.h"

class WRTTI;

// The trajectory actor (RTTI name CTrajectory): IActor vtable 0xd2573c,
// CRenderFuncPtr vtable 0xd25728 at 0x18. JP has three active traces (KR
// two), so every later member sits 4 bytes after KR's.
class CBallTrace;
class CComet;
class CDoughnut;
class CPuttLine;
class CBallTrack;
class CSkidMark;
class CBallWindTrack;
class ntSkidMark_Cobra;
class ntExplodeMark;

IObject* CTrajectoryMakeInstance(void);

// operator new size 0xCC in CTrajectoryMakeInstance.
class CTrajectory : public IActor, public CRenderFuncPtr {
	LAYOUT_CHECK_FRIEND;
	friend IObject* CTrajectoryMakeInstance(void);
public:
	static const WRTTI m_RTTI;                    // 0xe7a494
	virtual const WRTTI* GetRTTI(void) const;     // 0 (0x79bff0)
	virtual ~CTrajectory(void);                   // 1 (0x79c000, ??_G 0x79c020)
	virtual void OnPreLoadInit(void);             // 2 (0x79c080)
	virtual void OnLoad(void);                    // 3 (0x7a11e0)
	virtual void OnProcess(float);                // 6 (0x79cff0)
	virtual void OnDestroy(void);                 // 8 (0x79cf10)
	virtual void Display(void);                   // CRenderFuncPtr 1 (0x79d090)
	virtual void HandleMsg(const MsgObject &msg); // 11 (0x7a1370)

protected:
	CTrajectory(void);                  // 0x79bec0

private:
	CBallTrace *m_pActiveTrace[3];      // 0x1C (processed while the ball flies; not owned)
	CComet *m_pComet;                   // 0x28
	CDoughnut *m_pDoughnut;             // 0x2C
	CPuttLine *m_pPuttLine;             // 0x30
	CBallTrack *m_pBallTrack;           // 0x34
	CSkidMark *m_pSkidMark;             // 0x38
	CBallWindTrack *m_pBallWindTrack;   // 0x3C
	CPuttLine *m_pEffectTrace[32];      // 0x40 (kept putt lines, deleted by OnDestroy)
	CPuttLine *m_pCurPuttLine;          // 0xC0
	ntSkidMark_Cobra *m_pCobraSkidMark; // 0xC4
	ntExplodeMark *m_pExplodeMark;      // 0xC8
};
CHECK_SIZE(CTrajectory, 0xCC);
BEGIN_LAYOUT_CHECK(CTrajectory)
	CHECK_FIELD(CTrajectory, m_pActiveTrace, 0x1C);
	CHECK_FIELD(CTrajectory, m_pComet, 0x28);
	CHECK_FIELD(CTrajectory, m_pPuttLine, 0x30);
	CHECK_FIELD(CTrajectory, m_pBallWindTrack, 0x3C);
	CHECK_FIELD(CTrajectory, m_pEffectTrace, 0x40);
	CHECK_FIELD(CTrajectory, m_pCobraSkidMark, 0xC4);
	CHECK_FIELD(CTrajectory, m_pExplodeMark, 0xC8);
END_LAYOUT_CHECK

// Base of the trails (vtable 0xd25648). JP size 0x194: WTVertex is 0x58
// bytes in JP (the constructor 0x79d170 points m_pVertex at 0x34, 0x8c,
// 0x13c, 0xe4), so every derived member sits 0xc0 later than in KR.
class CBallTrace {
	LAYOUT_CHECK_FRIEND;
public:
	CBallTrace(void);
	virtual ~CBallTrace(void) {}     // 0 (??_G 0x79b980)
	virtual void Init(void) = 0;     // 1
	virtual void Process(float fElapsed) = 0;     // 2
	virtual void Display(void) = 0;  // 3

protected:
	virtual void Generate(void);     // 4 (0x79b960)
	virtual void BlowAway(float fDist, int nType);     // 5 (0x79b970)

	int m_nState;                // 0x4
	int m_hTexture;              // 0x8 (texture handle of data_f023f0)
	int m_nCount;                // 0xC (element count of the derived trail)
	int m_nHead;                 // 0x10 (reset by Init)
	float m_fTimer;              // 0x14 (reset by Init)
	float m_fInterval;           // 0x18
	bool m_bActive;              // 0x1C
	WTVertex *m_pVertex[5];      // 0x20 (-> m_vertex[0], [1], [3], [2]: a fan for DrawPolygonFan; [4] is its NULL terminator)
	WTVertex m_vertex[4];        // 0x34 (quad corners)
};
CHECK_SIZE(CBallTrace, 0x194);
BEGIN_LAYOUT_CHECK(CBallTrace)
	CHECK_FIELD(CBallTrace, m_hTexture, 0x8);
	CHECK_FIELD(CBallTrace, m_nCount, 0xC);
	CHECK_FIELD(CBallTrace, m_nHead, 0x10);
	CHECK_FIELD(CBallTrace, m_fTimer, 0x14);
	CHECK_FIELD(CBallTrace, m_fInterval, 0x18);
	CHECK_FIELD(CBallTrace, m_bActive, 0x1C);
	CHECK_FIELD(CBallTrace, m_pVertex, 0x20);
	CHECK_FIELD(CBallTrace, m_vertex, 0x34);
END_LAYOUT_CHECK

// Ball track (vtable 0xd25664). The JP exe keeps out-of-line copies of the
// nested types' constructors (nothing calls them; the callers inline them),
// so they are declared here and defined in trajectory.cpp.
class CBallTrack : public CBallTrace {
	LAYOUT_CHECK_FRIEND;
public:
	// Trail point.
	struct sPoint {
		WVector m_vPos;      // 0x0
		WVector m_vSide;     // 0xC
		float m_fAlpha;      // 0x18

		sPoint();            // 0x79beb0
	};

	// Rainbow segment.
	struct sPointEx {
		bool m_bActive;      // 0x0
		float m_fProgress;   // 0x4
		WVector m_vStart;    // 0x8
		WVector m_vDir;      // 0x14

		sPointEx();          // 0x79c0e0 (presumed: the copy after ??_GCBallTrack)
	};

	CBallTrack(void);                 // 0x79d1b0
	virtual ~CBallTrack(void);        // 0x79b9c0 (??_G 0x79c0b0)
	virtual void Init(void);          // 0x79d230
	virtual void Process(float fElapsed);     // 0x79d850
	virtual void Display(void);       // 0x79e2b0

	sPoint *m_pPoint;        // 0x194 (allocated in Init)
	bool m_bRainbow;         // 0x198
	sPointEx *m_pPointEx;    // 0x19C (allocated in Init)
	int m_hRainbowTexture;   // 0x1A0 (released by the destructor)
	int m_nPoint;            // 0x1A4 (KR offset + 0xc0, not checked in JP code yet)

private:
	float m_fAlpha;          // 0x1A8 (KR offset + 0xc0, not checked yet)
	float m_fFadeTimer;      // 0x1AC (KR offset + 0xc0, not checked yet)
	float m_fFadeTime;       // 0x1B0 (KR offset + 0xc0, not checked yet)
	float m_fMaxAlpha;       // 0x1B4 (KR offset + 0xc0, not checked yet)
	int m_nLastFrame;        // 0x1B8 (KR offset + 0xc0, not checked yet)
};
// Size from CBallWindTrack's constructor (its m_ballTrack 0x198, next member 0x354).
CHECK_SIZE(CBallTrack, 0x1BC);
BEGIN_LAYOUT_CHECK(CBallTrack)
	CHECK_FIELD(CBallTrack, m_pPoint, 0x194);
	CHECK_FIELD(CBallTrack, m_bRainbow, 0x198);
	CHECK_FIELD(CBallTrack, m_pPointEx, 0x19C);
	CHECK_FIELD(CBallTrack, m_hRainbowTexture, 0x1A0);
END_LAYOUT_CHECK
CHECK_SIZE(CBallTrack::sPoint, 0x1C);
CHECK_FIELD(CBallTrack::sPoint, m_fAlpha, 0x18);
CHECK_SIZE(CBallTrack::sPointEx, 0x20);

// Skid mark of the rolling ball (vtable 0xd25680).
class CSkidMark : public CBallTrace {
	LAYOUT_CHECK_FRIEND;
public:
	// Mark point on the ground.
	struct sPoint {
		WVector m_vLeft;         // 0x0
		WVector m_vRight;        // 0xC
		unsigned char m_alpha;   // 0x18
		sPoint();                // 0x79c260 (presumed: the copy after ??_GCSkidMark)
	};

	CSkidMark(void);                  // 0x79e430
	virtual ~CSkidMark(void);         // 0x79ba90 (??_G 0x79c230)
	virtual void Init(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);

private:
	sPoint *m_pPoint;        // 0x194 (m_nPoint elements, allocated in Init)
	int m_nPoint;            // 0x198
	int m_nCurPoint;         // 0x19C
	int m_nStartFrame;       // 0x1A0 (PreData index, -1 = unset)
	int m_nEndFrame;         // 0x1A4 (PreData index, -1 = unset)
	int m_nLastFrame;        // 0x1A8
};
CHECK_SIZE(CSkidMark::sPoint, 0x1C);
BEGIN_LAYOUT_CHECK(CSkidMark)
	CHECK_FIELD(CSkidMark, m_pPoint, 0x194);
	CHECK_FIELD(CSkidMark, m_nPoint, 0x198);
	CHECK_FIELD(CSkidMark, m_nCurPoint, 0x19C);
	CHECK_FIELD(CSkidMark, m_nStartFrame, 0x1A0);
	CHECK_FIELD(CSkidMark, m_nEndFrame, 0x1A4);
END_LAYOUT_CHECK

// Cobra shot skid mark (vtable 0xd2570c).
class ntSkidMark_Cobra : public CBallTrace {
	LAYOUT_CHECK_FRIEND;
public:
	// Mark point on the ground.
	struct sPoint {
		WVector m_vLeft;     // 0x0
		WVector m_vRight;    // 0xC
		sPoint();            // 0x79cc50 (presumed: the copy after ??_GntSkidMark_Cobra)
	};

	ntSkidMark_Cobra(void);           // 0x7a0990
	virtual ~ntSkidMark_Cobra(void);  // 0x79bde0 (??_G 0x79cc20)
	virtual void Init(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);

private:
	sPoint *m_pPoint;        // 0x194
	int m_nPoint;            // 0x198
	int m_nCurPoint;         // 0x19C
	int m_nStartFrame;       // 0x1A0 (PreData index, -1 = unset)
	int m_nEndFrame;         // 0x1A4 (PreData index, -1 = unset)
	int m_nLastFrame;        // 0x1A8
};
CHECK_SIZE(ntSkidMark_Cobra::sPoint, 0x18);
BEGIN_LAYOUT_CHECK(ntSkidMark_Cobra)
	CHECK_FIELD(ntSkidMark_Cobra, m_pPoint, 0x194);
	CHECK_FIELD(ntSkidMark_Cobra, m_nStartFrame, 0x1A0);
	CHECK_FIELD(ntSkidMark_Cobra, m_nEndFrame, 0x1A4);
END_LAYOUT_CHECK

// Wind lines along the ball track (vtable 0xd2569c).
class CBallWindTrack : public CBallTrace {
	LAYOUT_CHECK_FRIEND;
public:
	enum { MAX_LINE_EFFECT = 256 };

	struct sLineEffect {
		WVector m_vStart;    // 0x0
		WVector m_vEnd;      // 0xC
		int m_nAlpha;        // 0x18
		float m_fLength;     // 0x1C
		bool m_bActive;      // 0x20
		PADDING(0x21, 0x24);
		sLineEffect();       // 0x79c3d0 (presumed: the copy after ??_GCBallWindTrack)
	};

	CBallWindTrack(void);             // 0x79ee10
	virtual ~CBallWindTrack(void);    // 0x79bb20 (??_G 0x79c3a0)
	virtual void Init(void);          // 0x79bba0
	virtual void Process(float fElapsed);     // 0x79eeb0
	virtual void Display(void);       // 0x79c3e0

private:
	sLineEffect *m_pLineEffect;  // 0x194 (MAX_LINE_EFFECT elements)
	CBallTrack m_ballTrack;      // 0x198
	float m_fLineAlpha;          // 0x354
	WVector m_vLastEyePos;       // 0x358 (eye position of the previous Process)
	WVector m_vEyeMove;          // 0x364 (eye position minus m_vLastEyePos)
};
CHECK_SIZE(CBallWindTrack, 0x370);
BEGIN_LAYOUT_CHECK(CBallWindTrack)
	CHECK_FIELD(CBallWindTrack, m_pLineEffect, 0x194);
	CHECK_FIELD(CBallWindTrack, m_ballTrack, 0x198);
	CHECK_FIELD(CBallWindTrack, m_vLastEyePos, 0x358);
	CHECK_FIELD(CBallWindTrack, m_vEyeMove, 0x364);
END_LAYOUT_CHECK
CHECK_SIZE(CBallWindTrack::sLineEffect, 0x24);
CHECK_FIELD(CBallWindTrack::sLineEffect, m_bActive, 0x20);

// Putting guide line (vtable 0xd256f0).
class CPuttLine : public CBallTrace {
	LAYOUT_CHECK_FRIEND;
public:
	// Guide point: m_nAlpha 0x100 marks a kept point.
	struct sPoint {
		int m_nAlpha;        // 0x0
		WVector m_vLeft;     // 0x4
		WVector m_vRight;    // 0x10
		sPoint();            // 0x79ca80 (presumed: the copy after ??_GCPuttLine)
	};

	CPuttLine(void);
	virtual ~CPuttLine(void);
	virtual void Init(void);
	virtual void Process(float fElapsed);
	virtual void Display(void);
	bool IsKeep(void);
	int HowOldAreYou(void);
	void RemoveUnkeptAlpha(void);

private:
	sPoint *m_pPoint;            // 0x194
	int m_nLastPoint;            // 0x198 (last valid index of m_pPoint)
	unsigned long m_dwStartTime; // 0x19C (timeGetTime())
};
CHECK_SIZE(CPuttLine::sPoint, 0x1C);
BEGIN_LAYOUT_CHECK(CPuttLine)
	CHECK_FIELD(CPuttLine, m_pPoint, 0x194);
	CHECK_FIELD(CPuttLine, m_nLastPoint, 0x198);
	CHECK_FIELD(CPuttLine, m_dwStartTime, 0x19C);
END_LAYOUT_CHECK

// Comet trail (vtable 0xd256b8). Members after m_hTailTexture (0x380, read
// by the constructor and destructor) are placed at KR offset + 0xc0.
class CComet : public CBallTrace {
	LAYOUT_CHECK_FRIEND;
public:
	CComet(void);                     // 0x79f590
	virtual ~CComet(void);            // 0x79bbe0 (??_G 0x79c4d0)
	virtual void Init(void);          // 0x79f630
	virtual void Process(float fElapsed);     // 0x79fb50
	virtual void Display(void);       // 0x79c500

	enum { MAX_POINT = 20 };

protected:
	virtual void Generate(void);      // 0x79f8b0

private:
	WVector m_point[MAX_POINT][2];   // 0x194 (ring buffer, m_nHead is the newest)
	float m_fNumPoint;       // 0x374
	PADDING(0x378, 0x37C);   // members not transcribed yet
	float m_fAlpha;          // 0x37C
	int m_hTailTexture;      // 0x380 (released by the destructor)
	int m_bHeadPoint;        // 0x384
	WVector m_vHeadLeft;     // 0x388
	WVector m_vHeadRight;    // 0x394
};
BEGIN_LAYOUT_CHECK(CComet)
	CHECK_FIELD(CComet, m_point, 0x194);
	CHECK_FIELD(CComet, m_hTailTexture, 0x380);
END_LAYOUT_CHECK

// Rings around the ball (vtable 0xd256d4).
class CDoughnut : public CBallTrace {
	LAYOUT_CHECK_FRIEND;
public:
	struct sParticle {
		float m_fScale;      // 0x0
		float m_fAlpha;      // 0x4
		bool m_bActive;      // 0x8
		WMatrix m_matrix;    // 0xC
		sParticle();         // 0x79c820 (presumed: the copy after ??_GCDoughnut)
	};

	CDoughnut(void);                  // 0x79fed0
	virtual ~CDoughnut(void);         // 0x79bc50 (??_G 0x79c7f0)
	virtual void Init(void);     // 0x79bce0
	virtual void Process(float fElapsed);
	virtual void Display(void);

private:
	sParticle *m_pParticle;  // 0x194 (m_nCount elements)
};
CHECK_SIZE(CDoughnut::sParticle, 0x3C);
CHECK_FIELD(CDoughnut::sParticle, m_bActive, 0x8);
BEGIN_LAYOUT_CHECK(CDoughnut)
	CHECK_FIELD(CDoughnut, m_pParticle, 0x194);
END_LAYOUT_CHECK

// Explosion mark left where the ball lands.
class ntExplodeMark {
	LAYOUT_CHECK_FRIEND;
public:
	ntExplodeMark(void);             // 0x79cd90
	~ntExplodeMark(void);            // 0x79be70
	void Init(const WVector &pos);   // 0x79cdc0
	void Uninit(void);               // 0x79be90
	void Process(void);              // 0x79bea0
	void Display(void);

private:
	bool m_bActive;      // 0x0
	int m_hTexture;      // 0x4
	WVector m_vPos;      // 0x8
};
CHECK_SIZE(ntExplodeMark, 0x14);
BEGIN_LAYOUT_CHECK(ntExplodeMark)
	CHECK_FIELD(ntExplodeMark, m_bActive, 0x0);
	CHECK_FIELD(ntExplodeMark, m_hTexture, 0x4);
	CHECK_FIELD(ntExplodeMark, m_vPos, 0x8);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_TRAJECTORY_H
