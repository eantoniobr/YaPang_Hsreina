// Original: client/Fresh/include/frform.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRFORM_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRFORM_H

#include "defines.h"
#include "padding.h"

#include "client/FreshNext/include/frwnd.h"

// Result a form closes with (KR frform.h enum).
enum eFormRet {
	FrNONE = 0,
	FrOK = 1,
	FrCANCEL = 2,
	FrYES = 3,
	FrNO = 4
};

class FrForm;

// Creates the form `name` of the window manager's layout as a T owned by
// pOwner (KR frform.h:23-32). JP instances: CreateForm<FrCardRemoveConfirm>
// 0x7fee40 (new 0x120, the constructor, _Init, the cast; on failure the
// virtual destructor), CreateForm<FrForm> 0x48b8a0.
template <class T>
T* CreateForm(FrWndManager* pManager, FrCmdTarget* pOwner, const char* name, FrWnd* pParent)
{
	T* pForm = new T;
	FrForm* pRet = pForm->_Init(pManager, pOwner, name, pParent);
	if (pRet) {
		return DYNAMIC_CAST(T, pRet);
	}
	delete pForm;
	return 0;
}

// A dialog window (RTTI FrForm : FrWnd; m_RTTI 0xf1aabc). Size 0x110: the
// first member of every JP FrForm dialog is at 0x110 (NewRecordDlg). The
// constructor 0xbe5e20 and destructor 0xbe5e80 are out of line: a derived
// class declares its own destructor without defining it in a game unit
// (defining it lets cl inline FrForm's into ??_G). The new virtuals are slots
// 24-37 in KR frform.h's declaration order (cl places overloads in reverse
// declaration order): JP-verified Close(ret, bDestroy) at 26 (gui_control,
// UccDrawDlg 0x7e2d90) and OnCancel at 34 (UccDrawDlg 0x7e57a0); the others
// are KR names at the slots that order gives.
class FrForm : public FrWnd {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                                 // 0xf1aabc
	virtual const WRTTI* GetRTTI(void) const;                                  // 0

	FrForm(void);                                                              // 0xbe5e20
	virtual ~FrForm(void);                                                     // 1 (0xbe5e80)

	FrForm* _Init(FrWndManager* pWndManager, FrCmdTarget* pCmdDest, const char* name, FrWnd* pParent);   // 0xbe6940

	virtual bool Open(FRESH_RESULT_CALLBACK pfnResult, unsigned long flag);                    // 25
	virtual bool Open(FRESH_RESULT_CALLBACK pfnResult, const WPoint& pt, unsigned long flag);  // 24
	virtual bool Close(eFormRet ret, bool bDestroy);                           // 26 (0xbe5fa0)
	virtual bool Close(bool bDestroy);                                         // FrWnd's slot 2
	virtual void SetCaption(const char* caption);                              // 27
	virtual void SetDesc(const char* desc);                                    // 28
	virtual void SetMessage(const char* message, bool b);                      // 29
	virtual void EnableDrag(bool bEnable);                                     // 30
	virtual void SetTimeLimit(float timeLimit);                                // 31
	virtual bool OnInit(void);                                                 // 32

protected:
	virtual void OnOK(void);                                                   // 33
	virtual void OnCancel(void);                                               // 34

	void OnFreshOkay(void);                                                    // 0xbe5e10
	void OnFreshCancel(void);                                                  // 0xbe5e00

public:
	virtual void SetRect(const WRect& rect);                                   // 35
	virtual void SetClientRect(const WRect& rect);                             // 36

private:
	virtual bool IsResizeBtnArea(const WPoint& pt);                            // 37

protected:
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;                    // FrCmdTarget 1

	PADDING(0x044, 0x110);
};

CHECK_SIZE(FrForm, 0x110);

// FrForm::ms_bHasTail (KR static member; 0xe43438, no symbol in the JP exe).
extern "C" bool data_e43438;

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRFORM_H
