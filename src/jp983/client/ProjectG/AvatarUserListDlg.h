// Original: d:\build\custom\temp\code\client\projectg\avataruserlistdlg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_AVATARUSERLISTDLG_H
#define PG_JP983_CLIENT_PROJECTG_AVATARUSERLISTDLG_H

#include <stdint.h>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "client/FreshNext/include/frform.h"

class Bitmap;
class FrListBox;
struct sFRESH_ENTRY;

IObject* FrAvatarUserListDlgMakeInstance(void);              // 0x7b9c20

// User list of the avatar lobby (RTTI FrAvatarUserListDlg : FrForm; vtables
// 0xd26a94 (38 slots: GetRTTI, the destructor and OnProc at 9 overridden),
// 0xd26a88 (FrCmdTarget: ??_E thunk, GetMessageMap) and 0xd26a80
// (FrModalRenderer)). Size 0x150, the `new` of
// FrAvatarUserListDlgMakeInstance (KR 0x148); the members keep their KR
// offsets (OnUserListInit 0x7b9ce0, OnProc 0x7b9e00).
class FrAvatarUserListDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7b0c0
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x7b9bd0)

	FrAvatarUserListDlg(void);                                // 0x7b9b90
	virtual ~FrAvatarUserListDlg(void);                       // 1 (0x7b9be0, ??_G 0x7b9cb0)

	void UpdateUserList(void);

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1a050
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x7b9b80)

	void OnUserListInit(intptr_t param);                      // 0x7b9ce0
	void OnUserListLBtnDown(void);                            // 0x7ba270
	void OnUserListRBtnUp(void);

	virtual void OnProc(const float dt);                      // 9 (0x7b9e00)

	int m_selected;               // 0x110
	FrListBox* m_pUserList;       // 0x114
	float m_alpha;                // 0x118
	const Bitmap* m_pBitmaps[11]; // 0x11c, set by OnUserListInit
	PADDING(0x148, 0x150);
};

CHECK_SIZE(FrAvatarUserListDlg, 0x150);
BEGIN_LAYOUT_CHECK(FrAvatarUserListDlg)
	CHECK_FIELD(FrAvatarUserListDlg, m_selected, 0x110);
	CHECK_FIELD(FrAvatarUserListDlg, m_pUserList, 0x114);
	CHECK_FIELD(FrAvatarUserListDlg, m_alpha, 0x118);
	CHECK_FIELD(FrAvatarUserListDlg, m_pBitmaps, 0x11c);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_AVATARUSERLISTDLG_H
