// Original: unknown, JP-only RTTI class CSetEffectObject (JP 983 exe)
#include "CSetEffectObject.h"

// Constructor (VA unknown). Defining it here emits the vtable and with it
// the ??_G at 0x62b1f0, which calls the out-of-line ~CSetEffectObject
// (0x62aeb0) as the original does.
CSetEffectObject::CSetEffectObject()
{
}

// 0x627a20
void CSetEffectObject::OnReset()
{
}

// 0x62afc0
void CSetEffectObject::Load(const void* source)
{
    const SetEffectSource* effect = static_cast<const SetEffectSource*>(source);
    m_kind = effect->kind;
    ApplyEffect(effect->table->effectId, (unsigned int)effect->table->values[effect->index]);
}

// 0x62b010
void CSetEffectObject::OnLeave(int arg)
{
    if (IsEffectEnabled()) {
        RefreshEffects();
    }
}
