// Original: d:\build\custom\temp\code\client\projectg\uccbase.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_UCCBASE_H
#define PG_JP983_CLIENT_PROJECTG_UCCBASE_H

#include <stddef.h>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/UccLibrary.h"
#include "jp983/client/Wangreal/include/wtypes.h"

class Bitmap;
class FrArea;
class FrUccDrawDlg;
PG_ENUM_FWD(eButton)

// Tool of the UCC canvas (KR uccbase.h); CUccBase::MouseEventHandler
// dispatches on it.
enum eMode {
	UCC_MODE_DRAW = 0,
	UCC_MODE_MOVE = 1,
	UCC_MODE_SPOID = 2,
	UCC_MODE_PAINT = 3,
	UCC_MODE_ZOOM_IN = 4,
	UCC_MODE_ZOOM_OUT = 5
};

// The UCC drawing canvas (KR uccbase.h CUccBase; RTTI .?AVCUccBase@@, vtable
// 0xd2930c, 18 slots in KR order, ctor 0x7de8d0, dtor 0x7de910). Size 0x88
// as in KR (the derived members of CUccColorPicker and CUccEditBrush start
// there). Only the members JP bodies use are declared, at their KR offsets
// (JP-verified: m_pTexture 0x8, m_pTexture32 0x10, m_pArea 0x14,
// m_refreshFlags 0x64, m_mode 0x80).
class CUccBase {
	LAYOUT_CHECK_FRIEND;
	friend class FrUccDrawDlg;   // Reset sets m_refreshFlags
public:
	CUccBase(void);                                                                  // 0x7de8d0
	virtual ~CUccBase(void);                                                         // slot 0, 0x7de910
	virtual void Initialize(FrArea* pArea, Bitmap* pTexture, Bitmap* pMask);         // slot 1, 0x7dd0b0
	virtual bool IsInitialized(void);                                                // slot 2
	virtual void InitVariables(void);                                                // slot 3, 0x7db9c0
	virtual void DestroyVariables(void);                                             // slot 4, 0x7dba00
	virtual void Process(void);                                                      // slot 5, 0x7dbab0
	virtual void MouseEventHandler(eButton button, int state, const WPoint& point);  // slot 6
	virtual bool IsMouseOver(const WPoint& point);                                   // slot 7
	virtual void Draw(int x, int y, Bitmap* pBrush, bool b);                         // slot 8
	virtual void DrawLine(IPoint from, IPoint to, Bitmap* pBrush);                   // slot 9

protected:
	virtual void Refresh2D(void);                                                    // slot 10
	virtual void Refresh3D(void);                                                    // slot 11
	virtual void RefreshCache(void);                                                 // slot 12
	virtual void DrawEventHandler(eButton button, int state, const WPoint& point);   // slot 13
	virtual void MoveEventHandler(eButton button, int state, const WPoint& point);   // slot 14
	virtual void SpoidEventHandler(eButton button, int state, const WPoint& point);  // slot 15
	virtual void PaintEventHandler(eButton button, int state, const WPoint& point);  // slot 16
	virtual void ZoomEventHandler(eButton button, int state, const WPoint& point);   // slot 17

public:
	void SetMode(eMode mode) { m_mode = mode; }
	eMode GetMode(void) { return m_mode; }
	void SetArea(FrArea* pArea) { m_pArea = pArea; }

protected:
	PADDING(0x04, 0x08);
	Bitmap* m_pTexture;          // 0x8
	PADDING(0x0c, 0x10);
	Bitmap* m_pTexture32;        // 0x10, the 32 bpp copy shown in m_pArea
	FrArea* m_pArea;             // 0x14, the window the canvas is drawn in
	PADDING(0x18, 0x64);
	int m_refreshFlags;          // 0x64, parts to refresh
	PADDING(0x68, 0x80);
	eMode m_mode;                // 0x80
	PADDING(0x84, 0x88);
};

CHECK_SIZE(CUccBase, 0x88);
BEGIN_LAYOUT_CHECK(CUccBase)
	CHECK_FIELD(CUccBase, m_pTexture, 0x08);
	CHECK_FIELD(CUccBase, m_pTexture32, 0x10);
	CHECK_FIELD(CUccBase, m_pArea, 0x14);
	CHECK_FIELD(CUccBase, m_refreshFlags, 0x64);
	CHECK_FIELD(CUccBase, m_mode, 0x80);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_UCCBASE_H
