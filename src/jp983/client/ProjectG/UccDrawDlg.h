// Original: d:\build\custom\temp\code\client\projectg\uccdrawdlg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_UCCDRAWDLG_H
#define PG_JP983_CLIENT_PROJECTG_UCCDRAWDLG_H

#include <stddef.h>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "jp983/client/ProjectG/UccBase.h"
#include "jp983/client/Wangreal/include/wtypes.h"
#include "client/FreshNext/include/frcmdtarget.h"
#include "client/FreshNext/include/frform.h"

class FrUccPickColorDlg;
class FrUccSetInfoDlg;

// Content a security key is requested for (KR securitykeymanager.h; only the
// value this dialog passes is known).
enum eSKContent {
	SK_CONTENT_UCC = 1
};

// KR securitykeymanager.h: only what this unit calls. No jp983 header
// declares it yet.
class CSecurityKeyManager {
public:
	void ReqCreateKey(eSKContent content, unsigned long serial);   // 0x7d8e50
};

CSecurityKeyManager* SecurityKeyManager(void);                     // 0x7d9960

// KR shared/globalgamedefine.h sItemInfo: only the serial this unit reads.
// No jp983 header declares it yet.
struct sItemInfo {
	unsigned long m_serial;    // 0x00
};

// The tool-tip helper (KR ToolTipManager.h CToolTipManager), a member of the
// dialog: only what this unit calls; size from the KR layout.
class CToolTipManager {
public:
	void Process(void);        // 0x7db220

private:
	PADDING(0x00, 0x10);
};

CHECK_SIZE(CToolTipManager, 0x10);

// The cursor drawn over the canvas (KR overlaycursor.h COverlayCursor): only
// the cursor type SetCursor stores. The VS 2010 std::map at 0 is not
// modelled; m_cursorType at 0x10 as in KR (0x67c in the dialog).
class COverlayCursor {
public:
	void SetCursor(int type) { m_cursorType = type; }

private:
	PADDING(0x00, 0x10);
	int m_cursorType;            // 0x10
};

class FrButton;
PG_ENUM_FWD(eDrawMode)

// Tab of the drawing dialog (KR uccdrawdlg.h; ChangeTab's argument).
enum eUccTab {
	UCC_TAB_DRAW = 0,
	UCC_TAB_PATTERN = 1
};

IObject* FrUccDrawDlgMakeInstance(void);   // 0x7e6160

// The UCC drawing dialog (RTTI FrUccDrawDlg : FrForm; vtables 0xd29a84 (38
// slots), 0xd29a74 (FrCmdTarget), 0xd29a6c (FrModalRenderer)). Only the
// members the transcribed bodies use are declared, at their JP offsets (the
// JP dialog has 8 more bytes than KR's from m_pAskCancelDlg on).
// Size 0x8c0 (the `new` of FrUccDrawDlgMakeInstance).
class FrUccDrawDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
	friend IObject* FrUccDrawDlgMakeInstance(void);
public:
	static const WRTTI m_RTTI;   // 0xe7b9f0
	virtual const WRTTI* GetRTTI(void) const;                    // 0 (0x7e5540)

	virtual ~FrUccDrawDlg(void);                                 // 1

	virtual bool Close(eFormRet ret, bool bDestroy);             // 26 (0x7e2d90)

	void Clear(void);                                            // 0x7e2ce0
	void SetUccDrawInfo(eDrawMode mode, sItemInfo* pItemInfo, bool b);   // 0x7e6250

protected:
	FrUccDrawDlg(void);                                          // 0x7e5380

	virtual void OnCancel(void);                                 // 34 (0x7e57a0)

	void CloseWaitingForm(void);                                 // 0x7e2380
	void SetToolbarStatus(FrButton* pButton);                    // 0x7e23c0
	void Reset(void);
	void ChangeTab(eUccTab tab);                                 // 0x7e5fe0
	void Finish(void);                                           // 0x7e5950

	void OnTabEmoticonBtnUp(void);
	void OnTabTextBtnUp(void);
	bool OnUccSetInfoDlgResult(int ret, FrForm* pForm);
	void OnCloseBtnUp(void);
	bool OnUccPickColorDlgResult(int ret, FrForm* pForm);
	void OnDeleteBtnUp(void);
	void OnModifyBtnUp(void);
	void OnMakeBtnUp(void);
	void OnToolTipOnwerDraw(intptr_t param);
	void OnTempSaveBtnUp(void);
	void OnFinishBtnUp(void);
	// 0x7e2270 (JP only): the result callback of the "selfdesigndescimg"
	// form 0x7e58b0 opens.
	bool OnSelfDesignDescDlgResult(int ret, FrForm* pForm);
	// 0x7e2460 (JP only): true while no name has been set.
	bool IsNameEmpty(void);
	void OnDragBtnUp(void);
	void OnTabDrawBtnUp(void);
	void OnTabPatternBtnUp(void);
	void OnPaintBtnUp(void);
	void OnPickColorBtnUp(void);
	bool OnAskCompleteDlgResult(int ret, FrForm* pForm);
	bool OnAskResetDlgResult(int ret, FrForm* pForm);

private:
	sItemInfo* m_pItemInfo;            // 0x110
	CUccBase* m_pUccBase[2];           // 0x114, one canvas per side
	bool m_bSavingTemporarily;         // 0x11c
	PADDING(0x11d, 0x290);
	CToolTipManager m_toolTipManager;  // 0x290
	PADDING(0x2a0, 0x2c5);
	bool m_bCloseAfterSave;            // 0x2c5
	PADDING(0x2c6, 0x2f4);
	FrButton* m_pDragBtn;              // 0x2f4
	PADDING(0x2f8, 0x300);
	FrButton* m_pDrawBtn;              // 0x300, the draw tab button
	FrButton* m_pTabPatternBtn;        // 0x304
	PADDING(0x308, 0x390);
	FrUccSetInfoDlg* m_pUccSetInfoDlg; // 0x390
	FrUccPickColorDlg* m_pUccPickColorDlg; // 0x394
	FrForm* m_pAskCancelDlg;           // 0x398
	FrForm* m_pAskResetDlg;            // 0x39c
	FrForm* m_pAskCompleteDlg;         // 0x3a0
	FrForm* m_pSelfDesignDescDlg;      // 0x3a4, "selfdesigndescimg" (JP only)
	PADDING(0x3a8, 0x3e0);
	int m_curSide;                     // 0x3e0, index into m_pUccBase
	eDrawMode m_drawMode;              // 0x3e4
	char m_name[64];                   // 0x3e8, length not confirmed
	PADDING(0x428, 0x66c);
	COverlayCursor m_overlayCursor;    // 0x66c
	PADDING(0x680, 0x8c0);
};

CHECK_SIZE(FrUccDrawDlg, 0x8c0);

BEGIN_LAYOUT_CHECK(FrUccDrawDlg)
	CHECK_FIELD(FrUccDrawDlg, m_pItemInfo, 0x110);
	CHECK_FIELD(FrUccDrawDlg, m_bSavingTemporarily, 0x11c);
	CHECK_FIELD(FrUccDrawDlg, m_toolTipManager, 0x290);
	CHECK_FIELD(FrUccDrawDlg, m_bCloseAfterSave, 0x2c5);
	CHECK_FIELD(FrUccDrawDlg, m_pUccSetInfoDlg, 0x390);
	CHECK_FIELD(FrUccDrawDlg, m_pUccPickColorDlg, 0x394);
	CHECK_FIELD(FrUccDrawDlg, m_pAskCancelDlg, 0x398);
	CHECK_FIELD(FrUccDrawDlg, m_pSelfDesignDescDlg, 0x3a4);
	CHECK_FIELD(FrUccDrawDlg, m_pUccBase, 0x114);
	CHECK_FIELD(FrUccDrawDlg, m_pDragBtn, 0x2f4);
	CHECK_FIELD(FrUccDrawDlg, m_pDrawBtn, 0x300);
	CHECK_FIELD(FrUccDrawDlg, m_pTabPatternBtn, 0x304);
	CHECK_FIELD(FrUccDrawDlg, m_pAskResetDlg, 0x39c);
	CHECK_FIELD(FrUccDrawDlg, m_pAskCompleteDlg, 0x3a0);
	CHECK_FIELD(FrUccDrawDlg, m_curSide, 0x3e0);
	CHECK_FIELD(FrUccDrawDlg, m_drawMode, 0x3e4);
	CHECK_FIELD(FrUccDrawDlg, m_name, 0x3e8);
	CHECK_FIELD(FrUccDrawDlg, m_overlayCursor, 0x66c);
END_LAYOUT_CHECK

// A Wangreal singleton's instance pointer (0xe7b9ec, no symbol; also read by
// CMouseCursor and CProjectG).
extern "C" void* data_e7b9ec;

#endif // PG_JP983_CLIENT_PROJECTG_UCCDRAWDLG_H
