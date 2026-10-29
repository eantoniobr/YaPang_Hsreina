// Original: d:\build\custom\temp\code\client\projectg\fadingtext.cpp (JP 983 exe)
#include "jp983/client/ProjectG/FadingText.h"

#include <string.h>

// 0x7d5540
CFadingText::CFadingText() {
	m_duration = 0;
	m_pWnd = 0;
	m_x = 0;
	m_y = 0;
	m_color = 0xff000000;
	m_type = eFADE_OUT;

	m_active = false;
}

// 0x7d5580
CFadingText::~CFadingText() {
}

// 0x7d5590
void CFadingText::Print(const char* text, float duration, FrWnd* pWnd, float x, float y, eFadeType type,
	unsigned long color) {
	strncpy(m_text, text, sizeof(m_text));

	m_duration = duration;
	m_pWnd = pWnd;
	m_x = x;
	m_y = y;
	m_color = color;
	m_type = type;
	m_elapsed = 0;

	if (type == eFADE_OUT) {
		m_alpha = 0xff;
		m_direction = -1;
	}
	else if (type == eFADE_IN) {
		m_direction = 1;
		m_alpha = 0;
	}
	else if (type == eFADE_IN_OUT) {
		m_alpha = 0;
		m_direction = 2;
	}

	m_active = true;
}
