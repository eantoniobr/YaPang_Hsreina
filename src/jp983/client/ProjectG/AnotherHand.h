// Original: d:\build\custom\temp\code\client\projectg\anotherhand.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_ANOTHERHAND_H
#define PG_JP983_CLIENT_PROJECTG_ANOTHERHAND_H

// Receives the jobs a CAnotherHand runs on its worker thread (RTTI name
// CHandOwner; KR anotherhand.h). A one-slot interface; actors take it as
// their second base, at 0x18 after IActor.
class CHandOwner
{
public:
    virtual void OnAnotherHand(int nWork, void* pData) = 0;   // 0
};

#endif // PG_JP983_CLIENT_PROJECTG_ANOTHERHAND_H
