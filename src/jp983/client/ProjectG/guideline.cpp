// Original: d:\build\custom\temp\code\client\projectg\guideline.cpp (JP 983 exe)
#include "jp983/client/ProjectG/guideline.h"
#include "ObjectFactory.h"
#include "wresrcmng.h"

// The scene manager instance (KR CSceneManager::Instance()), unnamed global.
extern "C" CSceneManager* data_e741c0;

// 0x75b1e0
void CGuideLine::OnLoad(void)
{
}

// 0x75b1f0
void CGuideLine::OnInit(void)
{
    m_bHidden = m_bFading = false;
    m_bActive = false;
    m_segmentTime = 0;
    m_segmentCount = 0;
    m_bDirty = false;
    m_jpIndexE2C = -1;
}

// 0x75b210
CGuideLine::sRoad::sRoad(void)
{
}

// 0x75b220
void CGuideLine::OnPreLoadInit(void)
{
    m_pVertex[0] = &m_vertex[0];
    m_pVertex[1] = &m_vertex[1];
    m_pVertex[2] = &m_vertex[3];
    m_pVertex[3] = &m_vertex[2];
    m_pVertex[4] = NULL;

    for (int i = 0; i < 80; i++) {
        m_road[i].m_pFx = NULL;
    }

    // "\xB0\xA1\xC0\xCC\xB5\xE5\xB6\xF3\xC0\xCE" is "guide line" in Korean (CP949)
    data_e741c0->RegisterElement((eObjType)1, NULL, this, "\xB0\xA1\xC0\xCC\xB5\xE5\xB6\xF3\xC0\xCE", 0, NULL);

    m_texture = data_f023f0->LoadTexture("~Track.jpg", 0, 0, NULL);
}

// 0x75b320
CGuideLine::CGuideLine(void) : m_texture(0)
{
    AddSkipList(0x85806);
}

// 0x75b390
const WRTTI* CGuideLine::GetRTTI(void) const
{
    return &m_RTTI;
}

// 0x75b3a0 (no reference; ??_G 0x75b3c0 inlines it)
CGuideLine::~CGuideLine(void)
{
}

// 0x75b630: the factory function registered under "CGuideLine". Our cl
// inlines the constructor here; the original (/LTCG) calls it.
IObject* CGuideLineMakeInstance(void)
{
    return new CGuideLine;
}

// 0x75b6a0 (and its static instance's initializer)
struct __impCGuideLine
{
    __impCGuideLine(void)
    {
        ObjectFactory().AddObjectFunctor(CGuideLineMakeInstance, "CGuideLine");
        ActorFactory().AddActorClass("CGuideLine");
    }
};
static __impCGuideLine s_impCGuideLine;
