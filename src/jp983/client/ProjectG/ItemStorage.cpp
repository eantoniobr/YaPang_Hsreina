// Original: d:\build\custom\temp\code\client\projectg\itemstorage.cpp (JP 983 exe)
#include <string.h>

#include "ItemStorage.h"
#include "jp983/new/JpTextCatalog.h"

// 0x7f6dd0
void FrItemCounter::SetType(unsigned long type)
{
    m_type = type;

    switch (type) {
    case 0:
        SetCaption(Jp_LookupText("\xBE\xC6\xC0\xCC\xC5\xDB \xBA\xB8\xB0\xFC\xC7\xCF\xB1\xE2"));
        SetDesc(Jp_LookupText("\xBA\xB8\xB0\xFC\xC7\xD2 \xBE\xC6\xC0\xCC\xC5\xDB\xC0\xC7 \xBC\xF6\xB7\xAE\xC0\xBB \xC0\xD4\xB7\xC2\xC7\xCF\xBC\xBC\xBF\xE4."));
        break;
    case 1:
        SetCaption(Jp_LookupText("\xBE\xC6\xC0\xCC\xC5\xDB \xB0\xA1\xC1\xAE\xBF\xC0\xB1\xE2"));
        SetDesc(Jp_LookupText("\xB0\xA1\xC1\xAE\xBF\xC3 \xBE\xC6\xC0\xCC\xC5\xDB\xC0\xC7 \xBC\xF6\xB7\xAE\xC0\xBB \xC0\xD4\xB7\xC2\xC7\xCF\xBC\xBC\xBF\xE4."));
        break;
    }
}

// 0x7f6e40
unsigned long FrItemCounter::GetType(void) const
{
    return m_type;
}

// 0x7f6e50
const sStoredItemInfo& FrItemConfirm::GetStoredItemInfo(void) const
{
    return m_storedItemInfo;
}

// 0x7f6e60
void FrItemConfirm::SetType(unsigned long type)
{
    m_type = type;

    switch (type) {
    case 0:
        SetCaption(Jp_LookupText("\xBE\xC6\xC0\xCC\xC5\xDB \xBA\xB8\xB0\xFC\xC7\xCF\xB1\xE2"));
        SetDesc(Jp_LookupText("\xBE\xC6\xC0\xCC\xC5\xDB\xC0\xBB \xC3\xA2\xB0\xED\xBF\xA1 \xBA\xB8\xB0\xFC\xC7\xD5\xB4\xCF\xB4\xD9."));
        break;
    case 1:
        SetCaption(Jp_LookupText("\xBE\xC6\xC0\xCC\xC5\xDB \xB0\xA1\xC1\xAE\xBF\xC0\xB1\xE2"));
        SetDesc(Jp_LookupText("\xBE\xC6\xC0\xCC\xC5\xDB\xC0\xBB \xC3\xA2\xB0\xED\xBF\xA1\xBC\xAD \xB0\xA1\xC1\xAE\xBF\xC9\xB4\xCF\xB4\xD9."));
        break;
    }
}

// 0x7f6ed0
unsigned long FrItemConfirm::GetType(void) const
{
    return m_type;
}

// 0x7f6ee0
void FrItemStoragePangBank::SetStoredPang(__int64 pang)
{
    m_storedPang = pang;
}

// 0x7f6f00
__int64 FrItemStoragePangBank::GetStoredPang(void) const
{
    return m_storedPang;
}

// 0x7f6f10
void FrItemStoragePangBank::SetMyPang(__int64 pang)
{
    m_myPang = pang;
}

// 0x7f6f30
__int64 FrItemStoragePangBank::GetMyPang(void) const
{
    return m_myPang;
}

// 0x7f6f40
void FrItemStoragePangBank::SetType(unsigned long type)
{
    m_type = type;

    switch (type) {
    case TYPE_DEPOSIT:
        SetCaption(Jp_LookupText("\xC6\xCE \xBA\xB8\xB0\xFC\xC7\xCF\xB1\xE2"));
        SetDesc(Jp_LookupText("\xBA\xB8\xB0\xFC\xC7\xD2 \xC6\xCE\xC0\xBB \xC0\xD4\xB7\xC2\xC7\xCF\xBC\xBC\xBF\xE4."));
        break;
    case TYPE_WITHDRAW:
        SetCaption(Jp_LookupText("\xC6\xCE \xB0\xA1\xC1\xAE\xBF\xC0\xB1\xE2"));
        SetDesc(Jp_LookupText("\xB0\xA1\xC1\xAE\xBF\xC3 \xC6\xCE\xC0\xBB \xC0\xD4\xB7\xC2\xC7\xCF\xBC\xBC\xBF\xE4."));
        break;
    }
}

// 0x7f6fb0
unsigned long FrItemStoragePangBank::GetType(void) const
{
    return m_type;
}

// 0x7f6fc0
__int64 CItemStorage::GetStoredPang(void) const
{
    return m_storedPang;
}

// 0x7f6fd0
void FrItemStorageNotice::OnProc(const float)
{
}

// 0x7f6fe0
void FrItemStorageNotice::OnDraw(void)
{
}

// 0x7f6ff0
IObject* FrItemStorageNoticeMakeInstance(void)
{
    return new FrItemStorageNotice;
}

struct __sFrItemStorageNotice {
    // 0x7f7060
    __sFrItemStorageNotice(void)
    {
        ObjectFactory().AddObjectFunctor(FrItemStorageNoticeMakeInstance, "FrItemStorageNotice");
    }
};
static __sFrItemStorageNotice s_registerFrItemStorageNotice;

// 0x7f7080
const sFRESH_MSGMAP* FrItemStorageNotice::GetMessageMap(void) const
{
    return &FrItemStorageNotice::_MsgMap;
}

// 0x7f7090
void FrItemStorageNotice::OnLBDownConfirm(void)
{
    Close(true);
}

// 0x7f7230
const WRTTI* FrItemStorageAccessPanel::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x7f7260
bool FrItemStorageAccessPanel::DiffPassword(void)
{
    bool ret = false;

    if (strcmp(m_newPassword, m_confirmPassword) == 0) {
        ret = true;
    }

    return ret;
}

// 0x7f72a0
IObject* FrItemStorageAccessPanelMakeInstance(void)
{
    return new FrItemStorageAccessPanel;
}

struct __sFrItemStorageAccessPanel {
    // 0x7f7310
    __sFrItemStorageAccessPanel(void)
    {
        ObjectFactory().AddObjectFunctor(FrItemStorageAccessPanelMakeInstance, "FrItemStorageAccessPanel");
    }
};
static __sFrItemStorageAccessPanel s_registerFrItemStorageAccessPanel;

// 0x7f7330
const sFRESH_MSGMAP* FrItemStorageAccessPanel::GetMessageMap(void) const
{
    return &FrItemStorageAccessPanel::_MsgMap;
}

// 0x7f75a0
const sFRESH_MSGMAP* FrItemCounter::GetMessageMap(void) const
{
    return &FrItemCounter::_MsgMap;
}

// 0x7f75b0
void FrItemCounter::OnLBDownCancel(void)
{
    Close(FrCANCEL, true);
}

// 0x7f75c0
FrItemStoragePangBank::FrItemStoragePangBank(void)
{
    m_pDrawArea = 0;
    m_pInput = 0;
    m_pConfirmBn = 0;
    m_pCancelBn = 0;
    m_storedPang = 0;
    m_myPang = 0;
}

// 0x7f7650
IObject* FrItemStoragePangBankMakeInstance(void)
{
    return new FrItemStoragePangBank;
}

struct __sFrItemStoragePangBank {
    // 0x7f76c0
    __sFrItemStoragePangBank(void)
    {
        ObjectFactory().AddObjectFunctor(FrItemStoragePangBankMakeInstance, "FrItemStoragePangBank");
    }
};
static __sFrItemStoragePangBank s_registerFrItemStoragePangBank;

// 0x7f76e0
const sFRESH_MSGMAP* FrItemStoragePangBank::GetMessageMap(void) const
{
    return &FrItemStoragePangBank::_MsgMap;
}

// 0x7f76f0
void FrItemStoragePangBank::OnLBDownCancel(void)
{
    Close(FrCANCEL, true);
}

// 0x7f7730
const sFRESH_MSGMAP* FrItemConfirm::GetMessageMap(void) const
{
    return &FrItemConfirm::_MsgMap;
}

// 0x7f7740
void FrItemConfirm::OnLBDownCancel(void)
{
    Close(FrCANCEL, true);
}

// 0x7f8060: KR globalnetworkdefine.h in-class inline; the JP copy is here.
void sStoredItemInfo::SetTypeID(unsigned long typeId)
{
    item.typeId = typeId;
}

// 0x7f8070
void sStoredItemInfo::SetGuid(unsigned long guid)
{
    item.guid = guid;
}

// 0x7f8080
unsigned long sStoredItemInfo::GetCount(void) const
{
    return item.count;
}

// 0x7f8090
void sStoredItemInfo::SetCount(unsigned long count)
{
    item.count = count;
}

// 0x7f9270
FrItemConfirm::FrItemConfirm(void)
{
    m_pDrawArea = 0;
    m_pConfirmBn = 0;
    m_pCancelBn = 0;
    memset(&m_storedItemInfo, 0, sizeof(m_storedItemInfo));
}

// 0x7f9300
IObject* FrItemConfirmMakeInstance(void)
{
    return new FrItemConfirm;
}

struct __sFrItemConfirm {
    // 0x7f9370
    __sFrItemConfirm(void)
    {
        ObjectFactory().AddObjectFunctor(FrItemConfirmMakeInstance, "FrItemConfirm");
    }
};
static __sFrItemConfirm s_registerFrItemConfirm;

// 0x7faf80
FrItemCounter::FrItemCounter(void)
{
    m_pDrawArea = 0;
    m_pInput = 0;
    m_pConfirmBn = 0;
    m_pCancelBn = 0;
    memset(&m_storedItemInfo, 0, sizeof(m_storedItemInfo));
}

// 0x7fafe0
IObject* FrItemCounterMakeInstance(void)
{
    return new FrItemCounter;
}

struct __sFrItemCounter {
    // 0x7fb050
    __sFrItemCounter(void)
    {
        ObjectFactory().AddObjectFunctor(FrItemCounterMakeInstance, "FrItemCounter");
    }
};
static __sFrItemCounter s_registerFrItemCounter;
