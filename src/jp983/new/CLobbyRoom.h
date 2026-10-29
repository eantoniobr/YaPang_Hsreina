// Original: unknown, JP-only RTTI class CLobbyRoom (JP 983 exe)
#ifndef PG_JP983_NEW_CLOBBYROOM_H
#define PG_JP983_NEW_CLOBBYROOM_H

// JP-only class (RTTI name CLobbyRoom), vtable at 0xd0c55c, 9 slots, no
// base. Its constructor (0x598140) and destructor (0x5981d0, which releases
// the object held in 0xe75e34) were split to LobbyMain. Slots 1-8 are empty
// handlers whose callers are not known, so their names only say their shape.
class CLobbyRoom
{
public:
    CLobbyRoom();                                     // 0x598140
    virtual ~CLobbyRoom();                            // 0 (??_G 0x598870; ~ 0x5981d0)
    virtual void OnRoomEvent(int arg);                // 1 (0x598150, empty)
    virtual void OnRoomUpdate(int arg1, int arg2);    // 2 (0x598160, empty)
    virtual void OnRoomMessage(int arg1, int arg2);   // 3 (0x598170, empty)
    virtual void OnRoomNotify(int arg1, int arg2);    // 4 (0x598180, empty)
    virtual void OnPlayerEnter(int arg);              // 5 (0x598190, empty)
    virtual void OnPlayerLeave(int arg);              // 6 (0x5981a0, empty)
    virtual void OnPlayerChange(int arg);             // 7 (0x5981b0, empty)
    virtual void OnRoomRefresh();                     // 8 (0x5981c0, empty; also in vtable 0xd0c5f0)
};

#endif // PG_JP983_NEW_CLOBBYROOM_H
