// Original: d:\build\custom\temp\code\client\projectg\fxbox.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_FXBOX_H
#define PG_JP983_CLIENT_PROJECTG_FXBOX_H

#include "defines.h"
#include "padding.h"

class CFxSequence;
class CFxSpray;
class CFxKeeper;
class WView;
struct defines_t;
struct sFxKeeper;

// The effect container (KR fxbox.h). Only what the JP bodies call is
// declared: the vtable pointer and the members the CFx wrappers forward to.
// Its JP size is not known; CPvsFxBox (fx.h) covers the whole object.
class CFxBox {
public:
	virtual ~CFxBox(void);                                    // 0
	virtual void ProcessAttacher(float fDelta);               // 1, CFx::Process calls it

	void Display(WView* pView);
	CFxSequence* LoadSequence(const char* name, bool bOriginal, defines_t* pDefines);
	void AddSequence(CFxSequence* pSequence);
	CFxSpray* LoadSpray(const char* name, defines_t* pDefines);
	void AddSpray(CFxSpray* pSpray);
	void DeleteSequence(CFxSequence* pSequence, bool bImmediate);
	void DeleteSpray(CFxSpray* pSpray);
	void AddFxKeeper(sFxKeeper& keeper);
	void EraseFxKeeper(CFxKeeper* pKeeper);
	void ClearFxKeeper(void);
	CFxSpray* GetSpray(int index);                             // JP copy 0x87c780 (fx unit)
	bool Process(float fDelta);
	void ClearAll(bool bKeepActive);
};

#endif // PG_JP983_CLIENT_PROJECTG_FXBOX_H
