// Original: unknown, JP-only RTTI class FrAttendanceDlg (JP 983 exe)
#ifndef PG_JP983_NEW_FRATTENDANCEDLG_H
#define PG_JP983_NEW_FRATTENDANCEDLG_H

#include "defines.h"
#include "padding.h"

class WRTTI;
class WPoint;
class WRect;
class CChatMsg;
class FrWndManager;
struct FrInputState;

// The attendance (daily check-in) dialog of the JP client, an FrForm
// (FrForm : FrWnd : IObject, FrCmdTarget; FrModalRenderer at 8). Its RTTI
// names the hierarchy; only the primary vtable's slots up to the ones this
// unit defines are declared (vtable 0xcfe794, 38 slots). The slots follow
// KR Fresh's FrWnd order; the trivial ones are the FrWnd inline virtuals,
// identical-COMDAT-folded with every other window class's copy.
class FrAttendanceDlg {
public:
	virtual const WRTTI* GetRTTI(void) const;                             // slot 0
	virtual ~FrAttendanceDlg(void);                                       // slot 1
	virtual bool Close(bool bDestroy);                                    // slot 2
	virtual bool Create(const char* name, const char* text, FrWndManager* pWndManager, unsigned long style,
	                    const WRect& rect, void* pParent);                // slot 3
	virtual void PreCreateWindow(FrWndManager* pWndManager, unsigned long style, const WRect& rect,
	                             void* pParent);                          // slot 4
	virtual void MoveWindow(const WPoint& pt);                            // slot 5
	virtual void Enable(bool bEnable);                                    // slot 6
	virtual void SetVisible(bool bVisible);                               // slot 7
	virtual void OnDraw(void);                                            // slot 8
	virtual void OnProc(const float dt);                                  // slot 9
	virtual void OnResize(void);                                          // slot 10
	virtual void OnMouseMove(const WPoint& pt);                           // slot 11
	virtual bool OnLButtonUp(const WPoint& pt);                           // slot 12
	virtual bool OnLButtonDown(const WPoint& pt);                         // slot 13
	virtual bool OnRButtonUp(const WPoint& pt);                           // slot 14
	virtual bool OnRButtonDown(const WPoint& pt);                         // slot 15
	virtual void OnDblClick(const WPoint& pt);                            // slot 16
	virtual void OnWheel(FrInputState& input);                            // slot 17
	virtual const char* OnSelectText(const FrInputState* pInput);         // slot 18
	virtual void OnKeyFocus(CChatMsg* pMsg);                              // slot 19
	virtual void OnSetCursor(bool b, const WPoint& pt);                   // slot 20
	virtual void EnableKeyFocus(FrInputState& input);                     // slot 21

	static const WRTTI m_RTTI;   // 0xe73df4

	PADDING(0x04, 0x1c);
	unsigned long m_nFlags;      // 0x1c
};
CHECK_FIELD(FrAttendanceDlg, m_nFlags, 0x1c);

#endif // PG_JP983_NEW_FRATTENDANCEDLG_H
