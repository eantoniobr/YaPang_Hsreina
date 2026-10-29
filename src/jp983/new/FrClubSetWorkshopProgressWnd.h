// Original: unknown, JP-only RTTI class FrClubSetWorkshopProgressWnd (JP 983 exe)
#ifndef PG_JP983_NEW_FRCLUBSETWORKSHOPPROGRESSWND_H
#define PG_JP983_NEW_FRCLUBSETWORKSHOPPROGRESSWND_H

#include <vector>

#include "defines.h"
#include "padding.h"

// The club set workshop's main dialog, a JP-only RTTI class. Only the two
// methods the child windows call are declared; its singleton pointer is
// 0xe74c68 (CTaskManager::ChangeTask closes it through FrForm::Close).
class FrClubSetWorkshopMainDlg {
public:
	void DisableTabButtons(void);   // 0x4cd7f0: btn_tab_levelup, btn_tab_rankup, ... disabled
	void EnableTabButtons(void);    // 0x4cd8c0: the same buttons enabled
};

extern FrClubSetWorkshopMainDlg* data_00e74c68;

// The JP-only RTTI base of the workshop's child windows (vtable 0xd039b0).
// Slots 4-7 are empty in the base; the derived windows override some.
class ClubSetWorkshopChildWndBase {
public:
	virtual ~ClubSetWorkshopChildWndBase(void);    // slot 0, 0x4cbb00
	virtual void SetChildrenEnable(bool bEnable);   // slot 1, 0x4ca660
	virtual void OnBeginWork(void);                 // slot 2, 0x4ca6c0
	virtual void OnEndWork(void);                   // slot 3, 0x4ca6d0
	virtual void OnChildEvent(int nEvent);          // slot 4, 0x49eb90
	virtual void OnChildUpdate(void);               // slot 5, 0x49eba0
	virtual void OnChildNotify(int nNotify);        // slot 6, 0x49ebb0
	virtual void OnChildRefresh(void);              // slot 7, 0x49ebc0

	int m_nState;                       // 0x04
	bool m_bEnable;                     // 0x08
	std::vector<ClubSetWorkshopChildWndBase*> m_children;   // 0x0c
	int m_nValue1c;                     // 0x1c
	int m_nValue20;                     // 0x20
};
CHECK_FIELD(ClubSetWorkshopChildWndBase, m_bEnable, 0x08);
CHECK_FIELD(ClubSetWorkshopChildWndBase, m_children, 0x0c);
CHECK_FIELD(ClubSetWorkshopChildWndBase, m_nValue20, 0x20);
CHECK_SIZE(ClubSetWorkshopChildWndBase, 0x24);

// The JP-only RTTI primary base (vtable 0xd039d4, one slot: the destructor).
class ClubSetWorkshopHelper {
public:
	virtual ~ClubSetWorkshopHelper(void);

	PADDING(0x04, 0x50);
};

// The workshop's upgrade progress window: ClubSetWorkshopHelper at 0,
// ClubSetWorkshopChildWndBase at 0x50 (vtables 0xd00f00 and 0xd00edc).
class FrClubSetWorkshopProgressWnd : public ClubSetWorkshopHelper, public ClubSetWorkshopChildWndBase {
public:
	virtual ~FrClubSetWorkshopProgressWnd(void);

	PADDING(0x74, 0x78);
	std::vector<void*> m_list78;        // 0x78, element type not known yet
	PADDING(0x88, 0x90);
	std::vector<void*> m_list90;        // 0x90, element type not known yet
	PADDING(0xa0, 0xc4);
	ClubSetWorkshopHelper* m_pHelper;   // 0xc4, owned; its real type is not known (any class with the destructor in slot 0)
};
CHECK_FIELD(FrClubSetWorkshopProgressWnd, m_list78, 0x78);
CHECK_FIELD(FrClubSetWorkshopProgressWnd, m_list90, 0x90);
CHECK_FIELD(FrClubSetWorkshopProgressWnd, m_pHelper, 0xc4);

// Cleared by FrClubSetWorkshopProgressWnd's destructor; also written by
// 0x49f720, 0x4ccff0 and 0x4ce000.
extern FrClubSetWorkshopProgressWnd* data_00e74218;

#endif // PG_JP983_NEW_FRCLUBSETWORKSHOPPROGRESSWND_H
