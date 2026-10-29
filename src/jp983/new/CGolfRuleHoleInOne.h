// Original: unknown, JP-only RTTI class CGolfRuleHoleInOne (JP 983 exe)
#ifndef PG_JP983_NEW_CGOLFRULEHOLEINONE_H
#define PG_JP983_NEW_CGOLFRULEHOLEINONE_H

#include "defines.h"
#include "padding.h"

#include <vector>

#include "jp983/client/ProjectG/GolfRule.h"
#include "jp983/client/ProjectG/SharedDoc.h"

class CClub;
CClub& GolfClub(void); // 0x6afd60

// Stand-in for the JP CGolfRuleBase (RTTI base of the JP rule strategies,
// vtable 0xd1978c), until the jp983 tree has GolfRuleBase.h. Slots 0-6 keep
// the KR order; the JP class grew slots 7-15 and moved the destructor to the
// end (slot 16). Only the members this unit uses are named for what they do.
class CGolfRuleBase {
public:
	virtual void SetPlayer(void);                                         // 0
	virtual void SetGrade(void);                                          // 1
	virtual void SetReady(void);                                          // 2
	virtual void AddPlayer(unsigned char, char const*, unsigned long, unsigned long, unsigned long); // 3
	virtual void AddPlayerOffline(unsigned char, char const*, unsigned long, unsigned long);         // 4
	virtual int GetNumTimeout(void);                                      // 5 (0x6a68d0)
	virtual bool CheckGiveUp(void);                                       // 6
	virtual void Slot7(void);                                             // 7
	virtual void Slot8(void);                                             // 8
	virtual void Slot9(void);                                             // 9
	virtual void OnNotify(int value);                                     // 10 (0x6a5eb0, empty)
	virtual void Slot11(void);                                            // 11
	virtual void StartHole(void);                                         // 12
	virtual void Slot13(void);                                            // 13
	virtual void Slot14(void);                                            // 14
	virtual void ShowScore(int value);                                    // 15
	virtual ~CGolfRuleBase(void);                                         // 16 (0x6a5ea0)

	// 0x6a8130: the score board / end-of-hole step.
	void DoScoreBoard(void);

protected:
	CGolfRule* m_pRule; // 0x04, the owning rule task
	PADDING(0x08, 0x18);

	LAYOUT_CHECK_FRIEND;
};

BEGIN_LAYOUT_CHECK(CGolfRuleBase)
	CHECK_FIELD(CGolfRuleBase, m_pRule, 0x04);
END_LAYOUT_CHECK

// JP-only golf rule strategy (RTTI CGolfRuleHoleInOne : CGolfRuleBase),
// vtable 0xd09774, 17 slots: 0 0x5464c0, 1 0x544ce0, 2 0x544cf0,
// 3 0x6a7470, 4 0x6a6330, 5 0x6a68d0, 6 0x6a6900, 7 0x6a7a40, 8 0x545500,
// 9 0x5459a0, 10 0x6a5eb0, 11 0x6a7dc0, 12 0x545ce0, 13 0x545570,
// 14 0x6a8440, 15 0x544d00, 16 0x5468d0 (destructor 0x546430).
class CGolfRuleHoleInOne : public CGolfRuleBase {
public:
	CGolfRuleHoleInOne(void);
	virtual void SetGrade(void);
	virtual void SetReady(void);
	virtual void StartHole(void);
	virtual void ShowScore(int value);
	virtual ~CGolfRuleHoleInOne(void); // 16 (??_G 0x5468d0; ~ 0x546430, not split)

	// 0x545bb0: refills this client's combo gauge to the limit.
	void ResetComboGauge(void);

protected:
	std::vector<int> m_list; // 0x18, element type unknown (the destructor frees it)

	LAYOUT_CHECK_FRIEND;
};

BEGIN_LAYOUT_CHECK(CGolfRuleHoleInOne)
	CHECK_FIELD(CGolfRuleHoleInOne, m_list, 0x18);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_CGOLFRULEHOLEINONE_H
