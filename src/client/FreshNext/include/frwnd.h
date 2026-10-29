// Original: client/Fresh/include/frwnd.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRWND_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRWND_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/Wangreal/include/wflag.h"
#include "jp983/client/Wangreal/include/wtypes.h"
#include "client/FreshNext/include/frcmdtarget.h"

// Fresh's cast helper (KR frwnd.h): every object including this header gets
// its own thread-local `__rtti_obj` (JP: TLS +0x114), which the cast assigns
// before IObject::IsKindOf. The macro name is invented.
static __declspec(thread) void* __rtti_obj;
#define DYNAMIC_CAST(T, p) ((T*)((__rtti_obj = (void*)(p)) != 0 ? ((IObject*)__rtti_obj)->DynamicCast(&T::m_RTTI) : 0))

class CChatMsg;
class FrGraphicInterface;
class FrWndManager;
struct FrInputState;

// JP only (RTTI name FrModalRenderer): the black backdrop behind a modal
// form, FrWnd's third base at +0x8 (vtable 0xd5e5e4, one slot: the deleting
// destructor; FrWnd's thunk 0xbe8da0). Members from the JP notes of KR
// frwnd.h (FrModalDim there), not re-verified here.
class FrModalRenderer {
	LAYOUT_CHECK_FRIEND;
public:
	virtual ~FrModalRenderer(void);                           // 0

private:
	float m_width;                        // 0x4
	float m_height;                       // 0x8
	FrGraphicInterface* m_pDevice;        // 0xc
	bool m_bActive;                       // 0x10
};

CHECK_SIZE(FrModalRenderer, 0x14);

// Base of every Fresh window (RTTI FrWnd : IObject, FrCmdTarget,
// FrModalRenderer; vtables 0xd5e604 (24 slots), 0xd5e5f4, 0xd5e5ec). Slots
// 0-22 in KR frwnd.h order (JP-verified by FrAttendanceDlg's folded inline
// virtuals 0-21 and SetIconRect's `ret 4` at 22, 0xbe8d90); slot 23 is JP
// only (0xbe76d0, `ret`). Every KR member sits 0x14 further on (the
// FrModalRenderer base): m_nFlags 0x1c (FrAttendanceDlg), m_rect 0x34
// (JukeBoxDlg, UccCopyDlg). Later members and the JP size are not modelled.
// m_RTTI: its initializer 0xcf7810 builds ("FrWnd", base WRTTI 0xf0073c).
class FrWnd : public IObject, public FrCmdTarget, public FrModalRenderer {
	LAYOUT_CHECK_FRIEND;
public:
	virtual const WRTTI* GetRTTI(void) const;                                  // 0 (0xbe8d40)
	virtual ~FrWnd(void);                                                      // 1 (??_G 0xbe90d0)
	virtual bool Close(bool bDestroy);                                         // 2
	virtual bool Create(const char* name, const char* text, FrWndManager* pWndManager, unsigned long style,
	                    const WRect& rect, FrWnd* pParent);                    // 3
	virtual void PreCreateWindow(FrWndManager* pWndManager, unsigned long style, const WRect& rect,
	                             FrWnd* pParent);                              // 4
	virtual void MoveWindow(const WPoint& pt);                                 // 5
	virtual void Enable(bool bEnable);                                         // 6
	virtual void SetVisible(bool bVisible);                                    // 7
	virtual void OnDraw(void);                                                 // 8
	virtual void OnProc(const float dt);                                       // 9
	virtual void OnResize(void);                                               // 10
	virtual void OnMouseMove(const WPoint& pt);                                // 11
	virtual bool OnLButtonUp(const WPoint& pt);                                // 12
	virtual bool OnLButtonDown(const WPoint& pt);                              // 13
	virtual bool OnRButtonUp(const WPoint& pt);                                // 14
	virtual bool OnRButtonDown(const WPoint& pt);                              // 15
	virtual void OnDblClick(const WPoint& pt);                                 // 16
	virtual void OnWheel(FrInputState& input);                                 // 17
	virtual const char* OnSelectText(const FrInputState* pInput);              // 18
	virtual void OnKeyFocus(CChatMsg* pMsg);                                   // 19
	virtual void OnSetCursor(bool b, const WPoint& pt);                        // 20
	virtual void EnableKeyFocus(FrInputState& input);                          // 21
	virtual void SetIconRect(const WRect& rect);                               // 22 (0xbe8d90)
	virtual void UnknownSlot23(void);                                          // 23 (0xbe76d0, JP only)

	static const WRTTI m_RTTI;                                                 // 0xf1aacc

	const WRect& GetRect(void) { return m_rect; }
	void SetFadeout(bool bFadeout);                                            // 0xbe7b70
	void SetAlpha2ToChild(float alpha);                                        // 0xbe8740

protected:
	FrWnd(void);

	WFlags m_nFlags;              // 0x1c (KR 0x8; private in KR)
	PADDING(0x020, 0x034);
	WRect m_rect;                 // 0x34 (KR 0x20)
};

BEGIN_LAYOUT_CHECK(FrWnd)
	CHECK_FIELD(FrWnd, m_nFlags, 0x1c);
	CHECK_FIELD(FrWnd, m_rect, 0x34);
END_LAYOUT_CHECK

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRWND_H
