// Original: client/ProjectG/GolfRule.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_GOLFRULE_H
#define PG_JP983_CLIENT_PROJECTG_GOLFRULE_H

#include "defines.h"
#include "padding.h"

class CGolfRuleHoleInOne;
class CGolfRuleBase;

// JP CGolfRule (RTTI CGolfRule : CTaskMain : IActor, IObject, FrCmdTarget;
// vtables 0xd18534 and 0xd18528). Only the members the bodies of the JP
// units use are declared so far; the bases and the layout are not modelled.
class CGolfRule {
public:
	// 0x66e850: called by OnReload (vtable slot 5, 0x678a30), which sets the
	// byte at 0x634 when it returns nonzero; this build always returns 0.
	int IsReloadFlagged(void);

protected:
	void ChangeGameMode(unsigned long mode); // 0x68c2f0

	friend class CGolfRuleHoleInOne;
	friend class CGolfRuleBase;
};

#endif // PG_JP983_CLIENT_PROJECTG_GOLFRULE_H
