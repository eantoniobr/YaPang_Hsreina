// Original: d:\build\custom\temp\code\client\projectg\carddlg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_CARDDLG_H
#define PG_JP983_CLIENT_PROJECTG_CARDDLG_H

#include <stdint.h>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "client/FreshNext/include/frform.h"

class FrArea;
class FrEdit;
class FrListBox;
struct sFRESH_ENTRY;

IObject* FrSpCardUseDlgMakeInstance(void);            // 0x801410
IObject* FrCardUseDlgMakeInstance(void);              // 0x8015d0
IObject* FrOpenCardPackDlgMakeInstance(void);         // 0x801770
IObject* FrOpenCardPackResultDlgMakeInstance(void);   // 0x801910
IObject* FrSPCardBuffDlgMakeInstance(void);           // 0x802b00 (no split row)
IObject* FrCardAttachDlgMakeInstance(void);           // 0x8058f0
IObject* FrItemAttachCardDlgMakeInstance(void);       // 0x8086b0

// Special-card use dialog (RTTI FrSpCardUseDlg : FrForm; vtables 0xd2bab4,
// 0xd2baa8 (FrCmdTarget), 0xd2baa0 (FrModalRenderer)). Size 0x120, the `new`
// of FrSpCardUseDlgMakeInstance (KR 0x128).
class FrSpCardUseDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7bb18
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x8008c0)

	FrSpCardUseDlg(void);                                     // 0x800890
	virtual ~FrSpCardUseDlg(void);                            // 1 (0x8008d0, ??_G 0x8014a0)

	unsigned long GetOverlappedCard(void);                    // 0x805860
	void SetSpCardInfo(unsigned long& spCardTid);             // 0x8069e0

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d4d0
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x800880)

	void OnItemInit(intptr_t param);                          // 0x8014d0

	unsigned long m_overlappedCard;   // 0x110
	unsigned long m_spCardTid;        // 0x114
	FrArea* m_pItem;                  // 0x118
	PADDING(0x11c, 0x120);
};

CHECK_SIZE(FrSpCardUseDlg, 0x120);
BEGIN_LAYOUT_CHECK(FrSpCardUseDlg)
	CHECK_FIELD(FrSpCardUseDlg, m_overlappedCard, 0x110);
	CHECK_FIELD(FrSpCardUseDlg, m_spCardTid, 0x114);
	CHECK_FIELD(FrSpCardUseDlg, m_pItem, 0x118);
END_LAYOUT_CHECK

// Card use dialog (RTTI FrCardUseDlg; vtables 0xd2bb64, 0xd2bb58, 0xd2bb50).
// Size 0x130 (KR 0x128).
class FrCardUseDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7bb24
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x800940)

	FrCardUseDlg(void);                                       // 0x800900
	virtual ~FrCardUseDlg(void);                              // 1 (0x800950, ??_G 0x801660)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d4d8
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x8008f0)

public:
	virtual bool OnInit(void);                                // 32 (0x8052a0), JP-only

protected:
	void InitCardInfo(void);                                  // 0x803b70, called by OnInit
	void OnItemInit(intptr_t param);                          // 0x801690
	void OnEditInit(intptr_t param);                          // 0x801700, JP-only (its control name is in the message map, not read)

	unsigned long m_cardId;       // 0x110
	unsigned long m_cardTypeId;   // 0x114
	unsigned long m_value118;     // 0x118
	unsigned long m_value11c;     // 0x11c
	FrArea* m_pItem;              // 0x120
	FrEdit* m_pEdit;              // 0x124, JP-only
	PADDING(0x128, 0x130);
};

CHECK_SIZE(FrCardUseDlg, 0x130);
BEGIN_LAYOUT_CHECK(FrCardUseDlg)
	CHECK_FIELD(FrCardUseDlg, m_cardId, 0x110);
	CHECK_FIELD(FrCardUseDlg, m_cardTypeId, 0x114);
	CHECK_FIELD(FrCardUseDlg, m_value118, 0x118);
	CHECK_FIELD(FrCardUseDlg, m_value11c, 0x11c);
	CHECK_FIELD(FrCardUseDlg, m_pItem, 0x120);
	CHECK_FIELD(FrCardUseDlg, m_pEdit, 0x124);
END_LAYOUT_CHECK

// Card pack opening dialog (RTTI FrOpenCardPackDlg; vtables 0xd2bc14,
// 0xd2bc08, 0xd2bc00). Size 0x120.
class FrOpenCardPackDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7bb2c
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x8009b0)

	FrOpenCardPackDlg(void);                                  // 0x800980
	virtual ~FrOpenCardPackDlg(void);                         // 1 (0x8009c0, ??_G 0x801800)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d4e0
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x800970)

	void OnLevelImgInit(intptr_t param);                      // 0x801830
	void OnItemInit(intptr_t param);                          // 0x8018a0

	unsigned long m_cardId;       // 0x110
	unsigned long m_cardTypeId;   // 0x114
	FrArea* m_pItem;              // 0x118
	FrArea* m_pLevelImg;          // 0x11c
};

CHECK_SIZE(FrOpenCardPackDlg, 0x120);
BEGIN_LAYOUT_CHECK(FrOpenCardPackDlg)
	CHECK_FIELD(FrOpenCardPackDlg, m_cardId, 0x110);
	CHECK_FIELD(FrOpenCardPackDlg, m_cardTypeId, 0x114);
	CHECK_FIELD(FrOpenCardPackDlg, m_pItem, 0x118);
	CHECK_FIELD(FrOpenCardPackDlg, m_pLevelImg, 0x11c);
END_LAYOUT_CHECK

// Result of a card pack opening (RTTI FrOpenCardPackResultDlg; vtables
// 0xd2bcc4, 0xd2bcb8, 0xd2bcb0). Size 0x130 (KR 0x128).
class FrOpenCardPackResultDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7bb34
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x800a30)

	FrOpenCardPackResultDlg(void);                            // 0x8009f0
	virtual ~FrOpenCardPackResultDlg(void);                   // 1 (0x800a40, ??_G 0x8019a0)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d4e8
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x8009e0)

	void OnItemInit(intptr_t param);                          // 0x8019d0

	unsigned long m_values[3];   // 0x110
	PADDING(0x11c, 0x120);
	FrArea* m_pItem;             // 0x120
	PADDING(0x124, 0x130);
};

CHECK_SIZE(FrOpenCardPackResultDlg, 0x130);
BEGIN_LAYOUT_CHECK(FrOpenCardPackResultDlg)
	CHECK_FIELD(FrOpenCardPackResultDlg, m_values, 0x110);
	CHECK_FIELD(FrOpenCardPackResultDlg, m_pItem, 0x120);
END_LAYOUT_CHECK

// Card attaching dialog (RTTI FrCardAttachDlg; vtables 0xd2c14c, 0xd2c13c,
// 0xd2c134). Holds a std::string at 0x144 (its destructor 0x805360 frees
// it); the constructor and destructor are not written yet.
class FrCardAttachDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7bb3c
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x805330)

	FrCardAttachDlg(void);
	virtual ~FrCardAttachDlg(void);                           // 1 (0x805360, ??_G 0x805980)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d4f0
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x800a60)

	PADDING(0x110, 0x144);
};

// Card attaching to an item (RTTI FrItemAttachCardDlg; vtables 0xd2c2d4,
// 0xd2c2c8, 0xd2c2c0). The constructor and destructor (0x806e80) are not
// written yet.
class FrItemAttachCardDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7bb48
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x806e50)

	FrItemAttachCardDlg(void);
	virtual ~FrItemAttachCardDlg(void);                       // 1 (0x806e80, ??_G 0x808740)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d4f8
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x800a90)
};

// Special-card buff list (RTTI FrSPCardBuffDlg; vtables 0xd2bd8c, 0xd2bd80,
// 0xd2bd78). Overrides OnProc (9, 0x808140), Close (26) and OnInit (32).
class FrSPCardBuffDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7bb50
	virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x800e00)

	FrSPCardBuffDlg(void);                                    // 0x800dd0
	virtual ~FrSPCardBuffDlg(void);                           // 1 (0x800e10, ??_G 0x802b90)

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1d500
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x800dc0)

public:
	virtual bool OnInit(void);                         // 32 (0x800e30)
	virtual bool Close(eFormRet ret, bool bDestroy);   // 26 (0x800e40)

protected:
	virtual void OnProc(const float fDelta);           // 9 (0x808140)

	FrListBox* m_pSPCardList;   // 0x110
};

BEGIN_LAYOUT_CHECK(FrSPCardBuffDlg)
	CHECK_FIELD(FrSPCardBuffDlg, m_pSPCardList, 0x110);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_CARDDLG_H
