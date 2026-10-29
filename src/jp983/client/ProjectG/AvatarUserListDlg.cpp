// Original: d:\build\custom\temp\code\client\projectg\avataruserlistdlg.cpp (JP 983 exe)
#include "AvatarUserListDlg.h"

// 0x7b9b80
const sFRESH_MSGMAP* FrAvatarUserListDlg::GetMessageMap(void) const
{
	return &FrAvatarUserListDlg::_MsgMap;
}

// 0x7b9b90
FrAvatarUserListDlg::FrAvatarUserListDlg(void)
{
	m_pUserList = 0;
	m_alpha = 0;
	m_selected = -1;
}

// 0x7b9be0
FrAvatarUserListDlg::~FrAvatarUserListDlg(void)
{
}

// 0x7b9c20
IObject* FrAvatarUserListDlgMakeInstance(void)
{
	return new FrAvatarUserListDlg;
}

struct __sFrAvatarUserListDlg {
	// 0x7b9c90
	__sFrAvatarUserListDlg(void)
	{
		ObjectFactory().AddObjectFunctor(FrAvatarUserListDlgMakeInstance, "FrAvatarUserListDlg");
	}
};
static __sFrAvatarUserListDlg s_registerFrAvatarUserListDlg;

// 0x7ba270 (no reference besides the message map)
void FrAvatarUserListDlg::OnUserListLBtnDown(void)
{
}

// 0xcd6cb0 (dynamic initializer)
const WRTTI FrAvatarUserListDlg::m_RTTI("FrAvatarUserListDlg", &FrForm::m_RTTI);
