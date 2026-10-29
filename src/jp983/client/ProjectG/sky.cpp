// Original: client/ProjectG/sky.cpp (JP 983 exe)
#include "jp983/client/ProjectG/sky.h"
#include "wresrcmng.h"
#include "wview.h"

// The batch flags of a sky texture: the handle in the low 11 bits, then the
// render flags of the sky layers (their Wangreal names are not known).
#define SKY_TEX_FLAG(tex) (((tex) & 0x7FF) | 0x22300000)

// 0x704c80
void CSky::SetSkyTex(int texhandle, unsigned char layer, unsigned char batch)
{
	if (texhandle) {
		m_batch[batch].xiFlag0 = SKY_TEX_FLAG(texhandle);
	} else {
		m_batch[batch].xiFlag0 = 0;
	}
}

// 0x704d80
void CSky::RegisterCloud(char* name)
{
	ClearClouds();
	m_cloudTex = data_f023f0->LoadTexture(name, 0, 0, 0);
}

// 0x704f10
void CSky::UpdateBright(void)
{
}

// Small accessors the split places between CSky::ClearSky and CSky::Clear.
// Nothing in the readable code of the exe calls or references them (no
// call, no vtable slot, no function pointer): inline accessors left
// out-of-line by the compiler. Neither their class nor their name is known,
// so they are kept as free functions with the address in the name, over
// stand-in types holding only the field each one reads. 0x704f80, between
// them, is WView::GetScale (wview.h), emitted with this unit.

struct UnknownWithByteAt1a12 {
	PADDING(0x0, 0x1A12);
	unsigned char m_value;  // 0x1a12
};

struct UnknownWithIntAtdc {
	PADDING(0x0, 0xDC);
	int m_value;  // 0xdc
};

// 0x704f90
unsigned char UnreferencedGetByte_00704f90(const UnknownWithByteAt1a12* object)
{
	return object->m_value;
}

// 0x704fa0
int UnreferencedGetInt_00704fa0(const UnknownWithIntAtdc* object)
{
	return object->m_value;
}

// 0x704fb0
const UnknownWithIntAtdc* UnreferencedReturnSelf_00704fb0(const UnknownWithIntAtdc* object)
{
	return object;
}

// 0x7052d0
float CSky::CalcScaleByView(WView* view) const
{
	if (view->GetProjectionMode() == WView::PARALLEL) {
		return view->GetScale() * 2.0f / 1000.0;
	}
	return 1.0f;
}

// 0x705300
float CSky::CalcClipFarByView(WView* view) const
{
	if (view->GetProjectionMode() == WView::PARALLEL) {
		return CalcScaleByView(view) * 1000.0;
	}
	return view->GetClipFarValue();
}

// 0x705450
CSky::~CSky(void)
{
	Clear();
}
