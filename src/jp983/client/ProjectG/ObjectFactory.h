// Original: d:\build\custom\temp\code\client\projectg\objectfactory.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_OBJECTFACTORY_H
#define PG_JP983_CLIENT_PROJECTG_OBJECTFACTORY_H

#include "defines.h"
#include "jp983/client/ProjectG/RTTI.h"

// Root of the game's object hierarchy (RTTI name IObject): a vtable only.
// Slots as in KR objectfactory.h. IsKindOf / DynamicCast are KR's inline
// helpers: the JP DYNAMIC_CAST sites walk WRTTI::m_pBaseRTTI (+4) the same way.
class IObject
{
public:
    virtual const WRTTI* GetRTTI(void) const;                 // 0
    bool IsExactKindOf(const WRTTI* pRTTI) const { return GetRTTI() == pRTTI; }
    bool IsKindOf(const WRTTI* pRTTI) const {
        const WRTTI* pCur = GetRTTI();
        while (pCur != 0) {
            if (pCur == pRTTI) {
                return true;
            }
            pCur = pCur->GetBaseRTTI();
        }
        return false;
    }
    void* DynamicCast(const WRTTI* pRTTI) { return IsKindOf(pRTTI) ? this : 0; }
    virtual ~IObject(void);                                   // 1

protected:
    IObject(void);
};

CHECK_SIZE(IObject, 0x4);

// Factory function registered for each class name (KR typedef).
typedef IObject* (*IObjectFunc)(void);

// Name -> object and name -> factory function registries (KR
// objectfactory.h). The JP layout (VS 2010 std::map members) is not
// modelled yet: only the members the JP bodies call are declared.
class CObjectFactory
{
public:
    void AddObjectFunctor(IObjectFunc pfnMake, const char* name);     // 0xa4bcf0
};

CObjectFactory& ObjectFactory(void);                                  // 0xa4c0d0

// KR declares CActorFactory in actor.h; it is here until the shared jp983
// actor.h takes it. The list of actor class names; layout not modelled.
class CActorFactory
{
public:
    void AddActorClass(const char* name);                             // 0xa46aa0
};

CActorFactory& ActorFactory(void);                                    // 0xa471a0

#endif // PG_JP983_CLIENT_PROJECTG_OBJECTFACTORY_H
