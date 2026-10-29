// Original: d:\build\custom\temp\code\client\projectg\cardremove.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_CARDREMOVE_H
#define PG_JP983_CLIENT_PROJECTG_CARDREMOVE_H

#include <stdint.h>
#include <list>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "jp983/client/Wangreal/include/wtypes.h"
#include "client/FreshNext/include/frform.h"

class Bitmap;
class FrArea;
class FrListBox;
struct sFRESH_ENTRY;

IObject* FrCardRemoveMakeInstance(void);          // 0x7fff80
IObject* FrCardRemoveConfirmMakeInstance(void);   // 0x7fe650
IObject* FrCardRemoveResultMakeInstance(void);    // 0x8006f0

// "Card remover" form of My Room (RTTI FrCardRemove : FrForm; vtables
// 0xd2b8cc (38 slots: GetRTTI, the destructor and OnInit at 32
// overridden), 0xd2b8c0 (FrCmdTarget) and 0xd2b8b8 (FrModalRenderer)).
// Size 0x160, the `new` of FrCardRemoveMakeInstance (KR 0x138): the KR
// members keep their offsets (SetCardRemoveItem 0x7fe4b0, SetCurPartUid
// 0x7fe4d0, the destructor 0x7fff10); JP adds the background and item
// button bitmaps OnInit loads.
class FrCardRemove : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7baf8
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x7ffee0)

	FrCardRemove(void);
	virtual ~FrCardRemove(void);                              // 1 (0x7fff10, ??_G 0x8001b0)

	static bool IsCardRemoveItem(unsigned long itemTypeId);   // 0x7fe420

	void SetCardRemoveItem(unsigned long itemTypeId, unsigned long itemId);   // 0x7fe4b0

protected:
	bool SetCurPartUid(unsigned long partUid);                // 0x7fe4d0
	// KR took a bitmap name; JP an index into m_pBitmaps.
	void DrawInDlg(int index, float x, float y);                             // 0x7fe770
	void DrawTexture(int index, float x, float y, unsigned long diffuse);   // 0x7fe830

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d1b0
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x7fe4f0)

	virtual bool OnInit(void);                                // 32 (0x7fe440)

	void OnItemListDBClick(void);                             // 0x7fe500
	bool OnUseCardRemoveConfirm(int result, FrForm* pForm);   // 0x7fe510
	void OnCancelLBDown(void);                                // 0x7fe5e0
	void OnDrawAreaInit(intptr_t param);                      // 0x7fe920

	FrArea* m_pDrawArea;                          // 0x110, "draw_area"
	FrListBox* m_pItemList;                       // 0x114, "item_list"
	unsigned long m_cardRemoveItemTypeId;         // 0x118, card remover item in use (SetCardRemoveItem)
	unsigned long m_cardRemoveItemId;             // 0x11C
	unsigned long m_curPartTypeId;                // 0x120, part chosen in the list
	unsigned long m_curPartUid;                   // 0x124
	std::list<unsigned long> m_curPartCardList;   // 0x128, cards of the chosen part
	// 0x134, loaded by OnInit: 0-5 "card_remove_bg_1".."card_remove_bg_6",
	// 6 "itemlist_button_n", 7 "itemlist_button_o" (the constructor clears
	// all eight with one memset)
	const Bitmap* m_pBitmaps[8];
	UNKNOWN(0x154, 0x160);
};

CHECK_SIZE(FrCardRemove, 0x160);
BEGIN_LAYOUT_CHECK(FrCardRemove)
	CHECK_FIELD(FrCardRemove, m_pDrawArea, 0x110);
	CHECK_FIELD(FrCardRemove, m_pItemList, 0x114);
	CHECK_FIELD(FrCardRemove, m_cardRemoveItemTypeId, 0x118);
	CHECK_FIELD(FrCardRemove, m_cardRemoveItemId, 0x11C);
	CHECK_FIELD(FrCardRemove, m_curPartTypeId, 0x120);
	CHECK_FIELD(FrCardRemove, m_curPartUid, 0x124);
	CHECK_FIELD(FrCardRemove, m_curPartCardList, 0x128);
	CHECK_FIELD(FrCardRemove, m_pBitmaps, 0x134);
END_LAYOUT_CHECK

// "Use the card remover?" confirmation (RTTI FrCardRemoveConfirm : FrForm;
// vtables 0xd2b684, 0xd2b678, 0xd2b670). Size 0x120, the `new` of
// FrCardRemoveConfirmMakeInstance (KR 0x118).
class FrCardRemoveConfirm : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7bb04
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x7fe620)

	FrCardRemoveConfirm(void);                                // 0x7fe5f0
	virtual ~FrCardRemoveConfirm(void);                       // 1 (0x7fe630, ??_G 0x7fea70)

	void SetPart(unsigned long partTypeId, unsigned long partId) {
		m_partTypeId = partTypeId;
		m_partId = partId;
	}

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d1b8
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x7fe6e0)

	void OnConfirmLBDown(void);                               // 0x7fe6f0
	void OnDrawAreaOwnerDraw(intptr_t param);                 // 0x7feaa0
	void OnCancelLBDown(void);                                // 0x7fe720

	unsigned long m_partTypeId;  // 0x110, part whose card is removed (SetPart)
	unsigned long m_partId;      // 0x114
	UNKNOWN(0x118, 0x120);
};

CHECK_SIZE(FrCardRemoveConfirm, 0x120);
BEGIN_LAYOUT_CHECK(FrCardRemoveConfirm)
	CHECK_FIELD(FrCardRemoveConfirm, m_partTypeId, 0x110);
	CHECK_FIELD(FrCardRemoveConfirm, m_partId, 0x114);
END_LAYOUT_CHECK

// Result of a card removal (RTTI FrCardRemoveResult : FrForm; vtables
// 0xd2b98c (OnProc at 9 and OnInit at 32 overridden), 0xd2b980, 0xd2b978).
// Size 0x150 as in KR (FrCardRemoveResultMakeInstance; constructor 0x800010,
// destructor 0x800140).
class FrCardRemoveResult : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	// The enumerators are not named yet.
	enum eRESULT {
	};

	static const WRTTI m_RTTI;                                // 0xe7bb0c
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x800110)

	FrCardRemoveResult(void);                                 // 0x800010
	virtual ~FrCardRemoveResult(void);                        // 1 (0x800140, ??_G 0x800780)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d1c0
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x7fe730)

	void OnConfirmLBDown(void);                               // 0x7fe740

	eRESULT m_result;                     // 0x110
	std::list<unsigned long> m_cardList;  // 0x114, removed cards
	const Bitmap* m_pCardBitmap;          // 0x120
	const Bitmap* m_pCoverMask;           // 0x124
	WRect m_cardRect;                     // 0x128
	WRect m_maskRect;                     // 0x138
	int m_state;                          // 0x148
	unsigned long m_removerTypeId;        // 0x14C
};

CHECK_SIZE(FrCardRemoveResult, 0x150);
BEGIN_LAYOUT_CHECK(FrCardRemoveResult)
	CHECK_FIELD(FrCardRemoveResult, m_result, 0x110);
	CHECK_FIELD(FrCardRemoveResult, m_cardList, 0x114);
	CHECK_FIELD(FrCardRemoveResult, m_pCardBitmap, 0x120);
	CHECK_FIELD(FrCardRemoveResult, m_pCoverMask, 0x124);
	CHECK_FIELD(FrCardRemoveResult, m_cardRect, 0x128);
	CHECK_FIELD(FrCardRemoveResult, m_maskRect, 0x138);
	CHECK_FIELD(FrCardRemoveResult, m_state, 0x148);
	CHECK_FIELD(FrCardRemoveResult, m_removerTypeId, 0x14C);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_CARDREMOVE_H
