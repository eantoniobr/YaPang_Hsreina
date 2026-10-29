// Original: unknown, JP-only RTTI class CMyRoomWidget (JP 983 exe)
#include "CMyRoomWidget.h"

// Constructor (VA unknown). Defining it here emits the vtables and with them
// the deleting destructor 0x5a7d10 and its FrCmdTarget thunk 0x5a73c0; the
// real constructor and destructor are elsewhere.
CMyRoomWidget::CMyRoomWidget(void)
{
}

// 0x5a7030
const WRTTI* CMyRoomWidget::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x64f1c0
void CMyRoomWidget::UnknownSlot7(int arg)
{
}

// 0x64f1d0
void CMyRoomWidget::UnknownSlot8(void)
{
}
