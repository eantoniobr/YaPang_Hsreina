// Original: d:\build\custom\temp\code\client\projectg\ghostgamedlg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_GHOSTGAMEDLG_H
#define PG_JP983_CLIENT_PROJECTG_GHOSTGAMEDLG_H

#include <stdint.h>
#include <list>
#include <string>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "jp983/client/Wangreal/include/wtypes.h"
#include "client/FreshNext/include/frform.h"

class Bitmap;
class FrArea;
class FrGaugeBar;
class FrGraphicInterface;
class FrListBox;
class FrStatic;
class WTitleFont;
struct sFRESH_ENTRY;

IObject* FrRecentMatchMakeInstance(void);       // 0x81f090
IObject* FrGhostGameMapDlgMakeInstance(void);   // 0x8202c0
IObject* FrGhostAwardMakeInstance(void);        // 0x81f4e0

// List of the player's recent ghost matches (RTTI FrRecentMatch : FrForm;
// vtables 0xd2ef4c (38 slots: GetRTTI and the destructor overridden),
// 0xd2ef40 (FrCmdTarget: ??_E thunk, GetMessageMap) and 0xd2ef38
// (FrModalRenderer)). Size 0x160, the `new` of FrRecentMatchMakeInstance
// (as KR); the members keep their KR offsets (constructor 0x81e050).
class FrRecentMatch : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	// One row of the history list (KR layout, not verified in JP).
	struct sRecentMatchForm;

	static const WRTTI m_RTTI;                                // 0xe7bbec
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x81e1b0)

	FrRecentMatch(void);                                      // 0x81e050
	virtual ~FrRecentMatch(void);                             // 1 (0x81f900, ??_G 0x820290)

	void Exception(void);                                     // 0x818a80

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1e888
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x818a20)

private:
	const Bitmap* m_pCourseImg;   // 0x110
	const Bitmap* m_pItemImg;     // 0x114
	const Bitmap* m_pPangImg;     // 0x118 (not set by the constructor)
	int m_number1;                // 0x11c
	int m_number2;                // 0x120
	FrListBox* m_pHistoryList;    // 0x124 ("match_list")
	std::list<sRecentMatchForm*> m_history;   // 0x128
	FrArea* m_pBgArea;            // 0x134 ("bg_area")
	FrStatic* m_pStaticText1;     // 0x138 ("text1"; Exception sets its caption)
	WTitleFont* m_pTitleFont;     // 0x13c
	std::string m_string140;      // 0x140 (the ghost's nick, Init)
	PADDING(0x15c, 0x160);
};

CHECK_SIZE(FrRecentMatch, 0x160);
BEGIN_LAYOUT_CHECK(FrRecentMatch)
	CHECK_FIELD(FrRecentMatch, m_pCourseImg, 0x110);
	CHECK_FIELD(FrRecentMatch, m_pPangImg, 0x118);
	CHECK_FIELD(FrRecentMatch, m_number1, 0x11c);
	CHECK_FIELD(FrRecentMatch, m_pHistoryList, 0x124);
	CHECK_FIELD(FrRecentMatch, m_history, 0x128);
	CHECK_FIELD(FrRecentMatch, m_pBgArea, 0x134);
	CHECK_FIELD(FrRecentMatch, m_pStaticText1, 0x138);
	CHECK_FIELD(FrRecentMatch, m_pTitleFont, 0x13c);
	CHECK_FIELD(FrRecentMatch, m_string140, 0x140);
END_LAYOUT_CHECK

// Map selection dialog of the ghost game (RTTI FrGhostGameMapDlg : FrForm;
// vtables 0xd2f0bc (GetRTTI 0x81f370, the destructor ??_G 0x81fc60, OnProc
// 0x81c660 at 9), 0xd2f0b0 (FrCmdTarget) and 0xd2f0a8). Only what the
// bodies so far need: the members (KR: two vectors, a list of
// GHOST_GAME_BRIEF, two strings) are not modelled yet, so no constructor
// is defined here and the vtable is not emitted.
class FrGhostGameMapDlg : public FrForm {
public:
	static const WRTTI m_RTTI;                                // 0xe7bbf8
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x81f370)

	FrGhostGameMapDlg(void);
	virtual ~FrGhostGameMapDlg(void);                         // 1 (0x81f1f0, ??_G 0x81fc60)

	// One map's picture sliding in (KR layout; Reset 0x818b90 confirms 0x28-0x30).
	struct sImgTag {
		const Bitmap* m_pBitmap;     // 0x00
		const Bitmap* m_pEndBitmap;  // 0x04
		WRect m_rect;                // 0x08
		WRect m_endRect;             // 0x18
		float m_current;             // 0x28
		float m_alpha;               // 0x2c
		float m_alphaEnd;            // 0x30

		void Reset(void);            // 0x818b90
	};

	// One map's lock state (KR layout; AnimateLock 0x818bb0 confirms 0x0c-0x12).
	struct sImgInfo {
		float m_x;                   // 0x00
		float m_y;                   // 0x04
		float m_unknown08;           // 0x08
		float m_lockOffset;          // 0x0c
		bool m_flag10;               // 0x10
		bool m_flag11;               // 0x11
		bool m_flag12;               // 0x12
		int m_mapId;                 // 0x14
		bool m_flag18;               // 0x18

		void AnimateLock(float dt);  // 0x818bb0
	};

	virtual void OnProc(const float dt);                      // 9 (0x81c660)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1e890
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x818aa0)

	PADDING(0x110, 0x1a0);
};

CHECK_SIZE(FrGhostGameMapDlg::sImgTag, 0x34);
CHECK_FIELD(FrGhostGameMapDlg::sImgTag, m_current, 0x28);
CHECK_FIELD(FrGhostGameMapDlg::sImgTag, m_alpha, 0x2c);
CHECK_FIELD(FrGhostGameMapDlg::sImgTag, m_alphaEnd, 0x30);
CHECK_SIZE(FrGhostGameMapDlg::sImgInfo, 0x1c);
CHECK_FIELD(FrGhostGameMapDlg::sImgInfo, m_lockOffset, 0x0c);
CHECK_FIELD(FrGhostGameMapDlg::sImgInfo, m_flag10, 0x10);
CHECK_FIELD(FrGhostGameMapDlg::sImgInfo, m_flag12, 0x12);
CHECK_FIELD(FrGhostGameMapDlg::sImgInfo, m_mapId, 0x14);

// Award screen of the ghost game (RTTI FrGhostAward : FrForm; vtables
// 0xd2effc (GetRTTI 0x81e4e0, the destructor ??_G 0x81f570, OnProc 0x81e6c0
// at 9), 0xd2eff0 (FrCmdTarget) and 0xd2efe8). The members keep their KR
// offsets (constructor 0x81e320).
class FrGhostAward : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7bc08
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x81e4e0)

	FrGhostAward(void);                                       // 0x81e320
	virtual ~FrGhostAward(void);                              // 1 (0x81e510, ??_G 0x81f570)

	// A pang coin flying into the pouch (KR layout).
	class cPangFx {
	public:
		cPangFx(void);
		~cPangFx(void);                  // 0x818f60
		bool IsAlive(void);              // 0x818f70
		void Proc(float dt);             // 0x818f90
		void Render(FrGraphicInterface* pGI);   // 0x819010

		const Bitmap* m_pBitmap;  // 0x00
		WRect m_rect;             // 0x04
		float m_speed;            // 0x14
		float m_alpha;            // 0x18
		float m_targetY;          // 0x1c
	};

	// One side's result (KR layout; the constructor builds both strings).
	struct sResultInfo {
		std::string m_name;          // 0x00
		WPoint m_pos;                // 0x1c
		std::string m_levelImage;    // 0x24
		unsigned long m_gameResult;  // 0x40
		unsigned long m_exp;         // 0x44
		bool m_isGhost;              // 0x48
	};

	virtual void OnProc(const float dt);                      // 9 (0x81e6c0)
	bool IsFinishCalcBonus(void);                             // 0x819060

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1e8a0
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x818f50)

private:
	FrForm* m_pTimeBar;           // 0x110 (KR FrGhostTimeBar*)
	FrArea* m_pPouchArea;         // 0x114 ("bg_pouch")
	FrGaugeBar* m_pExpGauge;      // 0x118 ("gauge_exp")
	FrStatic* m_pDescText;        // 0x11c ("text_desc")
	FrStatic* m_pGaugeText;       // 0x120 ("gauge_text")
	PADDING(0x124, 0x12c);
	std::list<cPangFx*> m_pangFxList;   // 0x12c
	float m_calcBonusTime;        // 0x138
	unsigned char m_clickCount;   // 0x13c
	WTitleFont* m_pTitleFont;     // 0x140
	int m_autoBonus;              // 0x144
	int m_clickBonus;             // 0x148 (10 in the constructor)
	int m_basePang;               // 0x14c
	float m_shownBasePang;        // 0x150
	int m_gainExp;                // 0x154
	int m_remainExp;              // 0x158
	sResultInfo m_myResult;       // 0x15c
	sResultInfo m_ghostResult;    // 0x1a8
	PADDING(0x1f4, 0x1f8);
};

CHECK_SIZE(FrGhostAward::cPangFx, 0x20);
CHECK_FIELD(FrGhostAward::cPangFx, m_rect, 0x04);
CHECK_FIELD(FrGhostAward::cPangFx, m_targetY, 0x1c);
CHECK_SIZE(FrGhostAward::sResultInfo, 0x4c);
CHECK_FIELD(FrGhostAward::sResultInfo, m_pos, 0x1c);
CHECK_FIELD(FrGhostAward::sResultInfo, m_levelImage, 0x24);
CHECK_FIELD(FrGhostAward::sResultInfo, m_isGhost, 0x48);
CHECK_SIZE(FrGhostAward, 0x1f8);
BEGIN_LAYOUT_CHECK(FrGhostAward)
	CHECK_FIELD(FrGhostAward, m_pTimeBar, 0x110);
	CHECK_FIELD(FrGhostAward, m_pGaugeText, 0x120);
	CHECK_FIELD(FrGhostAward, m_pangFxList, 0x12c);
	CHECK_FIELD(FrGhostAward, m_calcBonusTime, 0x138);
	CHECK_FIELD(FrGhostAward, m_clickCount, 0x13c);
	CHECK_FIELD(FrGhostAward, m_pTitleFont, 0x140);
	CHECK_FIELD(FrGhostAward, m_clickBonus, 0x148);
	CHECK_FIELD(FrGhostAward, m_shownBasePang, 0x150);
	CHECK_FIELD(FrGhostAward, m_remainExp, 0x158);
	CHECK_FIELD(FrGhostAward, m_myResult, 0x15c);
	CHECK_FIELD(FrGhostAward, m_ghostResult, 0x1a8);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_GHOSTGAMEDLG_H
