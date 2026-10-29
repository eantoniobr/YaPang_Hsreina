// Original: d:\build\custom\temp\code\client\projectg\ucceditbrushdlg.cpp (JP 983 exe)
#include "UccEditBrushDlg.h"

#include <stdlib.h>

// 0x7e7d40
void CUccEditBrush::Refresh2D(void)
{
}

// 0x7e7d50
void CUccEditBrush::Refresh3D(void)
{
}

// 0x7e7d60
CUccEditBrush::~CUccEditBrush(void)
{
}

// 0x7e7dc0
void CUccEditBrush::Process(void)
{
	CUccBase::Process();

	RefreshTexCache(m_pTexture);
}

// 0x7e7de0
Bitmap* CUccEditBrush::GetTexture32BPP(void)
{
	Convert24to32(m_pTexture, m_pTexture32, NULL);
	return m_pTexture32;
}

// 0x7e7e90
const sFRESH_MSGMAP* FrUccEditBrushDlg::GetMessageMap(void) const
{
	return &FrUccEditBrushDlg::_MsgMap;
}

// 0x7e7fb0
const WRTTI* FrUccEditBrushDlg::GetRTTI(void) const
{
	return &m_RTTI;
}

// 0x7e82e0
void FrUccEditBrushDlg::SetIndex(eBrushType type, int index)
{
	if (m_brushIndex == -2) {
		m_brushIndex = index;
		m_brushType = type;
		if (m_brushIndex == -1) {
			InitNew();
		} else {
			InitModify();
		}
	}
}

// 0x7e8320
void FrUccEditBrushDlg::OnOKBtnUp(void)
{
	if (m_brushIndex != -2) {
		Bitmap* pBrush = m_editBrush.ProduceOriginalBrush();

		GetGDI();

		if (m_brushIndex == -1) {
			UccBrushList(m_brushType)->AddBrush(pBrush);
		} else {
			UccBrushList(m_brushType)->SetBrush(m_brushIndex, pBrush);

			RefreshTexCache(UccBrushList(m_brushType)->GetBrush(m_brushIndex));
		}
	}

	OnFreshOkay();
}

// 0x7e83a0 (referenced by the message map only)
void FrUccEditBrushDlg::OnCancelBtnUp(void)
{
	OnFreshCancel();
}

// 0x7e8400
void CUccEditBrush::DrawLine(IPoint from, IPoint to, Bitmap* pBrush)
{
	if (pBrush == NULL) {
		return;
	}

	int length = abs(to.x - from.x) < abs(to.y - from.y) ? abs(to.y - from.y) : abs(to.x - from.x);

	float stepX = (float)(to.x - from.x) / length;
	float stepY = (float)(to.y - from.y) / length;

	WPoint pos;
	pos.x = (float)from.x;
	pos.y = (float)from.y;

	while (true) {
		// snap to the centre of the 10x10 cell of the magnified brush
		WPoint pt((float)((int)pos.x / 10 * 10 + 5), (float)((int)pos.y / 10 * 10 + 5));
		Draw((int)pt.x, (int)pt.y, pBrush, false);

		if ((length == abs(to.x - from.x) && pos.x == to.x) || (length == abs(to.y - from.y) && pos.y == to.y)) {
			break;
		}

		pos.x += stepX;
		pos.y += stepY;
	}

	m_refreshFlags |= 4;
}

// 0x7e8540
IObject* FrUccEditBrushDlgMakeInstance(void)
{
	return new FrUccEditBrushDlg;
}

struct __sFrUccEditBrushDlg {
	// 0x7e85b0
	__sFrUccEditBrushDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrUccEditBrushDlgMakeInstance, "FrUccEditBrushDlg");
	}
};
static __sFrUccEditBrushDlg s_registerFrUccEditBrushDlg;

// 0x7e8600
void FrUccEditBrushDlg::OnCanvasInit(intptr_t param)
{
	m_pCanvas = DYNAMIC_CAST(FrArea, param);
	m_editBrush.SetArea(m_pCanvas);
}

// 0xcd8c80 (dynamic initializer)
const WRTTI FrUccEditBrushDlg::m_RTTI("FrUccEditBrushDlg", &FrForm::m_RTTI);
