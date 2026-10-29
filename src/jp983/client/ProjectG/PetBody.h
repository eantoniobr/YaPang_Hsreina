// Original: client/ProjectG/petbody.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_PETBODY_H
#define PG_JP983_CLIENT_PROJECTG_PETBODY_H

#include "defines.h"
#include "padding.h"
#include "wflag.h"
#include "wlist.h"
#include "wmath.h"
#include "wpuppet.h"

#include <string>

// The animated body of a pet or caddie (JP 983 layout). The layout is known
// only as far as the bodies read it: the JP class has a WVector KR lacks
// (0x80), so everything from KR's m_pos on sits 0xc bytes later.
class IActor;

class CPetBody {
    LAYOUT_CHECK_FRIEND;
public:
    // A script callback registered by name (size 0xc, KR).
    struct ScriptHandle {
        const char* name;   // 0x0
        IActor* actor;      // 0x4
        int id;             // 0x8
    };

    CPetBody(const char* script, bool arg);
    virtual ~CPetBody(void);
    virtual void Display(void);
    virtual void DisplayShadow(char* name);
    virtual void Process(float delta);

    void Reset(void);
    void SetPos(const WVector& pos);
    void TakeOff(WVector dir);
    void SetRotate(const WVector& rotation);
    void SetRotate(float angle);
    void SetRotate_Lean(const WVector& rotation);
    float GetDeltaAngleFromPoint(void) const;
    void SetScale(float scale);
    void Update(void);
    void RestoreLeanMat(void);
    WVector GetDirection(void) const;
    void LookUp(WVector* target, bool immediate);
    float GetAnimationLength(const char* motionName);
    void SetNextMotion(const char* motionName, bool loop);
    void AddScriptHandle(const char* name, IActor* actor, int id);
    void SetCustomGround(char* groundName);
    WPuppet* GetPet(void);

protected:
    float Move(float delta);
    void SetPivot(const char* boneName, WVector offset);
    bool ShouldDisplay(void);

    WPuppet* m_pPet;            // 0x4
    PADDING(0x8, 0xc);          // 0x8 m_shadowType (KR)
    const w_motion_data* m_pMotion; // 0xc
    float m_motionTime;         // 0x10, the frame the bones are sampled at
    WMatrix m_rotMatrix;        // 0x14, rotation, pivot = m_pos
    WMatrix m_matrix;           // 0x44, m_rotMatrix scaled (or leaned)
    WVector m_rotation;         // 0x74, Euler angles of m_rotMatrix (KR)
    WVector m_jpVector;         // 0x80, JP only; Reset zeroes it when m_bResetJpVector
    WVector m_pos;              // 0x8c
    WVector m_moveDelta;        // 0x98 (KR)
    float m_scale;              // 0xa4
    int m_flightState;          // 0xa8, 0 after TakeOff (KR)
    bool m_bFlying;             // 0xac, role unconfirmed (KR)
    PADDING(0xad, 0xb0);
    WVector m_takeOffDir;       // 0xb0
    WVector m_takeOffPos;       // 0xbc, m_pos when TakeOff was called
    float m_takeOffHeight;      // 0xc8, role unconfirmed (reset to 0)
    float m_takeOffSpeed;       // 0xcc, role unconfirmed (set to 50)
    float m_takeOffAngle;       // 0xd0, role unconfirmed (set to -pi/4)
    WFlags m_flags;             // 0xd4; 0x2: the motion loops, 0x10: matrix changed, 0x2000: hidden
    WList<ScriptHandle*> m_scriptHandles;  // 0xd8
    PADDING(0xf8, 0x128);
    std::string m_customGround; // 0x128
    WVector m_accumDelta;       // 0x144, the motion deltas Move accumulated (body frame)
    float m_aniSpeed;           // 0x150, role unconfirmed (reset to 1)
    float m_aniWeight;          // 0x154, role unconfirmed (reset to 1)
    char m_nextMotion[32];      // 0x158
    bool m_bNextMotionLoop;     // 0x178
    PADDING(0x179, 0x188);
    bool m_bResetJpVector;      // 0x188, JP only; role unconfirmed
    PADDING(0x189, 0x18c);
    WVector* m_lookTarget;      // 0x18c
    bool m_bLookImmediate;      // 0x190
    PADDING(0x191, 0x194);
    WVector2D m_lookAngle;      // 0x194, role unconfirmed
    WVector2D m_lookAngleTarget; // 0x19c, role unconfirmed
};
BEGIN_LAYOUT_CHECK(CPetBody)
    CHECK_FIELD(CPetBody, m_pPet, 0x4);
    CHECK_FIELD(CPetBody, m_pMotion, 0xc);
    CHECK_FIELD(CPetBody, m_motionTime, 0x10);
    CHECK_FIELD(CPetBody, m_rotMatrix, 0x14);
    CHECK_FIELD(CPetBody, m_matrix, 0x44);
    CHECK_FIELD(CPetBody, m_jpVector, 0x80);
    CHECK_FIELD(CPetBody, m_pos, 0x8c);
    CHECK_FIELD(CPetBody, m_scale, 0xa4);
    CHECK_FIELD(CPetBody, m_flightState, 0xa8);
    CHECK_FIELD(CPetBody, m_takeOffDir, 0xb0);
    CHECK_FIELD(CPetBody, m_takeOffPos, 0xbc);
    CHECK_FIELD(CPetBody, m_takeOffHeight, 0xc8);
    CHECK_FIELD(CPetBody, m_takeOffSpeed, 0xcc);
    CHECK_FIELD(CPetBody, m_takeOffAngle, 0xd0);
    CHECK_FIELD(CPetBody, m_flags, 0xd4);
    CHECK_FIELD(CPetBody, m_scriptHandles, 0xd8);
    CHECK_FIELD(CPetBody, m_customGround, 0x128);
    CHECK_FIELD(CPetBody, m_accumDelta, 0x144);
    CHECK_FIELD(CPetBody, m_aniSpeed, 0x150);
    CHECK_FIELD(CPetBody, m_aniWeight, 0x154);
    CHECK_FIELD(CPetBody, m_nextMotion, 0x158);
    CHECK_FIELD(CPetBody, m_bNextMotionLoop, 0x178);
    CHECK_FIELD(CPetBody, m_bResetJpVector, 0x188);
    CHECK_FIELD(CPetBody, m_lookTarget, 0x18c);
    CHECK_FIELD(CPetBody, m_bLookImmediate, 0x190);
    CHECK_FIELD(CPetBody, m_lookAngle, 0x194);
    CHECK_FIELD(CPetBody, m_lookAngleTarget, 0x19c);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_PETBODY_H
