// Original: d:\build\custom\temp\code\client\projectg\post_senddlg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_POST_SENDDLG_H
#define PG_JP983_CLIENT_PROJECTG_POST_SENDDLG_H

#include <stdint.h>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "client/FreshNext/include/frform.h"

IObject* CPost_SendDlgMakeInstance(void);        // 0x80f3c0
IObject* CPost_MyItemListMakeInstance(void);     // 0x80d240
IObject* CPost_ItemCountDlgMakeInstance(void);   // 0x80b2c0

class FrButton;
class FrEdit;
struct sFRESH_ENTRY;

// Mail writing dialog (RTTI CPost_SendDlg : FrForm; vtables 0xd2caa4 (GetRTTI,
// the destructor, OnOK at 33 and OnCancel at 34 overridden), 0xd2ca98
// (FrCmdTarget: ??_E thunk, GetMessageMap) and 0xd2ca90 (FrModalRenderer)).
// The destructor 0x80ed10 is out of line (??_G 0x80f450). Size 0x1b0, the
// `new` of CPost_SendDlgMakeInstance 0x80f3c0 (KR 0x1a8).
class CPost_SendDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                      // 0xe7bb84
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x80ece0)

	CPost_SendDlg(void);
	virtual ~CPost_SendDlg(void);                                   // 1 (0x80ed10)

	bool OnSendQuestionResult(int ret, FrForm* pForm);              // 0x80b0d0

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                                   // 0xe1e020
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;         // FrCmdTarget 1 (0x80b0b0)

	virtual void OnOK(void);                                        // 33 (0x80f480)
	virtual void OnCancel(void);                                    // 34 (0x80b9f0)

private:
	PADDING(0x110, 0x1b0);   // KR members (0x1a8) not verified in JP
};

CHECK_SIZE(CPost_SendDlg, 0x1b0);

// Item list of the mail dialog (RTTI CPost_MyItemList : FrForm; vtables
// 0xd2c70c (GetRTTI, the destructor, OnInit at 32 and OnOK at 33
// overridden), 0xd2c6fc (FrCmdTarget) and 0xd2c6f4 (FrModalRenderer)). The
// destructor 0x80b110 is out of line (??_G 0x80ba50). Size 0x180, the `new`
// of CPost_MyItemListMakeInstance 0x80d240 (KR 0x178).
class CPost_MyItemList : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                      // 0xe7bb90
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x80b1e0)

	CPost_MyItemList(void);                                         // 0x80c740
	virtual ~CPost_MyItemList(void);                                // 1 (0x80b110)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                                   // 0xe1e028
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;         // FrCmdTarget 1 (0x80b100)

	virtual void OnOK(void);                                        // 33 (0x80b230)
	virtual bool OnInit(void);                                      // 32 (0x80ea10)

	void SetList(void);                                             // 0x80dbf0

private:
	PADDING(0x110, 0x180);   // KR members (0x178) not verified in JP
};

CHECK_SIZE(CPost_MyItemList, 0x180);

// Item count dialog of the mail dialog (RTTI CPost_ItemCountDlg : FrForm;
// vtables 0xd2c7bc (GetRTTI and the destructor overridden), 0xd2c7b0
// (FrCmdTarget) and 0xd2c7a8 (FrModalRenderer)). Size 0x130, the `new` of
// CPost_ItemCountDlgMakeInstance 0x80b2c0 (KR 0x128).
class CPost_ItemCountDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                      // 0xe7bb98
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x80b290)

	CPost_ItemCountDlg(void);                                       // 0x80b250
	virtual ~CPost_ItemCountDlg(void);                              // 1 (0x80b2a0, ??_G 0x80bd10)

	void SetSelectItem(unsigned long item, int count);              // 0x80b3b0
	unsigned long GetSelectItem(void);                              // 0x80b3d0
	int GetCount(void);                                             // 0x80bf40
	bool OnPostEditItemCountEnterKey(int key);                      // 0x80b3e0

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                                   // 0xe1e030
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;         // FrCmdTarget 1 (0x80b350)

private:
	FrButton* m_pMinusBtn;        // 0x110
	FrButton* m_pPluseBtn;        // 0x114
	FrEdit* m_pCountEdit;         // 0x118
	int m_count;                  // 0x11c, between 1 and m_selectCount
	int m_selectCount;            // 0x120, count of the selected item
	unsigned long m_selectItem;   // 0x124
	PADDING(0x128, 0x130);        // 0x128 set by 0x80b240 (not identified)
};

CHECK_SIZE(CPost_ItemCountDlg, 0x130);
BEGIN_LAYOUT_CHECK(CPost_ItemCountDlg)
	CHECK_FIELD(CPost_ItemCountDlg, m_pMinusBtn, 0x110);
	CHECK_FIELD(CPost_ItemCountDlg, m_pPluseBtn, 0x114);
	CHECK_FIELD(CPost_ItemCountDlg, m_pCountEdit, 0x118);
	CHECK_FIELD(CPost_ItemCountDlg, m_count, 0x11c);
	CHECK_FIELD(CPost_ItemCountDlg, m_selectCount, 0x120);
	CHECK_FIELD(CPost_ItemCountDlg, m_selectItem, 0x124);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_POST_SENDDLG_H
