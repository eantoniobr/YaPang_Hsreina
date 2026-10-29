// Original: unknown, JP-only RTTI class CTutorialWidget (JP 983 exe)
#include "CTutorialWidget.h"

// Constructor (VA unknown; not in this unit). Defining it here emits the
// vtables and with them the ??_G at 0x6b2d10 and its FrCmdTarget
// this-adjusting thunk at 0x6b2c50, as the original does.
CTutorialWidget::CTutorialWidget(void)
{
}

// 0x6b2c10
const WRTTI* CTutorialWidget::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x6b2c20
void CTutorialWidget::UnknownSlot4(void)
{
}
