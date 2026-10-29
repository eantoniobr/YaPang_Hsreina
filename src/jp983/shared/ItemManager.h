// Original: shared/ItemManager.h (JP 983 exe)
#ifndef PG_JP983_SHARED_ITEMMANAGER_H
#define PG_JP983_SHARED_ITEMMANAGER_H

#include "defines.h"
#include "padding.h"

namespace IFF_STRUCT {
struct sPart;
}

// The item table manager (KR shared/ItemManager.h CItemManager), a member of
// CSharedDoc at 0x20c (ItemManager()). Only what JP bodies call. Its finders
// (0xa17120-0xa17be0) each search a std::map (VS 2010, 0x10 bytes, the head
// node at +4) and return &it->second: FindPart's map<unsigned long, sPart> is
// at 0x30 (head 0x34). The maps are not modelled; the last finder's map ends
// at 0x534, a lower bound of the size, which is not known.
class CItemManager {
public:
	IFF_STRUCT::sPart* FindPart(unsigned long typeId);   // 0xa17160

private:
	UNKNOWN(0x000, 0x534);
};

#endif // PG_JP983_SHARED_ITEMMANAGER_H
