// Original: d:\build\custom\temp\code\client\projectg\fxsequence.inl (JP 983 exe)
// Inline members of CFxSequence, included at the end of fxsequence.h.

#ifndef PG_JP983_CLIENT_PROJECTG_FXSEQUENCE_INL
#define PG_JP983_CLIENT_PROJECTG_FXSEQUENCE_INL

#include "fxspray.h"

// fxsequence.inl:7
// Turns the sequence on or off and, with bChildren, its sprays. The JP
// callers seen so far pass bChildren false, so the loop is folded away;
// CFxSpray::SetActive is only declared (its JP field is not verified).
inline void CFxSequence::SetActive(bool bActive, bool bChildren) {
	if (m_bActive != bActive) {
		m_bActive = bActive;

		if (bChildren) {
			for (std::map<CFxSpray*, CFxSpray*>::iterator it = m_sprays.begin(); it != m_sprays.end(); ++it) {
				it->second->SetActive(bActive);
			}
		}
	}
}

// fxsequence.inl:26
inline WVector& CFxSequence::Pos(void) {
	return m_pos;
}

// fxsequence.inl:40
inline std::map<CFxSpray*, CFxSpray*>& CFxSequence::GetSprayList(void) {
	return m_sprays;
}

// fxsequence.inl:63
inline void CFxSequence::SetDelay(float delay) {
	m_delay = delay;
}

#endif // PG_JP983_CLIENT_PROJECTG_FXSEQUENCE_INL
