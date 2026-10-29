// Original: unknown, JP-only RTTI class CReactionObject (JP 983 exe)
#ifndef PG_JP983_NEW_CREACTIONOBJECT_H
#define PG_JP983_NEW_CREACTIONOBJECT_H

#include "defines.h"
#include "padding.h"

// JP-only class (RTTI name CReactionObject, no base), vtable at 0xd12e94,
// 4 slots; slot 3 is also the derived vtable's at 0xd12eb8. Its destructor
// (0x5f0230, not split) releases m_target through the object behind
// 0xf023f0. The layout is known only as far as the bodies read it.
class CReactionObject
{
public:
    CReactionObject();
    virtual ~CReactionObject();                       // 0 (??_G 0x5f0870; ~ 0x5f0230)
    virtual void Start();                             // 1 (0x5f0200, empty)
    virtual void Stop();                              // 2 (0x5f0210, empty)
    virtual void SetTarget(void* target);             // 3 (0x5f0260)

protected:
    void* m_target; // 0x4
    PADDING(0x08, 0x38);
    bool m_finished; // 0x38
    float m_scale; // 0x3c

    LAYOUT_CHECK_FRIEND;
};

BEGIN_LAYOUT_CHECK(CReactionObject)
    CHECK_FIELD(CReactionObject, m_target, 0x4);
    CHECK_FIELD(CReactionObject, m_finished, 0x38);
    CHECK_FIELD(CReactionObject, m_scale, 0x3c);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_CREACTIONOBJECT_H
