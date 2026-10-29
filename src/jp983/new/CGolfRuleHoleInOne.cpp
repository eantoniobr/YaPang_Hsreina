// Original: unknown, JP-only RTTI class CGolfRuleHoleInOne (JP 983 exe)
#include "CGolfRuleHoleInOne.h"

// The camera work object (0xe74cc0), with its 0x6db6c0 member.
class CCameraWork {
public:
	void Play(int id); // 0x6db6c0
};
extern "C" CCameraWork* data_e74cc0;

class CClub {
public:
	void ResetSwing(void); // 0x6b0fb0
};

// Constructor (VA unknown; the store of the vtable 0xd09774 was not found).
// The real constructor and destructor (0x546430) are elsewhere, unplaced.
// Defining it here emits the vtable and with it the ??_G at 0x5468d0, which
// then calls the out-of-line ~CGolfRuleHoleInOne as the original does.
CGolfRuleHoleInOne::CGolfRuleHoleInOne(void)
{
}

// 0x544ce0
void CGolfRuleHoleInOne::SetGrade(void)
{
}

// 0x544cf0
void CGolfRuleHoleInOne::SetReady(void)
{
	m_pRule->ChangeGameMode(1);
}

// 0x544d00
void CGolfRuleHoleInOne::ShowScore(int value)
{
	DoScoreBoard();
}

// 0x545ce0
void CGolfRuleHoleInOne::StartHole(void)
{
	ResetComboGauge();
	data_e47dbc->m_10704 = false;
	data_e74cc0->Play(0xcc);
	GolfClub().ResetSwing();
	data_e47dbc->m_10588 = true;
}

// 0x6a5eb0
void CGolfRuleBase::OnNotify(int value)
{
}

// 0x6a68d0
int CGolfRuleBase::GetNumTimeout(void)
{
	return PLAYER(GOLFDOC()->m_myPlayerIndex)->m_numTimeout;
}
