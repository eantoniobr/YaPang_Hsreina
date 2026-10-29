// Original: d:\build\custom\temp\code\client\projectg\scoreboard.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_SCOREBOARD_H
#define PG_JP983_CLIENT_PROJECTG_SCOREBOARD_H

#include "defines.h"
#include "padding.h"

#include "actor.h"
#include "client/FreshNext/include/frcmdtarget.h"
#include "client/FreshNext/include/frbutton.h"
#include "client/FreshNext/include/frgaugebar.h"

class WRTTI;
class WPoint;
class WRect;
class FrWndManager;
struct sFRESH_MSGMAP;

// The score board forms are FrForms (FrForm : FrWnd : IObject, FrCmdTarget;
// FrModalRenderer at 8), 38-slot primary vtables. Only what this unit's
// bodies need is declared: GetRTTI (primary slot 0) and the message map
// accessor, the override of FrCmdTarget slot 1 in the vtable at +4.

// Ranking board (primary vtable 0xd2438c).
class FrRankForm {
public:
	virtual const WRTTI* GetRTTI(void) const;   // slot 0

	static const WRTTI m_RTTI;   // 0xe7a434
};

// Ranking board with the score gauge (primary vtable 0xd2456c).
class FrRankForm3 {
	LAYOUT_CHECK_FRIEND;
public:
	virtual const WRTTI* GetRTTI(void) const;   // slot 0

	void SetScore(int score, int remain);

	static const WRTTI m_RTTI;   // 0xe7a448

private:
	PADDING(0x004, 0x118);
	FrGaugeBar* m_pScoreGauge;   // 0x118
	PADDING(0x11c, 0x174);
	int m_score;                 // 0x174 (SetScore)
	int m_scoreRemain;           // 0x178 (SetScore)
};

BEGIN_LAYOUT_CHECK(FrRankForm3)
	CHECK_FIELD(FrRankForm3, m_pScoreGauge, 0x118);
	CHECK_FIELD(FrRankForm3, m_score, 0x174);
	CHECK_FIELD(FrRankForm3, m_scoreRemain, 0x178);
END_LAYOUT_CHECK

// The 3D exhibition stage of the leader (KR Exhibition); only what this unit
// calls (Process 0x877340). No jp983 header declares it yet.
class CExhibition {
public:
	void Process(float dt, bool b);
};

// The leader stage and rival data of FrRankFormEx (KR size 0x48; the JP
// offsets below are confirmed by SetActive).
class CRankExData {
	LAYOUT_CHECK_FRIEND;
public:
	void OnProc(float dt);
	void SetActive(bool bActive);
	void SetLeader(void);
	void ShowLeader(void);

private:
	void* m_pRival;          // 0x0 (sRivalData array)
	float m_motionLength;    // 0x4
	float m_motionTime;      // 0x8
	int m_leader;            // 0xc
	int m_showLeader;        // 0x10
	CExhibition* m_pExhibition;   // 0x14
};

BEGIN_LAYOUT_CHECK(CRankExData)
	CHECK_FIELD(CRankExData, m_motionLength, 0x4);
	CHECK_FIELD(CRankExData, m_motionTime, 0x8);
	CHECK_FIELD(CRankExData, m_leader, 0xc);
	CHECK_FIELD(CRankExData, m_showLeader, 0x10);
	CHECK_FIELD(CRankExData, m_pExhibition, 0x14);
END_LAYOUT_CHECK

// Ranking board with the rival data (primary vtable 0xd2419c, FrCmdTarget
// vtable 0xd2418c). Primary slots declared up to SetVisible (FrWnd order).
class FrRankFormEx {
	LAYOUT_CHECK_FRIEND;
public:
	virtual const WRTTI* GetRTTI(void) const;                             // slot 0
	virtual ~FrRankFormEx(void);                                          // slot 1
	virtual bool Close(bool bDestroy);                                    // slot 2
	virtual bool Create(const char* name, const char* text, FrWndManager* pWndManager, unsigned long style,
	                    const WRect& rect, void* pParent);                // slot 3
	virtual void PreCreateWindow(FrWndManager* pWndManager, unsigned long style, const WRect& rect,
	                             void* pParent);                          // slot 4
	virtual void MoveWindow(const WPoint& pt);                            // slot 5
	virtual void Enable(bool bEnable);                                    // slot 6
	virtual void SetVisible(bool bVisible);                               // slot 7

	void SetActive(bool bActive);

	static const WRTTI m_RTTI;   // 0xe7a450

protected:
	static sFRESH_MSGMAP _MsgMap;   // 0xe185e0
	const sFRESH_MSGMAP* GetMessageMap(void) const;

private:
	PADDING(0x004, 0x110);
	CRankExData m_rankEx;        // 0x110
};

BEGIN_LAYOUT_CHECK(FrRankFormEx)
	CHECK_FIELD(FrRankFormEx, m_rankEx, 0x110);
END_LAYOUT_CHECK

// Award form (primary vtable 0xd2424c, FrCmdTarget vtable 0xd24240).
class FrAwardForm {
public:
	virtual const WRTTI* GetRTTI(void) const;   // slot 0

	static const WRTTI m_RTTI;   // 0xe7a464

protected:
	static sFRESH_MSGMAP _MsgMap;   // 0xe185f0
	const sFRESH_MSGMAP* GetMessageMap(void) const;
};

// Picked-up item display of the round (cAquireItem).
class cAquireItem {
	LAYOUT_CHECK_FRIEND;
public:
	void OnProc(float dt);

private:
	PADDING(0x00, 0xa0);
	float m_value;      // 0xa0
	float m_maxValue;   // 0xa4
};

BEGIN_LAYOUT_CHECK(cAquireItem)
	CHECK_FIELD(cAquireItem, m_value, 0xa0);
	CHECK_FIELD(cAquireItem, m_maxValue, 0xa4);
END_LAYOUT_CHECK

// Score card form (primary vtable 0xd2496c, FrCmdTarget vtable 0xd2495c).
class FrScoreForm {
	LAYOUT_CHECK_FRIEND;
public:
	virtual const WRTTI* GetRTTI(void) const;   // slot 0

	void SetTypeBtn(void);
	void ChangeTurn(void);
	void UpdatePang(void);

	static const WRTTI m_RTTI;   // 0xe7a46c

private:
	PADDING(0x004, 0x11c);
	FrButton* m_pTypeBtn[6];   // 0x11c (pressed for the current m_scoreType)
	PADDING(0x134, 0x178);
	int m_scoreType;           // 0x178
	float m_typeTime;          // 0x17c

protected:
	static sFRESH_MSGMAP _MsgMap;   // 0xe185f8
	const sFRESH_MSGMAP* GetMessageMap(void) const;
};

BEGIN_LAYOUT_CHECK(FrScoreForm)
	CHECK_FIELD(FrScoreForm, m_pTypeBtn, 0x11c);
	CHECK_FIELD(FrScoreForm, m_scoreType, 0x178);
	CHECK_FIELD(FrScoreForm, m_typeTime, 0x17c);
END_LAYOUT_CHECK

// Match items form (primary vtable 0xd246b4, FrCmdTarget vtable 0xd246a8).
class FrMatchItems {
public:
	virtual const WRTTI* GetRTTI(void) const;   // slot 0

	static const WRTTI m_RTTI;   // 0xe7a474

protected:
	static sFRESH_MSGMAP _MsgMap;   // 0xe18600
	const sFRESH_MSGMAP* GetMessageMap(void) const;
};

// The score board actor (vtable 0xd252dc, 15 IActor slots; FrCmdTarget
// vtable 0xd252cc at +0x18).
class CScore : public IActor, public FrCmdTarget {
public:
	virtual const WRTTI* GetRTTI(void) const;   // IActor slot 0

	static const WRTTI m_RTTI;   // 0xe7a47c

protected:
	static sFRESH_MSGMAP _MsgMap;   // 0xe18608
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget slot 1
};

#endif // PG_JP983_CLIENT_PROJECTG_SCOREBOARD_H
