// Original: unknown, JP-only RTTI class LobbyItems (JP 983 exe)
#include "LobbyItems.h"

// Constructor (VA not split). Defining it here emits the vtables and with
// them the ??_G at 0x5635a0, which calls the out-of-line ~LobbyItems
// (0x562df0) as the original does.
LobbyItems::LobbyItems(void)
{
}

// 0x561b80
void LobbyItems::OnLoad(void)
{
}

// 0x561f10
void LobbyItems::OnAnotherHand(int nWork, void* pData)
{
    m_loadJob();
    m_loadDone = true;
}

// 0x5621f0
void LobbyItems::OnDisplay(void)
{
    for (int i = 0; i < 2; ++i) {
        if (m_items[i]) {
            m_items[i]->Display();
        }
    }
}

// 0x562ee0
const WRTTI* LobbyItems::GetRTTI(void) const
{
    return &m_RTTI;
}
