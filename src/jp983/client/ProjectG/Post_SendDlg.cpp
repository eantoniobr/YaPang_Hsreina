// Original: d:\build\custom\temp\code\client\projectg\post_senddlg.cpp (JP 983 exe)
#include "Post_SendDlg.h"

#include <stdlib.h>

#include "client/FreshNext/include/fredit.h"

// 0x80b0b0
const sFRESH_MSGMAP* CPost_SendDlg::GetMessageMap(void) const
{
	return &CPost_SendDlg::_MsgMap;
}

// 0x80b0c0 (no reference found)
bool __stdcall UnreferencedTrue_0080b0c0(int)
{
	return true;
}

// 0x80b0d0
bool CPost_SendDlg::OnSendQuestionResult(int ret, FrForm* pForm)
{
	if (ret == FrOK) {
		SetFadeout(true);
		FrForm::OnOK();
	}
	return true;
}

// 0x80b100
const sFRESH_MSGMAP* CPost_MyItemList::GetMessageMap(void) const
{
	return &CPost_MyItemList::_MsgMap;
}

// 0x80b1f0 (no reference found)
void UnreferencedEmpty_0080b1f0(void)
{
}

// 0x80b200 (no reference found)
void UnreferencedEmpty_0080b200(void)
{
}

// 0x80b210 (no reference found)
void UnreferencedEmpty_0080b210(void)
{
}

// 0x80b220 (no reference found)
void UnreferencedEmpty_0080b220(void)
{
}

// 0x80b230
void CPost_MyItemList::OnOK(void)
{
	FrForm::OnOK();
}

// 0x80b250
CPost_ItemCountDlg::CPost_ItemCountDlg(void)
{
	m_pMinusBtn = 0;
	m_pPluseBtn = 0;
	m_pCountEdit = 0;
	m_count = 1;
}

// 0x80b2a0
CPost_ItemCountDlg::~CPost_ItemCountDlg(void)
{
}

// 0x80b2c0
IObject* CPost_ItemCountDlgMakeInstance(void)
{
	return new CPost_ItemCountDlg;
}

struct __sCPost_ItemCountDlg {
	// 0x80b330
	__sCPost_ItemCountDlg(void)
	{
		ObjectFactory().AddObjectFunctor(CPost_ItemCountDlgMakeInstance, "CPost_ItemCountDlg");
	}
};
static __sCPost_ItemCountDlg s_registerCPost_ItemCountDlg;

// 0x80b350
const sFRESH_MSGMAP* CPost_ItemCountDlg::GetMessageMap(void) const
{
	return &CPost_ItemCountDlg::_MsgMap;
}

// 0x80b3b0
void CPost_ItemCountDlg::SetSelectItem(unsigned long item, int count)
{
	m_selectItem = item;
	m_selectCount = count;
}

// 0x80b3d0
unsigned long CPost_ItemCountDlg::GetSelectItem(void)
{
	return m_selectItem;
}

// 0x80b3e0
bool CPost_ItemCountDlg::OnPostEditItemCountEnterKey(int)
{
	OnOK();
	return true;
}

// 0x80bf40
int CPost_ItemCountDlg::GetCount(void)
{
	m_count = atoi(m_pCountEdit->GetLine(1, false));
	int maxCount = m_selectCount;
	m_count = m_count < 1 ? 1 : (m_count > maxCount ? maxCount : m_count);
	return m_count;
}

// 0x80d240
IObject* CPost_MyItemListMakeInstance(void)
{
	return new CPost_MyItemList;
}

struct __sCPost_MyItemList {
	// 0x80d2b0
	__sCPost_MyItemList(void)
	{
		ObjectFactory().AddObjectFunctor(CPost_MyItemListMakeInstance, "CPost_MyItemList");
	}
};
static __sCPost_MyItemList s_registerCPost_MyItemList;

// 0x80e830 (no reference found)
void UnreferencedEmpty_0080e830(void)
{
}

// 0x80ea10
bool CPost_MyItemList::OnInit(void)
{
	SetList();
	return true;
}

// 0x80f3c0
IObject* CPost_SendDlgMakeInstance(void)
{
	return new CPost_SendDlg;
}

struct __sCPost_SendDlg {
	// 0x80f430
	__sCPost_SendDlg(void)
	{
		ObjectFactory().AddObjectFunctor(CPost_SendDlgMakeInstance, "CPost_SendDlg");
	}
};
static __sCPost_SendDlg s_registerCPost_SendDlg;

// Not the original constructors (not written yet): defined so that the
// vtables, GetRTTI and the ??_E thunks are emitted.
CPost_SendDlg::CPost_SendDlg(void)
{
}

CPost_MyItemList::CPost_MyItemList(void)
{
}

// 0xcdab50 (dynamic initializer)
const WRTTI CPost_SendDlg::m_RTTI("CPost_SendDlg", &FrForm::m_RTTI);
// 0xcdad80 (dynamic initializer)
const WRTTI CPost_MyItemList::m_RTTI("CPost_MyItemList", &FrForm::m_RTTI);
const WRTTI CPost_ItemCountDlg::m_RTTI("CPost_ItemCountDlg", &FrForm::m_RTTI);
