// Original: unknown, JP-only RTTI class FrClubSetInfoWnd (JP 983 exe)
#ifndef PG_JP983_NEW_FRCLUBSETINFOWND_H
#define PG_JP983_NEW_FRCLUBSETINFOWND_H

#include "defines.h"
#include "padding.h"
#include "jp983/new/FrClubSetWorkshopProgressWnd.h"

// The club set workshop's club info window: ClubSetWorkshopHelper at 0,
// ClubSetWorkshopChildWndBase at 0x50 (vtables 0xd027c4 and 0xd027a0).
class FrClubSetInfoWnd : public ClubSetWorkshopHelper, public ClubSetWorkshopChildWndBase {
public:
	FrClubSetInfoWnd(void);
	virtual ~FrClubSetInfoWnd(void);                  // primary slot 0, 0x4be7e0 (??_G 0x4bf940)
	virtual bool IsReady(void);                       // primary slot 1, 0x4bd8e0
	virtual void OnUpdate(float dt);                  // primary slot 2, 0x4bd8f0
	virtual void SetChildrenEnable(bool bEnable);     // ClubSetWorkshopChildWndBase slot 1, 0x4bd9b0

	// 0x4ca4d0: sets the flag at +0x20 of entry nIndex of the 0x24-byte entry
	// vector at 0x10 (its first pointer at 0x14), when nIndex is in range.
	// It is ClubSetWorkshopHelper's (this at 0); declared here until that
	// class declares it.
	void SetEntryFlag(unsigned int nIndex, bool bFlag);

	PADDING(0x74, 0x78);
	int* m_pPending;                    // 0x78, blinking stops while *m_pPending != 0
	PADDING(0x7c, 0x764);
	unsigned int m_nBlinkEntry;         // 0x764, entry index passed to SetEntryFlag
	PADDING(0x768, 0x7f0);
	int m_nWorking;                     // 0x7f0, nonzero: no blinking
	float m_fBlinkTime;                 // 0x7f4
	bool m_bBlinkOn;                    // 0x7f8
};
CHECK_FIELD(FrClubSetInfoWnd, m_pPending, 0x78);
CHECK_FIELD(FrClubSetInfoWnd, m_nBlinkEntry, 0x764);
CHECK_FIELD(FrClubSetInfoWnd, m_nWorking, 0x7f0);
CHECK_FIELD(FrClubSetInfoWnd, m_fBlinkTime, 0x7f4);
CHECK_FIELD(FrClubSetInfoWnd, m_bBlinkOn, 0x7f8);

#endif // PG_JP983_NEW_FRCLUBSETINFOWND_H
