// Original: unknown, JP-only RTTI class CSubGolfRuleBase (JP 983 exe)
#ifndef PG_JP983_NEW_CSUBGOLFRULEBASE_H
#define PG_JP983_NEW_CSUBGOLFRULEBASE_H

// JP-only RTTI class CSubGolfRuleBase, vtable at 0xd16980, no base class.
// Its four hooks are empty here; derived rules (vtables at 0xd169c8 and
// 0xd169e8 reuse them) override them. Slot names are descriptive: no
// symbol names them. Fields are unknown: no body reads one.
class CSubGolfRuleBase
{
public:
    CSubGolfRuleBase(void);
    virtual ~CSubGolfRuleBase(void);          // 0 (??_G 0x64f9e0, dtor 0x64f910)
    virtual void OnStart(void);               // 1 (0x64f920, empty)
    virtual void OnEvent(int value);          // 2 (0x64f930, empty)
    virtual void OnUpdate(void);              // 3 (0x64f940, empty)
    virtual void OnEnd(void);                 // 4 (0x64f950, empty)
};

#endif // PG_JP983_NEW_CSUBGOLFRULEBASE_H
