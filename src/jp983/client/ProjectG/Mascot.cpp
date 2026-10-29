// Original: d:\build\custom\temp\code\client\projectg\mascot.cpp (JP 983 exe)
#include "mascot.h"

#include "ObjectFactory.h"
#include "commonutil.h"

// The scene manager instance (KR CSceneManager::Instance()), unnamed global.
extern "C" CSceneManager* data_e741c0;

// 0x761cd0 (unplaced in the pairing, so not scored): defined to emit the
// vtable and the scalar deleting destructor. Only the JP-only member is
// written; sMascot's constructor zeroes the mascots.
CMascot::CMascot(void)
{
    m_pMsgObject = new CMascotMsgObject(0, 0);
}

// 0x761e20
void CMascot::OnPreLoadInit(void)
{
    for (int i = 0; i < 4; i++) {
        CRenderFuncPtr* pRender = this;
        CSceneManager* pScene = data_e741c0;
        pScene->RegisterElement((eObjType)4, 0, pRender, MakeStr("mascot%02d", i), 8, 0);
    }
}

// 0x762230: the factory function registered under "CMascot".
IObject* CMascotMakeInstance(void)
{
    return new CMascot;
}

// 0x7622a0 (and its static instance's initializer)
struct __impCMascot
{
    __impCMascot(void)
    {
        ObjectFactory().AddObjectFunctor(CMascotMakeInstance, "CMascot");
        ActorFactory().AddActorClass("CMascot");
    }
};
static __impCMascot s_impCMascot;

// 0x7632b0
CCameraBird::CCameraBird(const char* name, unsigned char playerIndex)
{
    Init(name, 8);
    m_playerIndex = playerIndex;
    m_unk74 = 0.5f;
}
