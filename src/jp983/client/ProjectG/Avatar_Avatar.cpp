// Original: client/ProjectG/Avatar_Avatar.cpp (JP 983 exe)
#include "jp983/client/ProjectG/avatar_avatar.h"

#include <string.h>

// 0x7a3230
ntAvatar *ntAvatarManager::FindAvatarByIDName(const char *idName) const {
	for (int i = 0; i < 30; i++) {
		if (m_avatars[i]) {
			if (strcmp(m_avatars[i]->m_idName, idName) == 0) {
				return m_avatars[i];
			}
		}
	}

	return NULL;
}

// 0x7a32a0
ntAvatar *ntAvatarManager::FindAvatarByNickName(const char *nickName) const {
	for (int i = 0; i < 30; i++) {
		if (m_avatars[i]) {
			if (strcmp(m_avatars[i]->m_nickName, nickName) == 0) {
				return m_avatars[i];
			}
		}
	}

	return NULL;
}

// 0x7a3310
ntAvatar *ntAvatarManager::FindAvatarByGuid(int guid) const {
	for (int i = 0; i < 30; i++) {
		if (m_avatars[i]) {
			if (m_avatars[i]->m_guid == guid) {
				return m_avatars[i];
			}
		}
	}

	return NULL;
}

// 0x7a3350
bool ntAvatarManager::DeleteAvatar(const char *idName) {
	int i;
	for (i = 0; i < 30; i++) {
		if (m_avatars[i]) {
			if (strcmp(m_avatars[i]->m_idName, idName) == 0) {
				break;
			}
		}
	}

	if (i == 30) {
		return false;
	}

	if (m_avatars[i]) {
		delete m_avatars[i];
		m_avatars[i] = NULL;
	}
	m_avatarCount--;

	return true;
}

// 0x7a33e0
CQuadTree &ntAvatarManager::GetPVS() {
	return *m_pPVS;
}

// 0x7a33f0
void ntAvatarManager::SetLocalPVS(CQuadTree &pvs) {
	m_pPVS = &pvs;
}

// 0x7a3400
ntAvatarBurden::~ntAvatarBurden() {
}

// 0x7a3a40
ntAvatar *ntAvatar::GetFollowingAvatar() const {
	if (m_followName[0] != '\0') {
		return NULL;
	}

	return data_e73e10->FindAvatarByNickName(m_followName);
}

// 0x7a3b00
void ntAvatar::SetTargetPosition(const WVector &position) {
	m_targetPosition = position;
	m_targetPositionChanged = true;
}

// 0x7a4360
ntAvatar *ntAvatarManager::CheckClick(float x, float y) const {
	for (int i = 0; i < 30; i++) {
		if (m_avatars[i] && m_avatars[i]->IsClickable(x, y)) {
			return m_avatars[i];
		}
	}

	return NULL;
}

// 0x7a4760 (no reference in the JP exe)
unsigned long ntAvatar::GetValueC80(void) const {
	return m_valueC80;
}

// 0x7a47f0
void ntAvatar::SetPosition(const WVector &position) {
	m_position = position;
	SetTargetPosition(position);
}

// 0x7a6080
void ntAvatarManager::Render() {
	if (!m_active) {
		return;
	}

	for (int i = 0; i < 30; i++) {
		if (m_avatars[i]) {
			m_avatars[i]->Render();
		}
	}
}

// 0x7a87f0
void ntAvatarManager::Process(float elapsed) {
	for (int i = 0; i < 30; i++) {
		if (m_avatars[i]) {
			m_avatars[i]->Process(elapsed);
		}
	}
}
