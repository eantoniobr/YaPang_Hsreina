// Original: unknown, JP-only RTTI class CSetEffectObject (JP 983 exe)
#ifndef PG_JP983_NEW_CSETEFFECTOBJECT_H
#define PG_JP983_NEW_CSETEFFECTOBJECT_H

#include "defines.h"
#include "padding.h"

#include "CControlledObject.h"

// The record CSetEffectObject::Load reads.
struct SetEffectTable
{
    int effectId;                                     // 0x00
    PADDING(0x04, 0x1c);
    float values[1];                                  // 0x1c
};

struct SetEffectSource
{
    unsigned char kind;                               // 0x00
    PADDING(0x01, 0x04);
    int index;                                        // 0x04
    SetEffectTable* table;                            // 0x08
};

// JP-only class (RTTI name CSetEffectObject : CControlledObject), vtable at
// 0xd15ec0. Slots 2-4, 6-8, 10 and 11 keep CControlledObject's bodies; the
// layout is known only as far as the bodies read it.
class CSetEffectObject : public CControlledObject
{
public:
    CSetEffectObject();
    virtual ~CSetEffectObject();                      // 0 (??_G 0x62b1f0; ~ 0x62aeb0)
    virtual void Load(const void* source);            // 1 (0x62afc0), a SetEffectSource
    virtual void OnReset();                           // 5 (0x627a20, empty)
    virtual void OnLeave(int arg);                    // 9 (0x62b010)

    bool IsEffectEnabled();                           // 0x4b0e40 (returns a global flag)
    void RefreshEffects();                            // 0x62a9a0
    void ApplyEffect(int effectId, unsigned int value); // 0x62aa80

private:
    PADDING(0x04, 0x88);
    unsigned char m_kind;                             // 0x88

    LAYOUT_CHECK_FRIEND;
};

BEGIN_LAYOUT_CHECK(CSetEffectObject)
    CHECK_FIELD(CSetEffectObject, m_kind, 0x88);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_CSETEFFECTOBJECT_H
