// Original: d:\build\custom\temp\code\client\projectg\itemstorage.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_ITEMSTORAGE_H
#define PG_JP983_CLIENT_PROJECTG_ITEMSTORAGE_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "client/FreshNext/include/frform.h"

struct sFRESH_ENTRY;

IObject* FrItemStorageNoticeMakeInstance(void);     // 0x7f6ff0
IObject* FrItemStorageAccessPanelMakeInstance(void);   // 0x7f72a0
IObject* FrItemStoragePangBankMakeInstance(void);   // 0x7f7650
IObject* FrItemConfirmMakeInstance(void);           // 0x7f9300
IObject* FrItemCounterMakeInstance(void);           // 0x7fafe0

// A traded item (KR shared/globalnetworkdefine.h sTradeItem); no jp983 copy
// of that header exists yet. Only the members this unit touches, at their JP
// offsets. The constructor (0x5a7400) is out of line. Size 0xac: the JP
// sStoredItemInfo is 0xb0 (the memset of FrItemCounter's constructor).
struct sTradeItem {
	sTradeItem(void);              // 0x5a7400

	unsigned long index;           // 0x00
	unsigned long typeId;          // 0x04
	unsigned long guid;            // 0x08
	int count;                     // 0x0c
	PADDING(0x10, 0xac);
};

CHECK_SIZE(sTradeItem, 0xac);
BEGIN_LAYOUT_CHECK(sTradeItem)
	CHECK_FIELD(sTradeItem, typeId, 0x04);
	CHECK_FIELD(sTradeItem, guid, 0x08);
	CHECK_FIELD(sTradeItem, count, 0x0c);
END_LAYOUT_CHECK

// A stored item (KR shared/globalnetworkdefine.h sStoredItemInfo, KR size
// 0xae); JP size 0xb0. The accessors are in-class inlines in KR; their JP
// copies sit in this unit's object (0x7f8060-0x7f8090), so they are defined
// out of line in ItemStorage.cpp.
struct sStoredItemInfo {
	void SetTypeID(unsigned long typeId);   // 0x7f8060
	void SetGuid(unsigned long guid);       // 0x7f8070
	unsigned long GetCount(void) const;     // 0x7f8080
	void SetCount(unsigned long count);     // 0x7f8090

	unsigned long slot;   // 0x00
	sTradeItem item;      // 0x04
};

CHECK_SIZE(sStoredItemInfo, 0xb0);
BEGIN_LAYOUT_CHECK(sStoredItemInfo)
	CHECK_FIELD(sStoredItemInfo, item, 0x04);
END_LAYOUT_CHECK

// The item storage notice dialog (RTTI FrItemStorageNotice; vtables
// 0xd13e24 (38 slots), 0xd13e18 (FrCmdTarget), 0xd13e10 (FrModalRenderer)).
// No members of its own. GetRTTI's copy is 0x604500 (another unit).
class FrItemStorageNotice : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0

	virtual void OnProc(const float dt);   // 9 (0x7f6fd0)
	virtual void OnDraw(void);             // 8 (0x7f6fe0)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                               // 0xe1c968
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;     // FrCmdTarget 1 (0x7f7080)

	void OnLBDownConfirm(void);   // 0x7f7090
};

CHECK_SIZE(FrItemStorageNotice, 0x110);

// The storage access (password) panel (RTTI FrItemStorageAccessPanel;
// vtables 0xd2ae94, 0xd2ae84 (FrCmdTarget), 0xd2ae7c (FrModalRenderer)).
// Size 0x1c0 (the `new` of FrItemStorageAccessPanelMakeInstance 0x7f72a0; KR
// 0x1b8). The destructor 0x7f7240 is out of line.
class FrItemStorageAccessPanel : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	enum eFormType {
	};

	FrItemStorageAccessPanel(void);            // 0x7f70a0
	virtual ~FrItemStorageAccessPanel(void);   // 1 (0x7f7240)

	static const WRTTI m_RTTI;                 // 0xe7bad4
	virtual const WRTTI* GetRTTI(void) const;  // 0 (0x7f7230)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                               // 0xe1c970
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;     // FrCmdTarget 1 (0x7f7330)

	bool DiffPassword(void);   // 0x7f7260

private:
	eFormType m_formType;              // 0x110
	int m_inputStep;                   // 0x114
	char m_password[0x20];             // 0x118
	char m_newPassword[0x20];          // 0x138
	char m_confirmPassword[0x20];      // 0x158, compared with m_newPassword
	PADDING(0x178, 0x1c0);             // KR: number slots, print-out area, buttons (not verified in JP)
};

CHECK_SIZE(FrItemStorageAccessPanel, 0x1c0);
BEGIN_LAYOUT_CHECK(FrItemStorageAccessPanel)
	CHECK_FIELD(FrItemStorageAccessPanel, m_formType, 0x110);
	CHECK_FIELD(FrItemStorageAccessPanel, m_newPassword, 0x138);
	CHECK_FIELD(FrItemStorageAccessPanel, m_confirmPassword, 0x158);
END_LAYOUT_CHECK

class FrArea;
class FrEdit;
class FrButton;

// Count input of a stored item (RTTI FrItemCounter; vtables 0xd2af64,
// 0xd2af54 (FrCmdTarget), 0xd2af4c (FrModalRenderer)). Size 0x1e0 (the `new` of
// FrItemCounterMakeInstance 0x7fafe0; KR 0x1d8). The destructor
// 0x7f7570 is out of line: defining it here lets cl inline it into ??_G.
class FrItemCounter : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	FrItemCounter(void);            // 0x7faf80
	virtual ~FrItemCounter(void);   // 1 (0x7f7570)

	static const WRTTI m_RTTI;                                      // 0xe7badc
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x7f7590)

	void SetType(unsigned long type);    // 0x7f6dd0
	unsigned long GetType(void) const;   // 0x7f6e40

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                               // 0xe1c978
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;     // FrCmdTarget 1 (0x7f75a0)

	void OnLBDownCancel(void);    // 0x7f75b0

private:
	FrArea* m_pDrawArea;              // 0x110
	FrEdit* m_pInput;                 // 0x114
	FrButton* m_pConfirmBn;           // 0x118
	FrButton* m_pCancelBn;            // 0x11c
	unsigned long m_type;             // 0x120
	sStoredItemInfo m_storedItemInfo; // 0x124
	PADDING(0x1d4, 0x1e0);
};

CHECK_SIZE(FrItemCounter, 0x1e0);

BEGIN_LAYOUT_CHECK(FrItemCounter)
	CHECK_FIELD(FrItemCounter, m_pDrawArea, 0x110);
	CHECK_FIELD(FrItemCounter, m_pCancelBn, 0x11c);
	CHECK_FIELD(FrItemCounter, m_type, 0x120);
	CHECK_FIELD(FrItemCounter, m_storedItemInfo, 0x124);
END_LAYOUT_CHECK

// Confirmation of a stored item move (RTTI FrItemConfirm; vtables 0xd2b0dc,
// 0xd2b0d0 (FrCmdTarget), 0xd2b0c8 (FrModalRenderer)). Size 0x1d0 (the `new` of
// FrItemConfirmMakeInstance 0x7f9300). The destructor
// 0x7f7700 is out of line.
class FrItemConfirm : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	FrItemConfirm(void);            // 0x7f9270
	virtual ~FrItemConfirm(void);   // 1 (0x7f7700)

	static const WRTTI m_RTTI;                                      // 0xe7baec
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x7f7720)

	const sStoredItemInfo& GetStoredItemInfo(void) const;   // 0x7f6e50
	void SetType(unsigned long type);                       // 0x7f6e60
	unsigned long GetType(void) const;                      // 0x7f6ed0

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                               // 0xe1c988
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;     // FrCmdTarget 1 (0x7f7730)

	void OnLBDownCancel(void);    // 0x7f7740

private:
	FrArea* m_pDrawArea;              // 0x110
	FrButton* m_pConfirmBn;           // 0x114
	FrButton* m_pCancelBn;            // 0x118
	unsigned long m_type;             // 0x11c
	sStoredItemInfo m_storedItemInfo; // 0x120
};

CHECK_SIZE(FrItemConfirm, 0x1d0);

BEGIN_LAYOUT_CHECK(FrItemConfirm)
	CHECK_FIELD(FrItemConfirm, m_pDrawArea, 0x110);
	CHECK_FIELD(FrItemConfirm, m_type, 0x11c);
	CHECK_FIELD(FrItemConfirm, m_storedItemInfo, 0x120);
END_LAYOUT_CHECK

// Pang deposit and withdrawal (RTTI FrItemStoragePangBank; vtables
// 0xd2b014, 0xd2b008 (FrCmdTarget), 0xd2b000 (FrModalRenderer)). Size 0x140
// (the `new` of FrItemStoragePangBankMakeInstance 0x7f7650; KR 0x138). The destructor 0x7f7630 is out of line.
class FrItemStoragePangBank : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	// What the pang bank form does (KR names, inferred from the buttons).
	enum eType {
		TYPE_DEPOSIT = 0,
		TYPE_WITHDRAW = 1
	};

	FrItemStoragePangBank(void);            // 0x7f75c0
	virtual ~FrItemStoragePangBank(void);   // 1 (0x7f7630)

	void SetStoredPang(__int64 pang);   // 0x7f6ee0
	__int64 GetStoredPang(void) const;   // 0x7f6f00
	void SetMyPang(__int64 pang);        // 0x7f6f10
	__int64 GetMyPang(void) const;       // 0x7f6f30
	void SetType(unsigned long type);    // 0x7f6f40
	unsigned long GetType(void) const;   // 0x7f6fb0

	static const WRTTI m_RTTI;                                      // 0xe7bae4
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x7f7620)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                               // 0xe1c980
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;     // FrCmdTarget 1 (0x7f76e0)

	void OnLBDownCancel(void);    // 0x7f76f0

private:
	FrArea* m_pDrawArea;     // 0x110
	FrEdit* m_pInput;        // 0x114
	FrButton* m_pConfirmBn;  // 0x118
	FrButton* m_pCancelBn;   // 0x11c
	unsigned long m_type;    // 0x120
	UNKNOWN(0x124, 0x128);
	__int64 m_storedPang;    // 0x128
	__int64 m_myPang;        // 0x130
	PADDING(0x138, 0x140);
};

CHECK_SIZE(FrItemStoragePangBank, 0x140);
BEGIN_LAYOUT_CHECK(FrItemStoragePangBank)
	CHECK_FIELD(FrItemStoragePangBank, m_pDrawArea, 0x110);
	CHECK_FIELD(FrItemStoragePangBank, m_type, 0x120);
	CHECK_FIELD(FrItemStoragePangBank, m_storedPang, 0x128);
	CHECK_FIELD(FrItemStoragePangBank, m_myPang, 0x130);
END_LAYOUT_CHECK

// The item storage (RTTI CItemStorage : WSingleton<CItemStorage> (BaseObject),
// FrCmdTarget at 0x28; vtables 0xd2b478, 0xd2b46c). Not modelled yet: only
// the member this unit's bodies read, the bases are padding.
class CItemStorage {
	LAYOUT_CHECK_FRIEND;
public:
	__int64 GetStoredPang(void) const;   // 0x7f6fc0

private:
	PADDING(0x00, 0x58);
	__int64 m_storedPang;   // 0x58
};

BEGIN_LAYOUT_CHECK(CItemStorage)
	CHECK_FIELD(CItemStorage, m_storedPang, 0x58);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_ITEMSTORAGE_H
