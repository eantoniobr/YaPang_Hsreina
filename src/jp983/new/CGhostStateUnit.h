// Original: unknown, JP-only RTTI class CGhostStateUnit (JP 983 exe)
#ifndef PG_JP983_NEW_CGHOSTSTATEUNIT_H
#define PG_JP983_NEW_CGHOSTSTATEUNIT_H

#include "defines.h"
#include "padding.h"

class CSequenceStateMachine;

// The JP RTTI names CGhostStateUnit in GhostPlayer.cpp's anonymous namespace
// (.?AVCGhostStateUnit@?A0x48d90224@@), as in KR's GhostPlayer.cpp. Declared
// here at global scope so its JP-only unit can define its slots; the bodies
// are KR's (client/ProjectG/GhostPlayer.cpp).

// KR client/ProjectG/SequenceStateMachine.h. JP vtable 0xd2fb60: slots 0, 2,
// 3 and 4 pure, the destructor at slot 1 (0x829430). It belongs in a jp983
// SequenceStateMachine.h once a JP unit needs the machine itself.
class CStateUnit
{
    LAYOUT_CHECK_FRIEND;
    friend class CSequenceStateMachine;
public:
    virtual const char* GetClassNameA(void) const = 0; // 0
    virtual ~CStateUnit(void) {}                       // 1

protected:
    CStateUnit(void) : m_order(0) {}

private:
    virtual void OnProcess(float fDelta) = 0;          // 2
public:
    virtual void OnRender(void) = 0;                   // 3
private:
    virtual bool OnFinished(void) = 0;                 // 4

protected:
    CSequenceStateMachine* m_pOwner; // 0x4
    int m_order;                     // 0x8
};
CHECK_SIZE(CStateUnit, 0xC);
BEGIN_LAYOUT_CHECK(CStateUnit)
    CHECK_FIELD(CStateUnit, m_pOwner, 0x4);
    CHECK_FIELD(CStateUnit, m_order, 0x8);
END_LAYOUT_CHECK

// A state of the ghost replay: runs OnStateRun once per frame until it
// reports done, and stays current until m_timer runs out. JP vtable 0xd2fb78.
class CGhostStateUnit : public CStateUnit
{
    LAYOUT_CHECK_FRIEND;
public:
    virtual const char* GetClassNameA(void) const;     // 0 (0x8294d0, GhostPlayer)
    CGhostStateUnit(void);
    virtual ~CGhostStateUnit(void) {}                  // 1 (??_G 0x8295b0)

    virtual void OnRender(void);                       // 3 (0x829500)

    virtual bool OnStateRun(void) = 0;                 // 5

private:
    virtual void OnProcess(float fDelta);              // 2 (0x829510, GhostPlayer)
    virtual bool OnFinished(void);                     // 4 (0x829590)

protected:
    float m_elapsed;   // 0xc
    float m_timer;     // 0x10
    float m_timeLimit; // 0x14
    bool m_done;       // 0x18
    float m_delta;     // 0x1c
};
CHECK_SIZE(CGhostStateUnit, 0x20);
BEGIN_LAYOUT_CHECK(CGhostStateUnit)
    CHECK_FIELD(CGhostStateUnit, m_elapsed, 0xc);
    CHECK_FIELD(CGhostStateUnit, m_timer, 0x10);
    CHECK_FIELD(CGhostStateUnit, m_timeLimit, 0x14);
    CHECK_FIELD(CGhostStateUnit, m_done, 0x18);
    CHECK_FIELD(CGhostStateUnit, m_delta, 0x1c);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_CGHOSTSTATEUNIT_H
