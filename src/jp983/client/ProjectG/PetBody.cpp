// Original: client/ProjectG/PetBody.cpp (JP 983 exe)
#include "jp983/client/ProjectG/PetBody.h"

// An unnamed global point (0xf02454) the JP code measures angles to.
extern "C" WVector data_f02454;

#include <string.h>

// 0x7098e0
void CPetBody::LookUp(WVector* target, bool immediate)
{
    if (m_pPet->FindBoneByTail("Head") == NULL)
        return;

    m_lookTarget = target;
    m_bLookImmediate = immediate;
}

// 0x709910 (KR petbody.cpp:1132; no reference in the JP exe)
float CPetBody::GetAnimationLength(const char* motionName)
{
    w_motion_data* md = m_pPet->FindMotionData(motionName);

    return md->e - md->s;
}

// 0x709930
void CPetBody::SetNextMotion(const char* motionName, bool loop)
{
    m_bNextMotionLoop = loop;
    strcpy(m_nextMotion, motionName);
}

// 0x709960
WPuppet* CPetBody::GetPet(void)
{
    return m_pPet;
}

// 0x709e10 (KR petbody.h:59, inline there)
WVector CPetBody::GetDirection(void) const
{
    return m_rotMatrix.za * -1.0f;
}

// 0x709e40 (KR petbody.h:62, inline there)
void CPetBody::RestoreLeanMat(void)
{
    m_matrix = m_rotMatrix;
}

// 0x709e90
void CPetBody::Reset(void)
{
    m_flags.Reset();
    m_lookTarget = NULL;
    m_lookAngleTarget.Reset();
    m_lookAngle.Reset();

    m_aniWeight = 1.0f;
    m_aniSpeed = 1.0f;
    m_nextMotion[0] = '\0';

    if (m_bResetJpVector)
        m_jpVector.Reset();
}

// 0x709ef0
float CPetBody::Move(float delta)
{
    float time = Min(m_pMotion->end, delta + m_motionTime);

    if (m_flags.GetFlag(2)) {
        if (!m_flags.GetFlag(1)) {
            m_accumDelta = m_pPet->GetDeltaVec(m_pMotion->name, m_motionTime - m_pMotion->s, time - m_pMotion->s);
            m_flags.Enable(1);
        }
        else {
            m_accumDelta += m_pPet->GetDeltaVec(m_pMotion->name, m_motionTime - m_pMotion->s, time - m_pMotion->s);
        }
    }

    return time - m_motionTime;
}

// 0x70a020
void CPetBody::SetPos(const WVector& pos)
{
    m_pos = pos;
    m_rotMatrix.pivot = m_pos;
    m_matrix.pivot = m_pos;
    m_flags.Enable(0x10);
    m_flags.Disable(2);
}

// 0x70a090
void CPetBody::SetRotate(const WVector& rotation)
{
    m_rotation = rotation;
    m_rotMatrix = RotMat(m_rotation.x, 0) * RotMat(m_rotation.y, 1) * RotMat(m_rotation.z, 2);
    m_rotMatrix.pivot = m_pos;
    m_matrix = m_rotMatrix;

    m_flags.Enable(0x10);
}

// 0x70a1d0
void CPetBody::SetRotate_Lean(const WVector& rotation)
{
    m_rotation = rotation;
    m_matrix = RotMat(m_rotation.x, 0) * RotMat(m_rotation.y, 1) * RotMat(m_rotation.z, 2);
    m_matrix.pivot = m_pos;

    m_flags.Enable(0x10);
}

// 0x70a2c0
void CPetBody::SetRotate(float angle)
{
    WVector pivot = m_rotMatrix.pivot;
    m_rotation = WVector(0.0f, angle, 0.0f);
    m_rotMatrix = RotMat(angle, 1);
    m_rotMatrix.pivot = pivot;
    m_matrix = m_rotMatrix;

    m_flags.Enable(0x10);
}

// 0x70a740
void CPetBody::TakeOff(WVector dir)
{
    m_flightState = 0; m_takeOffPos = m_pos;
    m_takeOffDir = dir;
    m_takeOffAngle = -0.78539819f;
    m_takeOffHeight = 0.0f;
    m_takeOffSpeed = 50.0f;
}

// 0x70a7b0
bool CPetBody::ShouldDisplay(void)
{
    return !m_flags.GetFlag(0x2000) ? true : false;
}

// 0x70a7c0
void CPetBody::SetPivot(const char* boneName, WVector offset)
{
    if (m_pPet) {
        WVector pivot = m_pPet->GetPivot(boneName);
        pivot += offset;
        pivot *= m_scale;

        m_pos -= pivot;
    }
}

// 0x70a860
void CPetBody::SetScale(float scale)
{
    m_scale = scale;
    { WVector pg_scale(scale, scale, scale); m_matrix.AxisScale(pg_scale); }

    if (m_pPet) {
        WMatrix mat = m_pPet->GetMatrix();
        { WVector pg_scale(scale, scale, scale); mat.AxisScale(pg_scale); }
        m_pPet->SetMatrix(mat);
    }
}

// 0x70ab50 (JP only; called by CFxSpray::Process): the yaw between the
// facing direction and the direction from the body to a global point,
// unnamed in the JP exe (0xf02454, referenced 117 times; role unknown).
float CPetBody::GetDeltaAngleFromPoint(void) const
{
    return CalcDeltaAngle(data_f02454 - m_rotMatrix.pivot, m_rotMatrix.za * -1.0f);
}

// 0x70abb0
void CPetBody::Update(void)
{
    m_pPet->SetMatrix(m_matrix);
    m_pPet->AnimateBones(NULL, NULL, m_motionTime, m_flags.GetFlag(2) ? 1 : 0, NULL, false);
    m_pPet->Transform(NULL, 1.0f, 0);
    m_pPet->UpdateBSphere();
}

// 0x70bcb0
void CPetBody::AddScriptHandle(const char* name, IActor* actor, int id)
{
    ScriptHandle* handle = new ScriptHandle;

    handle->name = name;
    handle->actor = actor;
    handle->id = id;

    m_scriptHandles += handle;
}

// 0x70c8c0
void CPetBody::SetCustomGround(char* groundName)
{
    m_customGround = groundName;
}

// 0x70d1d0
// Placeholder: the real constructor (0x70d1d0) and destructor (0x70d320) are
// not written yet; this empty body makes cl emit the vtable and the scalar
// deleting destructor. The destructor must stay undefined here, or cl
// inlines it into ??_G.
CPetBody::CPetBody(const char* script, bool arg)
{
}
