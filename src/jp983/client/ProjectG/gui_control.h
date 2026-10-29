// Original: d:\build\custom\temp\code\client\projectg\gui_control.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_GUI_CONTROL_H
#define PG_JP983_CLIENT_PROJECTG_GUI_CONTROL_H

#include "defines.h"
#include "padding.h"

class WRTTI;
class WPoint;
class WRect;
class CChatMsg;
class FrChatFuncDlg;
class FrForm;
class FrWndManager;
struct FrInputState;
struct sFRESH_MSGMAP;

// Minimal stand-ins for the gui_control classes of the JP exe: only the
// members the bodies of this unit touch, at their JP offsets. The real bases
// (CTaskMain, FrForm, FrCmdTarget) are not modelled yet.

// A two-byte state object of CScreen (new'd into CScreen + 0x250 by the
// JP constructor 0x7517b0); its constructor calls Reset.
class CScreenState250 {
	LAYOUT_CHECK_FRIEND;
public:
	CScreenState250(void);
	void Reset(void);

private:
	bool m_active;      // 0x00, cleared by Reset
	PADDING(0x01, 0x02);
};

CHECK_SIZE(CScreenState250, 0x02);
BEGIN_LAYOUT_CHECK(CScreenState250)
	CHECK_FIELD(CScreenState250, m_active, 0x00);
END_LAYOUT_CHECK

// A five-byte flag object of CScreen (new'd into CScreen + 0x260 by the JP
// constructor 0x7517b0); HandleMsg sets the first flag.
class CScreenFlags260 {
	LAYOUT_CHECK_FRIEND;
public:
	CScreenFlags260(void);
	void Reset(void);
	void SetFirstFlag(bool flag);

private:
	PADDING(0x00, 0x01);
	bool m_flags[4];    // 0x01, cleared by Reset
};

CHECK_SIZE(CScreenFlags260, 0x05);
BEGIN_LAYOUT_CHECK(CScreenFlags260)
	CHECK_FIELD(CScreenFlags260, m_flags, 0x01);
END_LAYOUT_CHECK

// The round screen (HUD) task (vtable 0xd211fc). Only slot 0 is declared.
class CScreen {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;   // 0xe79f94
	virtual const WRTTI* GetRTTI(void) const;   // slot 0

	void SetUnknown4D5(bool flag);
	bool GetUnknown4D5(void);
	void DrawLimitedTime(void);       // 0x74cd20, the GP special rule "limited time" counter
	void DrawLimitedTimeRule(void);

private:
	PADDING(0x004, 0x4D5);
	bool m_unknown4D5;           // 0x4D5, HandleMsg sets it; the draw at 0x74cd20 runs while set
};

BEGIN_LAYOUT_CHECK(CScreen)
	CHECK_FIELD(CScreen, m_unknown4D5, 0x4D5);
END_LAYOUT_CHECK

// Option menu of the round screen (KR size 0x30).
class CAuxMenuUI {
	LAYOUT_CHECK_FRIEND;
private:
	bool OnChatFuncDlgResult(int ret, FrForm* pForm);

	PADDING(0x00, 0x2C);
	FrChatFuncDlg* m_pChatFuncDlg;      // 0x2C
};

BEGIN_LAYOUT_CHECK(CAuxMenuUI)
	CHECK_FIELD(CAuxMenuUI, m_pChatFuncDlg, 0x2C);
END_LAYOUT_CHECK

// Chat function dialog, an FrForm (FrForm : FrWnd : IObject, FrCmdTarget;
// FrModalRenderer at 8). Primary vtable 0xd20944 (38 slots), declared up to
// the FrForm Close(ret, bDestroy) this unit calls (slot 26); the FrCmdTarget
// vtable (0xd20934) holds GetMessageMap.
class FrChatFuncDlg {
	LAYOUT_CHECK_FRIEND;
public:
	virtual const WRTTI* GetRTTI(void) const;                             // slot 0
	virtual ~FrChatFuncDlg(void);                                         // slot 1
	virtual bool UnknownSlot2(bool bDestroy);                              // slot 2, FrWnd::Close(bool); named apart so the Close overloads stay at 25-26
	virtual bool Create(const char* name, const char* text, FrWndManager* pWndManager, unsigned long style,
	                    const WRect& rect, void* pParent);                // slot 3
	virtual void PreCreateWindow(FrWndManager* pWndManager, unsigned long style, const WRect& rect,
	                             void* pParent);                          // slot 4
	virtual void MoveWindow(const WPoint& pt);                            // slot 5
	virtual void Enable(bool bEnable);                                    // slot 6
	virtual void SetVisible(bool bVisible);                               // slot 7
	virtual void OnDraw(void);                                            // slot 8
	virtual void OnProc(const float dt);                                  // slot 9
	virtual void OnResize(void);                                          // slot 10
	virtual void OnMouseMove(const WPoint& pt);                           // slot 11
	virtual bool OnLButtonUp(const WPoint& pt);                           // slot 12
	virtual bool OnLButtonDown(const WPoint& pt);                         // slot 13
	virtual bool OnRButtonUp(const WPoint& pt);                           // slot 14
	virtual bool OnRButtonDown(const WPoint& pt);                         // slot 15
	virtual void OnDblClick(const WPoint& pt);                            // slot 16
	virtual void OnWheel(FrInputState& input);                            // slot 17
	virtual const char* OnSelectText(const FrInputState* pInput);         // slot 18
	virtual void OnKeyFocus(CChatMsg* pMsg);                              // slot 19
	virtual void OnSetCursor(bool b, const WPoint& pt);                   // slot 20
	virtual void EnableKeyFocus(FrInputState& input);                     // slot 21
	virtual void UnknownSlot22(void);                                     // slot 22
	virtual void UnknownSlot23(void);                                     // slot 23
	virtual void UnknownSlot24(void);                                     // slot 24
	// cl gives an overload set the slots of its first declaration, in reverse order.
	virtual bool Close(int ret, bool bDestroy);                           // slot 26
	virtual bool Close(bool bDestroy);                                    // slot 25

	static const WRTTI m_RTTI;   // 0xe79fa0

protected:
	void OnBtnCloseDlgUp(void);
	bool OnReportDlgResult(int ret, FrForm* pForm);

	static sFRESH_MSGMAP _MsgMap;   // 0xe17b74
	const sFRESH_MSGMAP* GetMessageMap(void) const;

private:
	PADDING(0x004, 0x128);
	FrForm* m_pReportDlg;        // 0x128, OnBtnAccuseUp
};

BEGIN_LAYOUT_CHECK(FrChatFuncDlg)
	CHECK_FIELD(FrChatFuncDlg, m_pReportDlg, 0x128);
END_LAYOUT_CHECK

// 0.1f; a float variable at 0xd05a2c (no symbol in the JP exe), read where
// the source has the literal.
extern "C" const float data_d05a2c;

// The "recover pangya shot" frame animation of the round screen (JP-only
// RTTI class, vtable 0xd209e0; new'd by the CScreen constructor 0x7517b0,
// run by CScreen::OnProcess). Steps m_frame from 1 to m_frameCount, one step
// per m_period seconds, then stops.
class CRecoverPangyaShotEffect {
	LAYOUT_CHECK_FRIEND;
public:
	CRecoverPangyaShotEffect(void);
	virtual ~CRecoverPangyaShotEffect(void);

	void Reset(void);
	void Process(float elapsed);

private:
	float m_period;              // 0x04, seconds per frame (0.1)
	int m_frameCount;            // 0x08, 4
	bool m_active;               // 0x0C
	int m_frame;                 // 0x10, 1 after Reset
	float m_time;                // 0x14, time in the current frame
};

CHECK_SIZE(CRecoverPangyaShotEffect, 0x18);
BEGIN_LAYOUT_CHECK(CRecoverPangyaShotEffect)
	CHECK_FIELD(CRecoverPangyaShotEffect, m_period, 0x04);
	CHECK_FIELD(CRecoverPangyaShotEffect, m_frameCount, 0x08);
	CHECK_FIELD(CRecoverPangyaShotEffect, m_active, 0x0C);
	CHECK_FIELD(CRecoverPangyaShotEffect, m_frame, 0x10);
	CHECK_FIELD(CRecoverPangyaShotEffect, m_time, 0x14);
END_LAYOUT_CHECK

// The ring of the "recover pangya shot" effect (JP-only RTTI class, vtable
// 0xd209e8). Like CRecoverPangyaShotEffect, with m_printFrame more frames;
// reaching m_printFrame plays the "luck_rainbow_print" sound.
class CRecoverPangyaShotRingEffect {
	LAYOUT_CHECK_FRIEND;
public:
	CRecoverPangyaShotRingEffect(void);
	virtual ~CRecoverPangyaShotRingEffect(void);

	void Reset(void);
	void Process(float elapsed);

private:
	float m_period;              // 0x04, seconds per frame (0.1)
	int m_frameCount;            // 0x08, 4
	int m_printFrame;            // 0x0C, 4
	bool m_active;               // 0x10
	int m_frame;                 // 0x14, 1 after Reset
	float m_time;                // 0x18, time in the current frame
};

CHECK_SIZE(CRecoverPangyaShotRingEffect, 0x1C);
BEGIN_LAYOUT_CHECK(CRecoverPangyaShotRingEffect)
	CHECK_FIELD(CRecoverPangyaShotRingEffect, m_period, 0x04);
	CHECK_FIELD(CRecoverPangyaShotRingEffect, m_frameCount, 0x08);
	CHECK_FIELD(CRecoverPangyaShotRingEffect, m_printFrame, 0x0C);
	CHECK_FIELD(CRecoverPangyaShotRingEffect, m_active, 0x10);
	CHECK_FIELD(CRecoverPangyaShotRingEffect, m_frame, 0x14);
	CHECK_FIELD(CRecoverPangyaShotRingEffect, m_time, 0x18);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_GUI_CONTROL_H
