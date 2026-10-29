// Original: d:\build\custom\temp\code\client\projectg\uccdrawdlg.cpp (JP 983 exe)
// This unit holds the out-of-line copies of WPoint::operator-= and
// WRect::operator- (jp983 wtypes.h).
#define UCCDRAWDLG_WTYPES_INLINE

#include "UccDrawDlg.h"

#include <string.h>

// The message-map entries are zero in the file (their handler pointers are
// filled at run time), so the handlers below have no reference in the
// readable code; they are placed by their KR bodies and the KR source order.

// 0x7e2240: KR's temp-save button handler; the JP dialog calls it from
// OnAskCancelDlgResult.
void FrUccDrawDlg::OnTempSaveBtnUp(void)
{
	SecurityKeyManager()->ReqCreateKey(SK_CONTENT_UCC, m_pItemInfo->m_serial);
	m_bSavingTemporarily = true;
}

// 0x7e2270
bool FrUccDrawDlg::OnSelfDesignDescDlgResult(int ret, FrForm* pForm)
{
	m_pSelfDesignDescDlg = NULL;
	return true;
}

// 0x7e2280: empty, as in KR.
void FrUccDrawDlg::OnTabEmoticonBtnUp(void)
{
}

// 0x7e2290: empty, as in KR.
void FrUccDrawDlg::OnTabTextBtnUp(void)
{
}

// 0x7e22a0
bool FrUccDrawDlg::OnUccSetInfoDlgResult(int ret, FrForm* pForm)
{
	m_pUccSetInfoDlg = NULL;
	if (ret == 1) {
		SecurityKeyManager()->ReqCreateKey(SK_CONTENT_UCC, m_pItemInfo->m_serial);
		m_bSavingTemporarily = true;
	}
	return true;
}

// 0x7e22e0
void FrUccDrawDlg::OnCloseBtnUp(void)
{
	OnCancel();
}

// 0x7e22f0
bool FrUccDrawDlg::OnUccPickColorDlgResult(int ret, FrForm* pForm)
{
	m_pUccPickColorDlg = NULL;
	return true;
}

// 0x7e2300: empty, as in KR.
void FrUccDrawDlg::OnDeleteBtnUp(void)
{
}

// 0x7e2310: empty, as in KR.
void FrUccDrawDlg::OnModifyBtnUp(void)
{
}

// 0x7e2320: empty, as in KR.
void FrUccDrawDlg::OnMakeBtnUp(void)
{
}

// 0x7e2330
void FrUccDrawDlg::OnToolTipOnwerDraw(intptr_t param)
{
	m_toolTipManager.Process();
}

// 0x7e2460
bool FrUccDrawDlg::IsNameEmpty(void)
{
	return strlen(m_name) == 0;
}

// 0x7e2490: no reference found (calls or data); reads the instance pointer
// of a Wangreal singleton.
void* UnreferencedGetInstance_007e2490(void)
{
	return data_e7b9ec;
}

// 0x7e25c0: no reference found (calls or data).
void* UnreferencedIdentity_007e25c0(void* p)
{
	return p;
}

// 0x7e25d0: no reference found (calls or data).
void* UnreferencedIdentity_007e25d0(void* p)
{
	return p;
}

// 0x7e2d90
bool FrUccDrawDlg::Close(eFormRet ret, bool bDestroy)
{
	CloseWaitingForm();
	return FrForm::Close(ret, bDestroy);
}

// 0x7e32f0
void FrUccDrawDlg::OnDragBtnUp(void)
{
	CUccBase* pUccBase = m_pUccBase[m_curSide];
	if (pUccBase->GetMode() == UCC_MODE_MOVE) {
		pUccBase->SetMode(UCC_MODE_DRAW);
		m_overlayCursor.SetCursor(UCC_MODE_DRAW);
	} else {
		pUccBase->SetMode(UCC_MODE_MOVE);
		m_overlayCursor.SetCursor(UCC_MODE_MOVE);
	}
	SetToolbarStatus(m_pDragBtn);
}

// 0x7e3a50
void FrUccDrawDlg::OnPaintBtnUp(void)
{
	m_pUccBase[m_curSide]->SetMode(UCC_MODE_PAINT);
	m_overlayCursor.SetCursor(4);
	SetToolbarStatus(m_pDrawBtn);
}

// 0x7e3af0
void FrUccDrawDlg::OnPickColorBtnUp(void)
{
	m_pUccBase[m_curSide]->SetMode(UCC_MODE_SPOID);
	m_overlayCursor.SetCursor(3);
	SetToolbarStatus(m_pDrawBtn);
}

// 0x7e5540
const WRTTI* FrUccDrawDlg::GetRTTI(void) const
{
	return &m_RTTI;
}

// 0x7e59f0
void FrUccDrawDlg::OnFinishBtnUp(void)
{
	Finish();
}

// 0x7e5a00
bool FrUccDrawDlg::OnAskCompleteDlgResult(int ret, FrForm* pForm)
{
	m_pAskCompleteDlg = NULL;
	if (ret == 1) {
		Finish();
	}
	return true;
}

// The constructor (0x7e5380) is declared only: cl would inline it into the
// factory function, which the original calls out of line.

// 0x7e6160
IObject* FrUccDrawDlgMakeInstance(void)
{
	return new FrUccDrawDlg;
}

struct __sFrUccDrawDlg {
	// 0x7e61d0
	__sFrUccDrawDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrUccDrawDlgMakeInstance, "FrUccDrawDlg");
	}
};
static __sFrUccDrawDlg s_registerFrUccDrawDlg;

// 0x7e6860
void FrUccDrawDlg::OnTabDrawBtnUp(void)
{
	ChangeTab(UCC_TAB_DRAW);
	m_pUccBase[m_curSide]->SetMode(UCC_MODE_DRAW);
	m_overlayCursor.SetCursor(0);
	SetToolbarStatus(m_pDrawBtn);
}

// 0x7e68a0
void FrUccDrawDlg::OnTabPatternBtnUp(void)
{
	ChangeTab(UCC_TAB_PATTERN);
	m_pUccBase[m_curSide]->SetMode(UCC_MODE_DRAW);

	m_overlayCursor.SetCursor(0);
	SetToolbarStatus(m_pTabPatternBtn);
}

// 0x7e6ab0
void FrUccDrawDlg::Reset(void)
{
	eDrawMode mode = m_drawMode;
	sItemInfo* pItemInfo = m_pItemInfo;

	Clear();
	SetUccDrawInfo(mode, pItemInfo, true);
	ChangeTab(UCC_TAB_DRAW);

	for (int i = 1; i >= 0; i--) {
		if (m_pUccBase[i] != NULL) {
			m_pUccBase[i]->m_refreshFlags |= 2;
			m_pUccBase[i]->Process();
		}
	}
}

// 0x7e7120
bool FrUccDrawDlg::OnAskResetDlgResult(int ret, FrForm* pForm)
{
	if (ret == 1) {
		Reset();
	}
	m_pAskResetDlg = NULL;
	return true;
}
