// Original: unknown, JP-only RTTI class CShopWidget (JP 983 exe)
#include "CShopWidget.h"

// Constructor (VA unknown; not in this unit). Defining it here emits the
// vtables and with them the ??_G at 0x5e0e50 and its FrCmdTarget
// this-adjusting thunk at 0x5e0d60, as the original does.
CShopWidget::CShopWidget(void)
{
}

// 0x5e0cc0
const WRTTI* CShopWidget::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x5e0cd0
void CShopWidget::UnknownSlot4(void)
{
}
