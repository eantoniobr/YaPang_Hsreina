// Original: unknown, JP-only RTTI class LobbyAvatarActor (JP 983 exe)
#include "LobbyAvatarActor.h"

extern LobbyTextSource* data_00e74d14;

// Constructor (VA unknown). Defining it here emits the vtables and with
// them the ??_G at 0x591a00, which calls the out-of-line ~LobbyAvatarActor
// (0x590da0) as the original does.
LobbyAvatarActor::LobbyAvatarActor(void)
{
}

// 0x58c3f0
void LobbyAvatarActor::OnLoad(void)
{
}

// 0x58c400
void LobbyAvatarActor::OnInit(void)
{
}

// 0x58d120
void LobbyAvatarActor::OnPreLoadInit(void)
{
    m_attached = true;
    LoadOverlay(data_00e74d14->GetText(0));
}

// 0x590ef0
const WRTTI* LobbyAvatarActor::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x592610
void LobbyAvatarActor::OnDestroy(void)
{
    ReleaseOverlays();
}
