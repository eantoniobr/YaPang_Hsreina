// Original: d:\build\custom\temp\code\client\projectg\ucccolorpicker.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_UCCCOLORPICKER_H
#define PG_JP983_CLIENT_PROJECTG_UCCCOLORPICKER_H

#include <stddef.h>

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/UccBase.h"
#include "jp983/client/Wangreal/include/wtypes.h"

class FrArea;
PG_ENUM_FWD(eButton)

// Colour map of the UCC editor (RTTI .?AVCUccColorPicker@@, vtable 0xd29454,
// 20 slots: CUccBase's 18, then Initialize(FrArea*) and GenerateColorMap).
// Size 0x8c as in KR.
class CUccColorPicker : public CUccBase {
	LAYOUT_CHECK_FRIEND;
public:
	CUccColorPicker(void);                                                           // 0x7e05c0
	virtual ~CUccColorPicker(void);                                                  // 0x7e0650

	virtual bool IsInitialized(void) { return m_pArea != NULL && m_pTexture32 != NULL; }   // slot 2, 0x7e05f0
	virtual void Process(void);                                                      // slot 5, 0x7e0610
	virtual void MouseEventHandler(eButton button, int state, const WPoint &point);  // slot 6, 0x7e0620
	virtual void DestroyVariables(void);                                             // slot 4, 0x7e0520
	virtual void Initialize(FrArea* pArea);                                          // slot 18, 0x7e0540

protected:
	virtual void Refresh2D(void);                                                    // slot 10, 0x7e0630
	virtual void Refresh3D(void);                                                    // slot 11, 0x7e0640
	virtual void GenerateColorMap(void);                                             // slot 19, 0x7e0570

	unsigned char m_red;     // 0x88, the colour last picked
	unsigned char m_green;   // 0x89
	unsigned char m_blue;    // 0x8a
};

CHECK_SIZE(CUccColorPicker, 0x8c);
BEGIN_LAYOUT_CHECK(CUccColorPicker)
	CHECK_FIELD(CUccColorPicker, m_red, 0x88);
	CHECK_FIELD(CUccColorPicker, m_green, 0x89);
	CHECK_FIELD(CUccColorPicker, m_blue, 0x8a);
END_LAYOUT_CHECK

// Brightness bar beside the colour map (RTTI .?AVCUccColorBrightness@@,
// vtable 0xd294ac).
class CUccColorBrightness : public CUccColorPicker {
public:
	CUccColorBrightness(void);                                                       // 0x7e06c0
	virtual ~CUccColorBrightness(void);                                              // 0x7e0710

	virtual bool IsInitialized(void) { return m_pArea != NULL && m_pTexture32 != NULL; }   // slot 2, 0x7e06e0
	virtual void Initialize(FrArea* pArea);                                          // slot 18, 0x7e0720

private:
	virtual void GenerateColorMap(void);                                             // slot 19, 0x7e0700
};

CHECK_SIZE(CUccColorBrightness, 0x8c);

#endif // PG_JP983_CLIENT_PROJECTG_UCCCOLORPICKER_H
