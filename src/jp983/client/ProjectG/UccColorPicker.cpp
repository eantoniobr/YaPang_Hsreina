// Original: d:\build\custom\temp\code\client\projectg\ucccolorpicker.cpp (JP 983 exe)
#include "jp983/client/ProjectG/UccColorPicker.h"

// 0x7e0520
void CUccColorPicker::DestroyVariables(void) {
	m_red = 0;
	m_green = 0;
	m_blue = 0;
}

// 0x7e0540
void CUccColorPicker::Initialize(FrArea* pArea) {
	CUccBase::Initialize(pArea, NULL, NULL);

	GenerateColorMap();
}

// 0x7e05c0
CUccColorPicker::CUccColorPicker(void) {
	// Cleared through references, red alone and then green and blue together:
	// the original's byte store at 0x88 followed by one word store at 0x89.
	unsigned char& red = m_red;
	unsigned char& green = m_green;
	unsigned char& blue = m_blue;
	red = 0;
	green = blue = 0;
}

// 0x7e0610
void CUccColorPicker::Process(void) {
}

// 0x7e0620
void CUccColorPicker::MouseEventHandler(eButton button, int state, const WPoint &point) {
}

// 0x7e0630
void CUccColorPicker::Refresh2D(void) {
}

// 0x7e0640
void CUccColorPicker::Refresh3D(void) {
}

// 0x7e0650
CUccColorPicker::~CUccColorPicker(void) {
	CUccColorPicker::DestroyVariables();
}

// 0x7e06c0
CUccColorBrightness::CUccColorBrightness(void) {
}

// 0x7e0700
void CUccColorBrightness::GenerateColorMap(void) {
}

// 0x7e0710
CUccColorBrightness::~CUccColorBrightness(void) {
}
