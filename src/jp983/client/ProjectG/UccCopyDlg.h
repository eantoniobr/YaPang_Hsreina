// Original: d:\build\custom\temp\code\client\projectg\ucccopydlg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_UCCCOPYDLG_H
#define PG_JP983_CLIENT_PROJECTG_UCCCOPYDLG_H

#include <windows.h>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/Wangreal/include/bitmap.h"
#include "jp983/client/Wangreal/include/wtypes.h"
#include "client/FreshNext/include/frcmdtarget.h"
#include "client/FreshNext/include/fresh.h"
#include "client/FreshNext/include/frarea.h"
#include "client/FreshNext/include/frbutton.h"
#include "client/FreshNext/include/frgraphicinterface.h"
#include "client/FreshNext/include/frlistbox.h"
#include "client/FreshNext/include/frform.h"

class FrUccCopyConfirmDlg;

FrGraphicInterface* GetGDI(void);   // commonutil, 0x7e9040

// The JP text of a KR text key (Jp_LookupText, docs/JP_REFRESH_UI.md).
const char* Jp_LookupText(const char* text);   // 0xb4eb80

// An owned item (KR shared item info); only the members this unit reads, at
// their JP offsets.
struct sItemInfo {
	unsigned long m_serial;     // 0x00
	unsigned long m_typeId;     // 0x04
	PADDING(0x08, 0x52);
	char m_uccKey[1];           // 0x52, length not verified in JP
};

BEGIN_LAYOUT_CHECK(sItemInfo)
	CHECK_FIELD(sItemInfo, m_typeId, 0x04);
	CHECK_FIELD(sItemInfo, m_uccKey, 0x52);
END_LAYOUT_CHECK

// A UCC design (KR UccManager.h sUccClothes); only the member this unit reads.
struct sUccClothes {
	PADDING(0x00, 0x14);
	char m_uccName[1];          // 0x14, length not verified in JP
};

BEGIN_LAYOUT_CHECK(sUccClothes)
	CHECK_FIELD(sUccClothes, m_uccName, 0x14);
END_LAYOUT_CHECK

// The UCC design manager (KR UccManager.h); only what this unit calls.
class CUccManager {
public:
	sUccClothes* FindClothes(unsigned long typeId, const char* uccKey);   // 0x7ed3c0
};

CUccManager* UccManager(void);   // 0x7ef6b0

// UccLibrary (KR uccLibrary.h); no jp983 header declares it yet (0x7e9620).
const Bitmap* GetUccItemIcon(sItemInfo* pItem);
const Bitmap* GetUccItemIcon(unsigned long serial);   // 0x7ea620
const char* GetUccItemName(unsigned long serial);     // 0x7ea690

// The three UCC copy dialogs are FrForms (FrForm : FrWnd : IObject,
// FrCmdTarget; FrModalRenderer at 8), 38-slot primary vtables. FrForm and
// FrWnd are not modelled in the jp983 tree: IObject (at 0) is the only base
// kept, the rest of their members are padding, and
// the FrForm / FrWnd members these bodies call (OnFreshOkay 0xbe5e10,
// OnFreshCancel 0xbe5e00, SetFadeout 0xbe7b70) are declared on each class.
// Only what this unit's bodies need is declared.

// UCC copy dialog (primary vtable 0xd29524, FrCmdTarget vtable 0xd29514,
// FrModalRenderer vtable 0xd2950c). Size 0x140 (the `new` of
// FrUccCopyDlgMakeInstance 0x7e1730; KR 0x138).
class FrUccCopyDlg : public IObject {
	LAYOUT_CHECK_FRIEND;
	friend IObject* FrUccCopyDlgMakeInstance(void);
public:
	virtual const WRTTI* GetRTTI(void) const;   // slot 0

	static const WRTTI m_RTTI;   // 0xe7b9d0

	FrUccCopyDlg(void);          // 0x7e0ed0

	void Init(void);

protected:
	void OnItemListBtnDown(void);
	void OnCancelBtnUp(void);
	void OnItemListOwnerDraw(int param);
	bool OnUccCopyConfirmDlgResult(int ret, FrForm* pForm);

	void OnFreshOkay(void);      // FrForm, 0xbe5e10
	void OnFreshCancel(void);    // FrForm, 0xbe5e00

private:
	PADDING(0x004, 0x110);
	const Bitmap* m_pItemBaseNormal;      // 0x110
	const Bitmap* m_pItemBaseOver;        // 0x114
	const Bitmap* m_pItemBaseDown;        // 0x118
	sItemInfo* m_pItem;                   // 0x11c
	FrArea* m_pCharIcon;                  // 0x120
	FrListBox* m_pItemList;               // 0x124
	FrButton* m_pOkBtn;                   // 0x128
	FrArea* m_pCancelBtn;                 // 0x12c
	FrUccCopyConfirmDlg* m_pConfirmDlg;   // 0x130
	PADDING(0x134, 0x140);
};

CHECK_SIZE(FrUccCopyDlg, 0x140);
BEGIN_LAYOUT_CHECK(FrUccCopyDlg)
	CHECK_FIELD(FrUccCopyDlg, m_pItemBaseNormal, 0x110);
	CHECK_FIELD(FrUccCopyDlg, m_pItemBaseOver, 0x114);
	CHECK_FIELD(FrUccCopyDlg, m_pItemBaseDown, 0x118);
	CHECK_FIELD(FrUccCopyDlg, m_pItem, 0x11c);
	CHECK_FIELD(FrUccCopyDlg, m_pCharIcon, 0x120);
	CHECK_FIELD(FrUccCopyDlg, m_pItemList, 0x124);
	CHECK_FIELD(FrUccCopyDlg, m_pOkBtn, 0x128);
	CHECK_FIELD(FrUccCopyDlg, m_pCancelBtn, 0x12c);
	CHECK_FIELD(FrUccCopyDlg, m_pConfirmDlg, 0x130);
END_LAYOUT_CHECK

IObject* FrUccCopyConfirmDlgMakeInstance(void);   // 0x7e1250

// Confirmation step of the UCC copy (primary vtable 0xd295d4, FrCmdTarget
// vtable 0xd295c8, FrModalRenderer vtable 0xd295c0). Size 0x130 (the `new`
// of FrUccCopyConfirmDlgMakeInstance; KR 0x128).
class FrUccCopyConfirmDlg : public IObject {
	LAYOUT_CHECK_FRIEND;
	friend IObject* FrUccCopyConfirmDlgMakeInstance(void);
public:
	FrUccCopyConfirmDlg(void);   // 0x7e0d00

	virtual const WRTTI* GetRTTI(void) const;   // slot 0

	void Init(sItemInfo* pSrcItem, sItemInfo* pDestItem);

	static const WRTTI m_RTTI;   // 0xe7b9dc

protected:
	static sFRESH_MSGMAP _MsgMap;   // 0xe1b2e8
	const sFRESH_MSGMAP* GetMessageMap(void) const;

	void OnCancelBtnUp(void);
	void OnEtcOwnerDraw(int param);

	void OnFreshCancel(void);              // FrForm, 0xbe5e00
	void SetFadeout(bool bFadeout);        // FrWnd, 0xbe7b70
	const WRect& GetRect(void) { return m_rect; }   // FrWnd (KR frwnd.h)

private:
	PADDING(0x004, 0x034);
	WRect m_rect;               // 0x34 FrWnd's rectangle (KR frwnd.h)
	PADDING(0x044, 0x110);
	sItemInfo* m_pSrcItem;      // 0x110
	sItemInfo* m_pDestItem;     // 0x114
	FrArea* m_pIcon;            // 0x118
	PADDING(0x11c, 0x130);
};

CHECK_SIZE(FrUccCopyConfirmDlg, 0x130);
BEGIN_LAYOUT_CHECK(FrUccCopyConfirmDlg)
	CHECK_FIELD(FrUccCopyConfirmDlg, m_rect, 0x34);
	CHECK_FIELD(FrUccCopyConfirmDlg, m_pSrcItem, 0x110);
	CHECK_FIELD(FrUccCopyConfirmDlg, m_pDestItem, 0x114);
	CHECK_FIELD(FrUccCopyConfirmDlg, m_pIcon, 0x118);
END_LAYOUT_CHECK

IObject* FrUccCopyCompletedDlgMakeInstance(void);   // 0x7e1530

// Last step of the UCC copy (primary vtable 0xd29684, FrCmdTarget vtable
// 0xd29678, FrModalRenderer vtable 0xd29670). Size 0x130 (the `new` of
// FrUccCopyCompletedDlgMakeInstance; KR 0x128).
class FrUccCopyCompletedDlg : public IObject {
	LAYOUT_CHECK_FRIEND;
	friend IObject* FrUccCopyCompletedDlgMakeInstance(void);
public:
	FrUccCopyCompletedDlg(void);   // 0x7e0dd0

	virtual const WRTTI* GetRTTI(void) const;   // slot 0

	void Init(unsigned long typeId, const char* name);

	static const WRTTI m_RTTI;   // 0xe7b9e4

protected:
	static sFRESH_MSGMAP _MsgMap;   // 0xe1b2f0
	const sFRESH_MSGMAP* GetMessageMap(void) const;

	void OnOkBtnUp(void);

	void OnFreshOkay(void);      // FrForm, 0xbe5e10

private:
	PADDING(0x004, 0x110);
	unsigned long m_typeId;     // 0x110
	char m_name[10];            // 0x114
	PADDING(0x11e, 0x130);
};

CHECK_SIZE(FrUccCopyCompletedDlg, 0x130);
BEGIN_LAYOUT_CHECK(FrUccCopyCompletedDlg)
	CHECK_FIELD(FrUccCopyCompletedDlg, m_typeId, 0x110);
	CHECK_FIELD(FrUccCopyCompletedDlg, m_name, 0x114);
END_LAYOUT_CHECK

IObject* FrUccCopyDlgMakeInstance(void);   // 0x7e1730

#endif // PG_JP983_CLIENT_PROJECTG_UCCCOPYDLG_H
