// Original: d:\build\custom\temp\code\client\projectg\ucccopydlg.cpp (JP 983 exe)
#include <string.h>

#include "UccCopyDlg.h"

// The message-map entries of the three dialogs are zero in the file (their
// handler pointers are filled at run time), so the handlers below have no
// reference in the readable code; they are placed by their KR bodies.

// 0x7e0c70
void FrUccCopyDlg::Init(void)
{
    m_pItem = 0;
    m_pConfirmDlg = 0;

    m_pItemBaseNormal = data_f022d0->RegisterBitmap("item_base_n");
    m_pItemBaseOver = data_f022d0->RegisterBitmap("item_base_o");
    m_pItemBaseDown = data_f022d0->RegisterBitmap("item_base_d");
}

// 0x7e0cd0: KR FrUccCopyDlg::OnItemListBtnDown (empty, as in KR).
void FrUccCopyDlg::OnItemListBtnDown(void)
{
}

// 0x7e0ce0
void FrUccCopyDlg::OnCancelBtnUp(void)
{
    OnFreshCancel();
}

// 0x7e0cf0
const sFRESH_MSGMAP* FrUccCopyConfirmDlg::GetMessageMap(void) const
{
    return &FrUccCopyConfirmDlg::_MsgMap;
}

// 0x7e0d30
const WRTTI* FrUccCopyConfirmDlg::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x7e0d60
void FrUccCopyConfirmDlg::OnCancelBtnUp(void)
{
    SetFadeout(true);
    OnFreshCancel();
}

// 0x7e0d80
void FrUccCopyConfirmDlg::Init(sItemInfo* pSrcItem, sItemInfo* pDestItem)
{
    m_pSrcItem = pSrcItem;
    m_pDestItem = pDestItem;

    if (m_pIcon && m_pDestItem) {
        const Bitmap* pIcon = GetUccItemIcon(m_pDestItem);
        if (pIcon) {
            m_pIcon->SetBgImg(pIcon);
        }
    }
}

// 0x7e0dc0
const sFRESH_MSGMAP* FrUccCopyCompletedDlg::GetMessageMap(void) const
{
    return &FrUccCopyCompletedDlg::_MsgMap;
}

// 0x7e0e00
const WRTTI* FrUccCopyCompletedDlg::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x7e0e30
void FrUccCopyCompletedDlg::Init(unsigned long typeId, const char* name)
{
    m_typeId = typeId;
    strncpy(m_name, name, 9);
}

// 0x7e0e60
void FrUccCopyCompletedDlg::OnOkBtnUp(void)
{
    OnFreshOkay();
}

// 0x7e0fe0
void FrUccCopyDlg::OnItemListOwnerDraw(int param)
{
    FrListItem* pListItem = (FrListItem*)param;
    if (!pListItem) {
        return;
    }
    FrGraphicInterface* pGDI = GetGDI();
    if (!pGDI) {
        return;
    }

    const Bitmap* pBase;
    if (pListItem->selected) {
        pBase = m_pItemBaseDown;
    } else if (pListItem->underCursor) {
        pBase = m_pItemBaseOver;
    } else {
        pBase = m_pItemBaseNormal;
    }

    WRect rect(pListItem->pos.x, pListItem->pos.y, (float)pBase->Width(), (float)pBase->Height());
    pGDI->DrawTexture(pBase, rect, 0xffffffff, 0);

    sItemInfo* pItem = (sItemInfo*)pListItem->pData;
    if (!pItem) {
        return;
    }

    const Bitmap* pIcon = GetUccItemIcon(pItem->m_serial);
    const char* pName = GetUccItemName(pItem->m_serial);

    WPoint pos = pListItem->pos;
    if (pIcon) {
        pGDI->DrawTexture(pIcon, WRect(pos.x + 15.0, pos.y + 5.0, (float)pIcon->Width(), (float)pIcon->Height()), 0xffffffff, 0);
    }
    pGDI->PrintText(WPoint(pos.x + 184.0, pos.y + 6.0), 2, pName, 0);
}

// 0x7e1220
bool FrUccCopyDlg::OnUccCopyConfirmDlgResult(int ret, FrForm* pForm)
{
    if (pForm) {
        data_e43438 = true;   // FrForm::ms_bHasTail
    }

    m_pConfirmDlg = 0;
    if (ret == 1) {   // FrOK
        OnFreshOkay();
    }

    return true;
}

// 0x7e1250
IObject* FrUccCopyConfirmDlgMakeInstance(void)
{
    return new FrUccCopyConfirmDlg;
}

struct __sFrUccCopyConfirmDlg {
    // 0x7e12c0
    __sFrUccCopyConfirmDlg(void)
    {
        ObjectFactory().AddObjectFunctor(FrUccCopyConfirmDlgMakeInstance, "FrUccCopyConfirmDlg");
    }
};
static __sFrUccCopyConfirmDlg s_registerFrUccCopyConfirmDlg;

// 0x7e1460
void FrUccCopyConfirmDlg::OnEtcOwnerDraw(int param)
{
    FrGraphicInterface* pGDI = GetGDI();
    if (!pGDI) {
        return;
    }
    if (!m_pDestItem) {
        return;
    }

    sUccClothes* pClothes = UccManager()->FindClothes(m_pDestItem->m_typeId, m_pDestItem->m_uccKey);
    if (pClothes) {
        WRect rect = GetRect();

        WPoint pos(rect.x + 100.0, rect.y + 28.0);
        // "Do you want to copy it?"
        pGDI->PrintText(pos, 0, Jp_LookupText("복제하시겠습니까?"), 0);
        pGDI->SetTextStyle(1);
        pGDI->PrintText(WPoint(pos.x, pos.y + 16.0), 0, pClothes->m_uccName, 0);
        pGDI->SetTextStyle(0);
    }
}

// 0x7e1530
IObject* FrUccCopyCompletedDlgMakeInstance(void)
{
    return new FrUccCopyCompletedDlg;
}

struct __sFrUccCopyCompletedDlg {
    // 0x7e15a0
    __sFrUccCopyCompletedDlg(void)
    {
        ObjectFactory().AddObjectFunctor(FrUccCopyCompletedDlgMakeInstance, "FrUccCopyCompletedDlg");
    }
};
static __sFrUccCopyCompletedDlg s_registerFrUccCopyCompletedDlg;

// 0x7e1730
IObject* FrUccCopyDlgMakeInstance(void)
{
    return new FrUccCopyDlg;
}

struct __sFrUccCopyDlg {
    // 0x7e17a0
    __sFrUccCopyDlg(void)
    {
        ObjectFactory().AddObjectFunctor(FrUccCopyDlgMakeInstance, "FrUccCopyDlg");
    }
};
static __sFrUccCopyDlg s_registerFrUccCopyDlg;
