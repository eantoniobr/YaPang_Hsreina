// Original: unknown, JP-only RTTI class CGrandPrixTimeBase (JP 983 exe)
#ifndef PG_JP983_NEW_CGRANDPRIXTIMEBASE_H
#define PG_JP983_NEW_CGRANDPRIXTIMEBASE_H

// JP-only abstract class (RTTI name CGrandPrixTimeBase, no bases), vtable at
// 0xd09f44: slot 0 is __purecall, slot 1 an empty virtual. The same empty
// stub also fills slots of the vtables at 0xd0a170 and 0xd0a17c.
class CGrandPrixTimeBase
{
public:
    virtual void Update() = 0;                        // 0 (__purecall)
    virtual void OnTimeChanged();                     // 1 (0x55aa10, empty)
};

#endif // PG_JP983_NEW_CGRANDPRIXTIMEBASE_H
