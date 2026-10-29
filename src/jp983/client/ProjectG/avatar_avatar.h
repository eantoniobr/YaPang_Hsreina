// Original: client/ProjectG/avatar_avatar.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_AVATAR_AVATAR_H
#define PG_JP983_CLIENT_PROJECTG_AVATAR_AVATAR_H

#include "defines.h"
#include "padding.h"
#include "wmath.h"

// JP 983 layouts, known only as far as the bodies of this unit read them.

class CQuadTree;

// KR 0x294 bytes; in JP m_charInfo (0x201 bytes copied) is at 0x8, the part
// list at 0x20C and the pet frame at 0x2D4 (the constructors at 0x7a37a0 and
// 0x7a4710).
class ntAvatarBurden {
public:
	~ntAvatarBurden();

	unsigned long m_first;      // 0x0
	unsigned long m_key;        // 0x4
	UNKNOWN(0x8, 0x2D4);        // sCharacterInfo at 0x8, CPartTidList at 0x20C
	void *m_pPetFrame;          // 0x2D4, CPetFrame *
};
CHECK_FIELD(ntAvatarBurden, m_pPetFrame, 0x2D4);

// The JP avatar has 0x68 more bytes than KR's before m_position (KR 0xFC).
class ntAvatar {
	LAYOUT_CHECK_FRIEND;
	friend class ntAvatarManager;

public:
	// The JP vtable (0xd25874, RTTI ntAvatar : AvatarBase : CPetFrame::HierarchyChangeObserver)
	// has two slots: 0x47f130 (the observer's, takes one pointer) and the scalar
	// deleting destructor (0x7a77a0). The bases are not modelled yet.
	virtual void OnHierarchyChange(void *pFrame);
	virtual ~ntAvatar();
	bool IsClickable(float x, float y) const;
	ntAvatar *GetFollowingAvatar() const;
	void SetPosition(const WVector &position);
	void SetTargetPosition(const WVector &position);
	unsigned long GetValueC80(void) const;
	void Render();
	void Process(float elapsed);

private:
	UNKNOWN(0x4, 0x6C);
	char m_idName[0x16];                // 0x6C (KR 0x4)
	char m_nickName[0x16];              // 0x82 (KR 0x1A)
	UNKNOWN(0x98, 0xAE);
	char m_followName[0x16];            // 0xAE (KR 0x46), nickname of the avatar followed
	UNKNOWN(0xC4, 0x14C);
	int m_guid;                         // 0x14C (KR 0xE4)
	UNKNOWN(0x150, 0x164);
	WVector m_position;                 // 0x164 (KR 0xFC)
	UNKNOWN(0x170, 0x18C);
	WVector m_targetPosition;           // 0x18C (KR 0x124)
	bool m_targetPositionChanged;       // 0x198 (KR 0x130)
	UNKNOWN(0x199, 0xC44);
	char m_spItems[5][0xC];             // 0xC44, SpecialPrizeItem[5] (GetMySpItem, 0x7a31f0)
	unsigned long m_valueC80;           // 0xC80, JP-only, read by an unreferenced getter (0x7a4760)
};
BEGIN_LAYOUT_CHECK(ntAvatar)
	CHECK_FIELD(ntAvatar, m_idName, 0x6C);
	CHECK_FIELD(ntAvatar, m_nickName, 0x82);
	CHECK_FIELD(ntAvatar, m_followName, 0xAE);
	CHECK_FIELD(ntAvatar, m_guid, 0x14C);
	CHECK_FIELD(ntAvatar, m_position, 0x164);
	CHECK_FIELD(ntAvatar, m_targetPosition, 0x18C);
	CHECK_FIELD(ntAvatar, m_targetPositionChanged, 0x198);
	CHECK_FIELD(ntAvatar, m_spItems, 0xC44);
	CHECK_FIELD(ntAvatar, m_valueC80, 0xC80);
END_LAYOUT_CHECK

// Only the members this unit's bodies use. The WSingleton<ntAvatarManager>
// base (BaseObject, 0x28 bytes) is not modelled yet: no jp983 singleton.h.
class ntAvatarManager {
	LAYOUT_CHECK_FRIEND;

public:
	ntAvatar *FindAvatarByIDName(const char *idName) const;
	ntAvatar *FindAvatarByNickName(const char *nickName) const;
	ntAvatar *FindAvatarByGuid(int guid) const;
	ntAvatar *CheckClick(float x, float y) const;
	bool DeleteAvatar(const char *idName);
	void Render();
	void Process(float elapsed);

protected:
	CQuadTree &GetPVS();
	void SetLocalPVS(CQuadTree &pvs);

private:
	UNKNOWN(0x0, 0x28);            // WSingleton<ntAvatarManager>
	int m_avatarCount;             // 0x28
	ntAvatar *m_avatars[30];       // 0x2C
	UNKNOWN(0xA4, 0xB0);
	bool m_active;                 // 0xB0
	UNKNOWN(0xB1, 0xB4);
	CQuadTree *m_pPVS;             // 0xB4
};
BEGIN_LAYOUT_CHECK(ntAvatarManager)
	CHECK_FIELD(ntAvatarManager, m_avatarCount, 0x28);
	CHECK_FIELD(ntAvatarManager, m_avatars, 0x2C);
	CHECK_FIELD(ntAvatarManager, m_active, 0xB0);
	CHECK_FIELD(ntAvatarManager, m_pPVS, 0xB4);
END_LAYOUT_CHECK

// WSingleton<ntAvatarManager>::m_pInstance (0xe73e10), unnamed in the JP
// exe; replace with the template's static once a jp983 singleton.h exists.
extern "C" ntAvatarManager *data_e73e10;

#endif // PG_JP983_CLIENT_PROJECTG_AVATAR_AVATAR_H
