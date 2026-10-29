// Original: client/ProjectG/NetResourceManager.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_NETRESOURCEMANAGER_H
#define PG_JP983_CLIENT_PROJECTG_NETRESOURCEMANAGER_H

#include "defines.h"

class NetResourceManager;

// WSingleton<NetResourceManager>::m_pInstance of the JP exe (0xe74c78; the
// only caller of DownloadUccClothes, 0x7ebfb0, loads `this` from it).
extern "C" NetResourceManager* data_e74c78;

// The downloader of UCC textures and other server resources (KR
// NetResourceManager : WSingleton<NetResourceManager>). The base and the
// layout are not modelled; only what JP bodies call.
class NetResourceManager {
public:
	static NetResourceManager* Instance(void) { return data_e74c78; }

	void DownloadUccClothes(unsigned long typeId, const char* uccKey, unsigned short slot, bool force);   // 0x9ab5e0
};

#endif // PG_JP983_CLIENT_PROJECTG_NETRESOURCEMANAGER_H
