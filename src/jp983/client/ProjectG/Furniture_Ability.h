// Original: d:\build\custom\temp\code\client\projectg\furniture_ability.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_FURNITURE_ABILITY_H
#define PG_JP983_CLIENT_PROJECTG_FURNITURE_ABILITY_H

#include <stdint.h>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "client/FreshNext/include/frform.h"

class Bitmap;
class FrArea;
class FrButton;
class FrEdit;
class FrListBox;
class WTitleFont;
struct sFRESH_ENTRY;
struct sItemInfo;

// Furniture ability dialog of the room editor (RTTI CFurniture_AbilityDlg :
// FrForm; vtables 0xd2a6a4 (38 slots: GetRTTI and the destructor
// overridden), 0xd2a694 (FrCmdTarget: ??_E thunk, GetMessageMap) and
// 0xd2a68c (FrModalRenderer)). The members keep their KR offsets (the
// handlers 0x7f1520-0x7f1790, the destructor 0x7f13d0). Size from KR (0x150),
// not re-verified in JP.
class CFurniture_AbilityDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7baa0
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x7f14a0)

	CFurniture_AbilityDlg(void);                              // 0x7f1b80
	virtual ~CFurniture_AbilityDlg(void);                     // 1 (0x7f13d0, ??_G 0x7f14f0)

	void OnFurnitureAbility_ItemListInit(intptr_t param);       // 0x7f1520
	void OnFurnitureAbility_ItemListOwnerDraw(intptr_t param);  // 0x7f1810
	void OnFurnitureAbility_ItemListBtnDown(void);              // 0x7f1a80
	void OnFurnitureAbility_ItemListMouseMove(void);            // 0x7f14b0
	void OnFurnitureAbility_ImgSelect(intptr_t param);          // 0x7f1590
	void OnFurnitureAbility_SelectListInit(intptr_t param);     // 0x7f1610
	void OnFurnitureAbility_EditArrayInit(intptr_t param);      // 0x7f1690
	void OnFurnitureAbility_BtnArrayInit(intptr_t param);       // 0x7f1710
	void OnFurnitureAbility_TextImg(intptr_t param);            // 0x7f1790
	void GetItemInfo(sItemInfo* pInfo);                         // 0x7f14c0

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1c508
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x7f13c0)

	void SetList(void);                                       // 0x7f1b20

	FrListBox* m_pItemList;        // 0x110
	FrListBox* m_pSelectList;      // 0x114
	FrArea* m_pImgSelect;          // 0x118
	unsigned long m_value11c;      // 0x11c
	sItemInfo* m_pSelectedItem;    // 0x120
	FrButton* m_pBtnArray;         // 0x124
	FrEdit* m_pEditArray;          // 0x128
	FrArea* m_pTextImg;            // 0x12c
	WTitleFont* m_pTitleFont;      // 0x130
	WTitleFont* m_pNumberFont;     // 0x134
	const Bitmap* m_pSelectNormal; // 0x138, "rmr_select_n"
	const Bitmap* m_pSelectDown;   // 0x13c, "rmr_select_d"
	const Bitmap* m_pLine;         // 0x140, "rmr_line"
	PADDING(0x144, 0x150);
};

CHECK_SIZE(CFurniture_AbilityDlg, 0x150);
BEGIN_LAYOUT_CHECK(CFurniture_AbilityDlg)
	CHECK_FIELD(CFurniture_AbilityDlg, m_pItemList, 0x110);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pSelectList, 0x114);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pImgSelect, 0x118);
	CHECK_FIELD(CFurniture_AbilityDlg, m_value11c, 0x11c);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pSelectedItem, 0x120);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pBtnArray, 0x124);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pEditArray, 0x128);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pTextImg, 0x12c);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pTitleFont, 0x130);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pNumberFont, 0x134);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pSelectNormal, 0x138);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pSelectDown, 0x13c);
	CHECK_FIELD(CFurniture_AbilityDlg, m_pLine, 0x140);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_FURNITURE_ABILITY_H
