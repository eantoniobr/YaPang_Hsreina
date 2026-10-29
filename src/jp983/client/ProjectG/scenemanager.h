// Original: client/ProjectG/scenemanager.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_SCENEMANAGER_H
#define PG_JP983_CLIENT_PROJECTG_SCENEMANAGER_H

#include "defines.h"

class WPuppet;
class Waabb;

// Kind of a registered scene element; the enumerators are not known yet.
enum eObjType {
};

// The render callback interface, declared only as far as the JP bodies need
// it. The JP bodies of slots 0 (0x5f0850) and 2 (0x5f0860) are empty.
class CRenderFuncPtr
{
public:
    CRenderFuncPtr(void) {}
    ~CRenderFuncPtr(void) {}

    virtual void DisplayShadow(void);                         // 0
    virtual void Display(void) = 0;                           // 1

protected:
    virtual void DebugDisplay(void);                          // 2
};

CHECK_SIZE(CRenderFuncPtr, 0x4);

// The scene's element registry; only RegisterElement is declared. The JP
// instance pointer is the unnamed global at 0xe741c0.
class CSceneManager
{
public:
    void RegisterElement(eObjType type, WPuppet* pPuppet, CRenderFuncPtr* pRender, const char* name, unsigned long flags, Waabb* pBox);
};

#endif // PG_JP983_CLIENT_PROJECTG_SCENEMANAGER_H
