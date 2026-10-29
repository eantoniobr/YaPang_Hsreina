// Original: d:\build\custom\temp\code\client\projectg\carddlg.cpp (JP 983 exe)
#include "CardDlg.h"

#include <new>

#include "client/FreshNext/include/frarea.h"
#include "client/FreshNext/include/fredit.h"

// 0x800880
const sFRESH_MSGMAP* FrSpCardUseDlg::GetMessageMap(void) const
{
	return &FrSpCardUseDlg::_MsgMap;
}

// 0x800890
FrSpCardUseDlg::FrSpCardUseDlg(void)
{
	m_spCardTid = 0;
	m_overlappedCard = 0;
}

// 0x8008d0
FrSpCardUseDlg::~FrSpCardUseDlg(void)
{
}

// 0x8008f0
const sFRESH_MSGMAP* FrCardUseDlg::GetMessageMap(void) const
{
	return &FrCardUseDlg::_MsgMap;
}

// 0x800900
FrCardUseDlg::FrCardUseDlg(void)
{
	m_cardTypeId = 0;
	m_cardId = 0;

	m_value118 = 0;
	m_value11c = 0;
}

// 0x800950
FrCardUseDlg::~FrCardUseDlg(void)
{
}

// 0x800970
const sFRESH_MSGMAP* FrOpenCardPackDlg::GetMessageMap(void) const
{
	return &FrOpenCardPackDlg::_MsgMap;
}

// 0x800980
FrOpenCardPackDlg::FrOpenCardPackDlg(void)
{
	m_cardTypeId = 0;
	m_cardId = 0;
}

// 0x8009c0
FrOpenCardPackDlg::~FrOpenCardPackDlg(void)
{
}

// 0x8009e0
const sFRESH_MSGMAP* FrOpenCardPackResultDlg::GetMessageMap(void) const
{
	return &FrOpenCardPackResultDlg::_MsgMap;
}

// 0x8009f0
FrOpenCardPackResultDlg::FrOpenCardPackResultDlg(void)
{
	for (int i = 0; i < 3; i++) {
		m_values[i] = 0;
	}
}

// 0x800a40
FrOpenCardPackResultDlg::~FrOpenCardPackResultDlg(void)
{
}

// 0x800a60
const sFRESH_MSGMAP* FrCardAttachDlg::GetMessageMap(void) const
{
	return &FrCardAttachDlg::_MsgMap;
}

// 0x800a90
const sFRESH_MSGMAP* FrItemAttachCardDlg::GetMessageMap(void) const
{
	return &FrItemAttachCardDlg::_MsgMap;
}

// 0x800dc0
const sFRESH_MSGMAP* FrSPCardBuffDlg::GetMessageMap(void) const
{
	return &FrSPCardBuffDlg::_MsgMap;
}

// 0x800dd0
FrSPCardBuffDlg::FrSPCardBuffDlg(void)
{
	m_pSPCardList = 0;
}

// 0x800e10
FrSPCardBuffDlg::~FrSPCardBuffDlg(void)
{
}

// 0x800e30
bool FrSPCardBuffDlg::OnInit(void)
{
	FrForm::OnInit();
	return true;
}

// 0x800e40
bool FrSPCardBuffDlg::Close(eFormRet ret, bool bDestroy)
{
	return FrForm::Close(ret, bDestroy);
}

// 0x801410
IObject* FrSpCardUseDlgMakeInstance(void)
{
	return new FrSpCardUseDlg;
}

struct __sFrSpCardUseDlg {
	// 0x801480
	__sFrSpCardUseDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrSpCardUseDlgMakeInstance, "FrSpCardUseDlg");
	}
};
static __sFrSpCardUseDlg s_registerFrSpCardUseDlg;

// 0x8014d0
void FrSpCardUseDlg::OnItemInit(intptr_t param)
{
	m_pItem = DYNAMIC_CAST(FrArea, param);
}

// 0x8015d0
IObject* FrCardUseDlgMakeInstance(void)
{
	return new FrCardUseDlg;
}

struct __sFrCardUseDlg {
	// 0x801640
	__sFrCardUseDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrCardUseDlgMakeInstance, "FrCardUseDlg");
	}
};
static __sFrCardUseDlg s_registerFrCardUseDlg;

// 0x801690
void FrCardUseDlg::OnItemInit(intptr_t param)
{
	m_pItem = DYNAMIC_CAST(FrArea, param);
}

// 0x801700
void FrCardUseDlg::OnEditInit(intptr_t param)
{
	m_pEdit = DYNAMIC_CAST(FrEdit, param);
}

// 0x801770
IObject* FrOpenCardPackDlgMakeInstance(void)
{
	return new FrOpenCardPackDlg;
}

struct __sFrOpenCardPackDlg {
	// 0x8017e0
	__sFrOpenCardPackDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrOpenCardPackDlgMakeInstance, "FrOpenCardPackDlg");
	}
};
static __sFrOpenCardPackDlg s_registerFrOpenCardPackDlg;

// 0x801830
void FrOpenCardPackDlg::OnLevelImgInit(intptr_t param)
{
	m_pLevelImg = DYNAMIC_CAST(FrArea, param);
}

// 0x8018a0
void FrOpenCardPackDlg::OnItemInit(intptr_t param)
{
	m_pItem = DYNAMIC_CAST(FrArea, param);
}

// 0x801910
IObject* FrOpenCardPackResultDlgMakeInstance(void)
{
	return new FrOpenCardPackResultDlg;
}

struct __sFrOpenCardPackResultDlg {
	// 0x801980
	__sFrOpenCardPackResultDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrOpenCardPackResultDlgMakeInstance, "FrOpenCardPackResultDlg");
	}
};
static __sFrOpenCardPackResultDlg s_registerFrOpenCardPackResultDlg;

// 0x8019d0
void FrOpenCardPackResultDlg::OnItemInit(intptr_t param)
{
	m_pItem = DYNAMIC_CAST(FrArea, param);
}

// 0x802890 (no reference found)
void UnreferencedEmpty_802890(void)
{
}

struct __sFrSPCardBuffDlg {
	// 0x802b70
	__sFrSPCardBuffDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrSPCardBuffDlgMakeInstance, "FrSPCardBuffDlg");
	}
};
static __sFrSPCardBuffDlg s_registerFrSPCardBuffDlg;

// 0x8052a0
bool FrCardUseDlg::OnInit(void)
{
	InitCardInfo();
	return FrForm::OnInit();
}

struct __sFrCardAttachDlg {
	// 0x805960
	__sFrCardAttachDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrCardAttachDlgMakeInstance, "FrCardAttachDlg");
	}
};
static __sFrCardAttachDlg s_registerFrCardAttachDlg;

// 0x8069e0
void FrSpCardUseDlg::SetSpCardInfo(unsigned long& spCardTid)
{
	m_spCardTid = spCardTid;
	m_overlappedCard = GetOverlappedCard();
}

struct __sFrItemAttachCardDlg {
	// 0x808720
	__sFrItemAttachCardDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrItemAttachCardDlgMakeInstance, "FrItemAttachCardDlg");
	}
};
static __sFrItemAttachCardDlg s_registerFrItemAttachCardDlg;

// Not the original constructors (not written yet): defined so that the
// vtables, GetRTTI and the ??_E thunks are emitted.
FrCardAttachDlg::FrCardAttachDlg(void)
{
}

FrItemAttachCardDlg::FrItemAttachCardDlg(void)
{
}

// 0xcda080-0xcdaaa0 (dynamic initializers)
const WRTTI FrSpCardUseDlg::m_RTTI("FrSpCardUseDlg", &FrForm::m_RTTI);
const WRTTI FrCardUseDlg::m_RTTI("FrCardUseDlg", &FrForm::m_RTTI);
const WRTTI FrOpenCardPackDlg::m_RTTI("FrOpenCardPackDlg", &FrForm::m_RTTI);
const WRTTI FrOpenCardPackResultDlg::m_RTTI("FrOpenCardPackResultDlg", &FrForm::m_RTTI);
const WRTTI FrCardAttachDlg::m_RTTI("FrCardAttachDlg", &FrForm::m_RTTI);
const WRTTI FrItemAttachCardDlg::m_RTTI("FrItemAttachCardDlg", &FrForm::m_RTTI);
const WRTTI FrSPCardBuffDlg::m_RTTI("FrSPCardBuffDlg", &FrForm::m_RTTI);
