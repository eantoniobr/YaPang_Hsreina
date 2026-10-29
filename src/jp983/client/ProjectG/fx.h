// Original: d:\build\custom\temp\code\client\projectg\fx.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_FX_H
#define PG_JP983_CLIENT_PROJECTG_FX_H

#include <map>

#include "defines.h"
#include "padding.h"
#include "FxBox.h"
#include "scenemanager.h"

class CFxSequence;
class CFxSpray;
class CFxKeeper;
class CGolfBall;
struct sFxKeeper;

// CFx's effect box (RTTI .?AVCPvsFxBox@@ : CFxBox, vtable 0xcff340, seven
// slots). Only its JP size is known (CFx::m_controls follows it at 0x46C);
// the members of both classes are not modelled yet.
class CPvsFxBox : public CFxBox {
public:
	UNKNOWN(0x4, 0x440);
};
CHECK_SIZE(CPvsFxBox, 0x440);

// Base of the effects CFx runs (RTTI .?AVCFxControl@@, vtable 0xd3458c:
// the scalar deleting destructor 0x878ca0 and Process, pure).
class CFxControl {
public:
	// fx.h:20
	virtual ~CFxControl(void) {}
	virtual bool Process(float fDelta) = 0;   // vtable slot 1 (_purecall)

	unsigned long m_serial;                    // 0x04, CFx's map key
};
CHECK_SIZE(CFxControl, 0x8);
CHECK_FIELD(CFxControl, m_serial, 0x4);

// CFxControl::ms_serial: the next serial, unnamed in the JP exe.
extern "C" unsigned long data_e7d5c0;

// RTTI .?AVCFxPowerSpin@@, vtable 0xd34774. Fields: KR layout, not
// verified in the JP code yet.
class CFxPowerSpin : public CFxControl {
public:
	CFxPowerSpin(CPvsFxBox& box, CGolfBall& ball);
	virtual ~CFxPowerSpin(void);
	virtual bool Process(float fDelta);

	CPvsFxBox& m_box;                          // 0x08
	CGolfBall& m_ball;                         // 0x0C
	CFxSequence* m_pSequence;                  // 0x10
	bool m_bEnd;                               // 0x14
	PADDING(0x15, 0x18);
};

// Fields: KR layout, not verified in the JP code yet.
class CFxShotImpact : public CFxControl {
public:
	CFxShotImpact(CPvsFxBox& box, CGolfBall& ball);
	virtual ~CFxShotImpact(void);
	virtual bool Process(float fDelta);

	CPvsFxBox& m_box;                          // 0x08
	CGolfBall& m_ball;                         // 0x0C
	CFxSequence* m_pSequence;                  // 0x10
	bool m_bEnd;                               // 0x14
	PADDING(0x15, 0x18);
};

// RTTI .?AVCFxClubImpact@@, vtable 0xd34824. Fields: KR layout, not
// verified in the JP code yet.
class CFxClubImpact : public CFxControl {
public:
	CFxClubImpact(CPvsFxBox& box, CGolfBall& ball, unsigned long clubId);
	virtual ~CFxClubImpact(void);
	virtual bool Process(float fDelta);

	CPvsFxBox& m_box;                          // 0x08
	CGolfBall& m_ball;                         // 0x0C
};

// Vtable 0xd34624; layout from the JP constructor (0x8796d0).
class CFxPowerShot2 : public CFxControl {
public:
	CFxPowerShot2(CPvsFxBox& box, CGolfBall& ball);
	virtual ~CFxPowerShot2(void);
	virtual bool Process(float fDelta);

	bool m_bDone;                              // 0x08
	CPvsFxBox& m_box;                          // 0x0C
	CGolfBall& m_ball;                         // 0x10
};
CHECK_SIZE(CFxPowerShot2, 0x14);
CHECK_FIELD(CFxPowerShot2, m_bDone, 0x8);

// The effect manager singleton (RTTI .?AVCFx@@: CRenderFuncPtr at 0,
// WSingleton<CFx> (BaseObject) at +4; vtables 0xd348d8 and 0xd348d0).
// The WSingleton base is not modelled (its vtable holds the destructor, so
// no destructor is declared here); only the members the JP bodies use are.
class CFx : public CRenderFuncPtr {
	LAYOUT_CHECK_FRIEND;
public:
	virtual void Display(void);                // 1
	virtual void Process(float fDelta);        // 3

	CFxSequence* OpenSequence(const char* name, bool bOriginal);
	void CloseSequence(CFxSequence* pSequence, bool bImmediate);
	CFxSpray* OpenSpray(const char* name);
	void CloseSpray(CFxSpray* pSpray);
	void AddFxKeeper(sFxKeeper& keeper);
	void EraseFxKeeper(CFxKeeper* pKeeper);
	void ClearFxKeeper(void);
	void SetActive(bool bActive);
	CFxSpray* GetSpray(int index);
	void ClearAll(bool bKeepActive);

protected:
	void ClearControl(void);

public:

	UNKNOWN(0x4, 0x2C);                        // WSingleton<CFx> base
	CPvsFxBox m_fxBox;                         // 0x2C
	std::map<int, CFxControl*> m_controls;     // 0x46C, by CFxControl::m_serial (0x10 bytes)
	bool m_bActive;                            // 0x47C
};

BEGIN_LAYOUT_CHECK(CFx)
	CHECK_FIELD(CFx, m_fxBox, 0x2C);
	CHECK_FIELD(CFx, m_controls, 0x46C);
	CHECK_FIELD(CFx, m_bActive, 0x47C);
END_LAYOUT_CHECK

// WSingleton<CFx>::m_pInstance (no symbol in the JP exe).
extern "C" CFx* data_e78c1c;

#endif // PG_JP983_CLIENT_PROJECTG_FX_H
