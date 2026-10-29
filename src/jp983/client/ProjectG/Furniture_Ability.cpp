// Original: d:\build\custom\temp\code\client\projectg\furniture_ability.cpp (JP 983 exe)
#include "Furniture_Ability.h"

#include "client/FreshNext/include/frarea.h"
#include "client/FreshNext/include/frbutton.h"

// 0x7f13c0
const sFRESH_MSGMAP* CFurniture_AbilityDlg::GetMessageMap(void) const
{
	return &CFurniture_AbilityDlg::_MsgMap;
}

// 0x7f14b0 (KR furniture_ability.cpp:263; the JP message map is not
// readable in the file, so no reference was found)
void CFurniture_AbilityDlg::OnFurnitureAbility_ItemListMouseMove(void)
{
}

// 0x7f14c0 (KR furniture_ability.cpp:380; no reference found)
void CFurniture_AbilityDlg::GetItemInfo(sItemInfo* pInfo)
{
}

// 0x7f1590
void CFurniture_AbilityDlg::OnFurnitureAbility_ImgSelect(intptr_t param)
{
	m_pImgSelect = DYNAMIC_CAST(FrArea, param);
	if (m_pImgSelect) {
		m_pImgSelect->SetVisible(false);
	}
}

// 0x7f1710
void CFurniture_AbilityDlg::OnFurnitureAbility_BtnArrayInit(intptr_t param)
{
	m_pBtnArray = DYNAMIC_CAST(FrButton, param);
	if (m_pBtnArray) {
		m_pBtnArray->SetVisible(false);
	}
}

// 0x7f1790
void CFurniture_AbilityDlg::OnFurnitureAbility_TextImg(intptr_t param)
{
	m_pTextImg = DYNAMIC_CAST(FrArea, param);
	if (m_pTextImg) {
		m_pTextImg->SetVisible(false);
	}
}

// 0x7f1b80: the real constructor (390 bytes, title fonts and SetList) is
// not written yet; this empty one only emits the vtables and ??_G (the
// destructor 0x7f13d0 stays out of line).
CFurniture_AbilityDlg::CFurniture_AbilityDlg(void)
{
}

// 0xcd9120 (dynamic initializer)
const WRTTI CFurniture_AbilityDlg::m_RTTI("CFurniture_AbilityDlg", &FrForm::m_RTTI);
