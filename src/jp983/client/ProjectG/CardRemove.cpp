// Original: d:\build\custom\temp\code\client\projectg\cardremove.cpp (JP 983 exe)
#include "CardRemove.h"

#include <string.h>

#include "client/FreshNext/include/fresh.h"
#include "client/FreshNext/include/frarea.h"
#include "client/FreshNext/include/frwndmanager.h"
#include "client/FreshNext/include/frgraphicinterface.h"
#include "jp983/client/Wangreal/include/bitmap.h"
#include "jp983/client/ProjectG/Packet.h"
#include "jp983/new/JpTextCatalog.h"
#include "jp983/client/ProjectG/commonutil.h"

// 0x7fe440
bool FrCardRemove::OnInit(void)
{
	for (int i = 0; i <= 5; ++i)
		m_pBitmaps[i] = data_f022d0->GetBitmap(MakeStr("card_remove_bg_%d", i + 1));

	m_pBitmaps[6] = data_f022d0->GetBitmap("itemlist_button_n");
	m_pBitmaps[7] = data_f022d0->GetBitmap("itemlist_button_o");

	return FrForm::OnInit();
}

// 0x7fe4b0
void FrCardRemove::SetCardRemoveItem(unsigned long itemTypeId, unsigned long itemId)
{
	m_cardRemoveItemTypeId = itemTypeId;
	m_cardRemoveItemId = itemId;
}

// 0x7fe4d0
bool FrCardRemove::SetCurPartUid(unsigned long partUid)
{
	bool changed = false;
	if (partUid != m_curPartUid) {
		m_curPartUid = partUid;
		changed = true;
	}

	return changed;
}

// 0x7fe4f0
const sFRESH_MSGMAP* FrCardRemove::GetMessageMap(void) const
{
	return &FrCardRemove::_MsgMap;
}

// 0x7fe500 (no reference besides the message map)
void FrCardRemove::OnItemListDBClick(void)
{
}

// 0x7fe510 (the result callback FrCardRemove::OnConfirmLBDown opens the
// confirmation with)
bool FrCardRemove::OnUseCardRemoveConfirm(int result, FrForm* pForm)
{
	if (result == FrOK) {
		if (IsCardRemoveItem(m_cardRemoveItemTypeId) == true) {
			// KR GCT_USE_CARD_REMOVE_REQ (0xE2); JP id 0xE0, not yet in
			// jp983/shared/packet.h.
			WSendPacket packet((enumClientPacket)0xE0);
			packet.Encode4(m_cardRemoveItemTypeId);
			packet.Encode4(m_cardRemoveItemId);
			packet.Encode4(m_curPartTypeId);
			packet.Encode4(m_curPartUid);
			packet.Send(SEND_TO_DEFAULT);
		}

		Close(true);
	}

	return true;
}

// 0x7fe5e0 (no reference besides the message map)
void FrCardRemove::OnCancelLBDown(void)
{
	Close(true);
}

// 0x7fe5f0
FrCardRemoveConfirm::FrCardRemoveConfirm(void) : m_partTypeId(0), m_partId(0)
{
}

// 0x7fe630
FrCardRemoveConfirm::~FrCardRemoveConfirm(void)
{
}

// 0x7fe650
IObject* FrCardRemoveConfirmMakeInstance(void)
{
	return new FrCardRemoveConfirm;
}

struct __sFrCardRemoveConfirm {
	// 0x7fe6c0
	__sFrCardRemoveConfirm(void)
	{
		ObjectFactory().AddObjectFunctor(FrCardRemoveConfirmMakeInstance, "FrCardRemoveConfirm");
	}
};
static __sFrCardRemoveConfirm s_registerFrCardRemoveConfirm;

// 0x7fe6e0
const sFRESH_MSGMAP* FrCardRemoveConfirm::GetMessageMap(void) const
{
	return &FrCardRemoveConfirm::_MsgMap;
}

// 0x7fe6f0 (no reference besides the message map)
void FrCardRemoveConfirm::OnConfirmLBDown(void)
{
	if (m_partTypeId && m_partId) {
		Close(FrOK, true);
	} else {
		Close(true);
	}
}

// 0x7fe720 (no reference besides the message map)
void FrCardRemoveConfirm::OnCancelLBDown(void)
{
	Close(true);
}

// 0x7fe730
const sFRESH_MSGMAP* FrCardRemoveResult::GetMessageMap(void) const
{
	return &FrCardRemoveResult::_MsgMap;
}

// 0x7fe740 (no reference besides the message map)
void FrCardRemoveResult::OnConfirmLBDown(void)
{
	Close(true);
}

// 0x7fe770
void FrCardRemove::DrawInDlg(int index, float x, float y)
{
	const Bitmap* pBitmap = m_pBitmaps[index];
	FrGraphicInterface* pGDI = data_f022d0->GetManager()->GetGDI();

	WRect rect = GetRect();
	rect.x += x + 2.0;
	rect.y += y + 23.0;
	rect.w = (float)pBitmap->Width();
	rect.h = (float)pBitmap->Height();

	pGDI->DrawTexture(pBitmap, rect, 0xFFFFFFFF, 0);
}

// 0x7fe830
void FrCardRemove::DrawTexture(int index, float x, float y, unsigned long diffuse)
{
	const Bitmap* pBitmap = m_pBitmaps[index];
	data_f022d0->GetManager()->GetGDI()->DrawTexture(pBitmap, WRect(x, y, pBitmap->Width(), pBitmap->Height()), diffuse, 0);
}

// 0x7fe920 (no reference besides the message map)
void FrCardRemove::OnDrawAreaInit(intptr_t param)
{
	m_pDrawArea = DYNAMIC_CAST(FrArea, param);
}

// 0x7ffd90
FrCardRemove::FrCardRemove(void)
{
	m_pDrawArea = 0;
	m_pItemList = 0;

	m_cardRemoveItemTypeId = 0;
	m_cardRemoveItemId = 0;

	m_curPartTypeId = 0;
	m_curPartUid = 0;

	m_curPartCardList.clear();

	memset(m_pBitmaps, 0, sizeof(m_pBitmaps));
}

// 0x7feaa0 (no reference besides the message map)
void FrCardRemoveConfirm::OnDrawAreaOwnerDraw(intptr_t param)
{
	FrGraphicInterface* pGDI = data_f022d0->GetManager()->GetGDI();
	if (pGDI) {
		WRect rect = GetRect();
		WPoint pos((float)(rect.x + rect.w * 0.5), (float)(rect.y + 55.0));
		// "Do you want to use the card remover?"
		pGDI->PrintText(pos, 1, Jp_LookupText("\xC4\xAB\xB5\xE5\xC3\xDF\xC3\xE2\xBE\xD7\xC0\xBB \xBB\xE7\xBF\xEB\xC7\xCF\xBD\xC3\xB0\xDA\xBD\xC0\xB4\xCF\xB1\xEE?"), 0);
	}
}

// 0x7fff10
FrCardRemove::~FrCardRemove(void)
{
}

// 0x7fff80
IObject* FrCardRemoveMakeInstance(void)
{
	return new FrCardRemove;
}

struct __sFrCardRemove {
	// 0x7ffff0
	__sFrCardRemove(void)
	{
		ObjectFactory().AddObjectFunctor(FrCardRemoveMakeInstance, "FrCardRemove");
	}
};
static __sFrCardRemove s_registerFrCardRemove;

// 0x800010
FrCardRemoveResult::FrCardRemoveResult(void)
	: m_result((eRESULT)0), m_pCardBitmap(0), m_pCoverMask(0),
	  m_cardRect(0, 0, 0, 0), m_maskRect(0, 0, 0, 0), m_state(0), m_removerTypeId(0)
{
}

// 0x800140
FrCardRemoveResult::~FrCardRemoveResult(void)
{
}

// 0x8006f0
IObject* FrCardRemoveResultMakeInstance(void)
{
	return new FrCardRemoveResult;
}

struct __sFrCardRemoveResult {
	// 0x800760
	__sFrCardRemoveResult(void)
	{
		ObjectFactory().AddObjectFunctor(FrCardRemoveResultMakeInstance, "FrCardRemoveResult");
	}
};
static __sFrCardRemoveResult s_registerFrCardRemoveResult;

// 0xcd9d30 (dynamic initializer)
const WRTTI FrCardRemove::m_RTTI("FrCardRemove", &FrForm::m_RTTI);

// 0xcd9ec0 (dynamic initializer)
const WRTTI FrCardRemoveConfirm::m_RTTI("FrCardRemoveConfirm", &FrForm::m_RTTI);

// 0xcd9fc0 (dynamic initializer)
const WRTTI FrCardRemoveResult::m_RTTI("FrCardRemoveResult", &FrForm::m_RTTI);
