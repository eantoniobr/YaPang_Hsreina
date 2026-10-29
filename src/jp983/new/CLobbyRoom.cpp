// Original: unknown, JP-only RTTI class CLobbyRoom (JP 983 exe)
#include "CLobbyRoom.h"

// 0x598140 (split to LobbyMain). Defining it here emits the vtable and with
// it the ??_G at 0x598870, which calls the out-of-line ~CLobbyRoom (0x5981d0)
// as the original does.
CLobbyRoom::CLobbyRoom()
{
}

// 0x598150
void CLobbyRoom::OnRoomEvent(int arg)
{
}

// 0x598160
void CLobbyRoom::OnRoomUpdate(int arg1, int arg2)
{
}

// 0x598170
void CLobbyRoom::OnRoomMessage(int arg1, int arg2)
{
}

// 0x598180
void CLobbyRoom::OnRoomNotify(int arg1, int arg2)
{
}

// 0x598190
void CLobbyRoom::OnPlayerEnter(int arg)
{
}

// 0x5981a0
void CLobbyRoom::OnPlayerLeave(int arg)
{
}

// 0x5981b0
void CLobbyRoom::OnPlayerChange(int arg)
{
}

// 0x5981c0
void CLobbyRoom::OnRoomRefresh()
{
}
