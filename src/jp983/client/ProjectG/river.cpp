// Original: client/ProjectG/river.cpp (JP 983 exe)
#include "jp983/client/ProjectG/river.h"
#include "wresrcmng.h"

// 0x6fce50
void CRiver::Process(float fDelta)
{
	for (int i = 0; i < 2; i++) {
		if (m_layers[i].enabled) {
			m_layers[i].offset -= fDelta * m_layers[i].speed;
		}
	}
}

// 0x6fce90
void ntRiver_Lava::Process(float fDelta)
{
	for (int i = 0; i < 2; i++) {
		if (m_layers[i].enabled) {
			m_layers[i].offset -= fDelta * m_layers[i].speed;
		}
	}
}

// 0x6fced0
void CRiver_ex::Process(float fDelta)
{
	for (int i = 0; i < 2; i++) {
		if (m_layers[i].enabled) {
			m_layers[i].offset -= fDelta * m_layers[i].speed;
		}
	}
}

// 0x6fe740
CRiver::CRiver(void)
{
	for (int i = 0; i < 2; i++) {
		m_layers[i].offset = 0.0f;
		m_layers[i].speed = 0.0f;
		m_layers[i].texture = 0;
		m_layers[i].tileHead = 0.0f;
		m_layers[i].tileSide = 0.0f;
		m_layers[i].depth = 0.0f;
		m_layers[i].enabled = false;
	}
}

// 0x6fe790
CRiver::~CRiver(void)
{
	for (int i = 0; i < 2; i++) {
		if (data_f023f0 != NULL && m_layers[i].texture != 0) {
			data_f023f0->Release(m_layers[i].texture);
			m_layers[i].texture = 0;
		}
	}
}

// 0x6fe870
ntRiver_Lava::ntRiver_Lava(void)
{
	for (int i = 0; i < 2; i++) {
		m_layers[i].offset = 0.0f;
		m_layers[i].speed = 0.0f;
		m_layers[i].texture = 0;
		m_layers[i].tileHead = 0.0f;
		m_layers[i].tileSide = 0.0f;
		m_layers[i].depth = 0.0f;
		m_layers[i].enabled = false;
	}
}

// 0x6fe8c0
ntRiver_Lava::~ntRiver_Lava(void)
{
	for (int i = 0; i < 2; i++) {
		if (data_f023f0 != NULL && m_layers[i].texture != 0) {
			data_f023f0->Release(m_layers[i].texture);
			m_layers[i].texture = 0;
		}
	}
}

// 0x6fe9a0
CRiver_ex::CRiver_ex(void)
{
	for (int i = 0; i < 2; i++) {
		m_layers[i].offset = 0.0f;
		m_layers[i].speed = 0.0f;
		m_layers[i].texture = 0;
		m_layers[i].tileHead = 0.0f;
		m_layers[i].tileSide = 0.0f;
		m_layers[i].depth = 0.0f;
		m_layers[i].enabled = false;
	}
}

// 0x6fe9f0
CRiver_ex::~CRiver_ex(void)
{
	for (int i = 0; i < 2; i++) {
		if (data_f023f0 != NULL && m_layers[i].texture != 0) {
			data_f023f0->Release(m_layers[i].texture);
			m_layers[i].texture = 0;
		}
	}
}
