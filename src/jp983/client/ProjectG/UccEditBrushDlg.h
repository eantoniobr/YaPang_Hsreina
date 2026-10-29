// Original: d:\build\custom\temp\code\client\projectg\ucceditbrushdlg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_UCCEDITBRUSHDLG_H
#define PG_JP983_CLIENT_PROJECTG_UCCEDITBRUSHDLG_H

#include <stddef.h>
#include <stdint.h>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "jp983/client/ProjectG/UccBase.h"
#include "jp983/client/ProjectG/UccLibrary.h"
#include "jp983/client/Wangreal/include/bitmap.h"
#include "jp983/client/Wangreal/include/wtypes.h"
#include "client/FreshNext/include/frform.h"
#include "client/FreshNext/include/frarea.h"

class FrGraphicInterface;
struct sFRESH_ENTRY;
PG_ENUM_FWD(eButton)
PG_ENUM_FWD(eBrushType)

// The brush list of a brush type (KR uccbrush.h CUccBrush): only what this
// unit calls. No jp983 UccBrush.h exists yet.
class CUccBrush {
public:
	Bitmap* GetBrush(int index);               // 0x7df6c0
	void SetBrush(int index, Bitmap* pBrush);  // 0x7df6f0
	void AddBrush(Bitmap* pBrush);             // 0x7dfec0
};

CUccBrush* UccBrushList(eBrushType type);      // 0x7e0200

// The canvas of the brush editor (RTTI CUccEditBrush : CUccBase, vtable
// 0xd29fd4, CUccBase's 18 slots). Size 0x9c as in KR (FrUccEditBrushDlg's
// next member is at 0x148 + 0x9c). The jp983 Bitmap models only its first
// 8 bytes (KR size 0x14): the rest of m_originalBrush is padding.
class CUccEditBrush : public CUccBase {
	LAYOUT_CHECK_FRIEND;
public:
	CUccEditBrush(void);                                             // 0x7e7cd0
	virtual ~CUccEditBrush(void);                                    // slot 0, 0x7e7d60 (??_E 0x7e83d0)

	virtual bool IsInitialized(void) { return m_pTexture != NULL; }  // slot 2, 0x7e7d30
	virtual void Process(void);                                      // slot 5, 0x7e7dc0
	virtual void DrawLine(IPoint from, IPoint to, Bitmap* pBrush);   // slot 9, 0x7e8400

	Bitmap* GetTexture32BPP(void);                                   // 0x7e7de0
	Bitmap* ProduceOriginalBrush(void);                              // 0x7e7e00

protected:
	virtual void Refresh2D(void);                                    // slot 10, 0x7e7d40
	virtual void Refresh3D(void);                                    // slot 11, 0x7e7d50

private:
	Bitmap m_originalBrush;      // 0x88, the 24x24 brush ProduceOriginalBrush returns
};

CHECK_SIZE(CUccEditBrush, 0x9c);
BEGIN_LAYOUT_CHECK(CUccEditBrush)
	CHECK_FIELD(CUccEditBrush, m_originalBrush, 0x88);
END_LAYOUT_CHECK

IObject* FrUccEditBrushDlgMakeInstance(void);   // 0x7e8540

// Brush editor of the UCC editor (RTTI FrUccEditBrushDlg : FrForm; vtables
// 0xd2a034 (38 slots: GetRTTI, the destructor and OnProc at 9 overridden),
// 0xd2a028 (FrCmdTarget: ??_E thunk, GetMessageMap) and 0xd2a020
// (FrModalRenderer)). Size 0x1f0, the `new` of FrUccEditBrushDlgMakeInstance
// (KR 0x1e8); the KR members keep their offsets.
class FrUccEditBrushDlg : public FrForm {
	LAYOUT_CHECK_FRIEND;
public:
	static const WRTTI m_RTTI;                                // 0xe7b9fc
	virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x7e7fb0)

	FrUccEditBrushDlg(void);                                  // 0x7e7ea0
	virtual ~FrUccEditBrushDlg(void);                         // 1 (0x7e7fc0, ??_E 0x7e85d0)

	void InitNew(void);                                       // 0x7e8050
	void InitModify(void);                                    // 0x7e8140
	void SetIndex(eBrushType type, int index);                // 0x7e82e0

private:
	static sFRESH_ENTRY _MsgEntries[];

protected:
	static sFRESH_MSGMAP _MsgMap;                             // 0xe1c0a8
	virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0x7e7e90)

	virtual void OnProc(const float dt);                      // 9 (0x7e8680)
	void OnCanvasInit(intptr_t param);                        // 0x7e8600
	void OnOKBtnUp(void);                                     // 0x7e8320
	void OnCancelBtnUp(void);                                 // 0x7e83a0

private:
	int m_brushIndex;              // 0x110, -2 before SetIndex, -1 for a new brush
	eBrushType m_brushType;        // 0x114
	FrArea* m_pCanvas;             // 0x118
	Bitmap* m_pCanvasImage;        // 0x11c, the background of m_pCanvas
	PADDING(0x120, 0x148);         // Bitmap m_defaultBrush[2] (KR): the jp983 Bitmap lacks its 0x14 layout
	CUccEditBrush m_editBrush;     // 0x148
	PADDING(0x1e4, 0x1f0);
};

CHECK_SIZE(FrUccEditBrushDlg, 0x1f0);
BEGIN_LAYOUT_CHECK(FrUccEditBrushDlg)
	CHECK_FIELD(FrUccEditBrushDlg, m_brushIndex, 0x110);
	CHECK_FIELD(FrUccEditBrushDlg, m_brushType, 0x114);
	CHECK_FIELD(FrUccEditBrushDlg, m_pCanvas, 0x118);
	CHECK_FIELD(FrUccEditBrushDlg, m_pCanvasImage, 0x11c);
	CHECK_FIELD(FrUccEditBrushDlg, m_editBrush, 0x148);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_UCCEDITBRUSHDLG_H
