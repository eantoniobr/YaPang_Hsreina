// Original: d:\build\custom\temp\code\client\projectg\g_starmode.cpp
#include "NetworkSystem.h"
#include "G_StarMode.h"

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "TaskManager.h"
#include "Packet.h"
#include "actor.h"
#include "SharedDoc.h"
#include "parttidlist.h"
#include "FamilyMain.h"
#include "mousecursor.h"
#include <fstream>
#include "commonutil.h"

// The project's SDK has no <wininet.h>; the function and the two flags used
// here are declared locally.
extern "C" __declspec(dllimport) BOOL __stdcall InternetGetConnectedState(LPDWORD lpdwFlags, DWORD dwReserved);
#define INTERNET_CONNECTION_LAN 0x02
#define INTERNET_CONNECTION_CONFIGURED 0x40

// The first line of a character settings file, and the line written in its
// place when saving fails (adjacent .rdata at 0xA2980C and 0xA2982C, not
// pooled literals).
static const char s_settingsHeader[] = "SINGLE_PLAY_CHARACTER_SETTINGS\n";
static const char s_errorHeader[] = "ERROR!\n";

// g_starmode.cpp:39
CGStarMode::CGStarMode(void) {
	memset(m_parts, 0, sizeof(m_parts));

	m_pSecondBuffer = NULL;
	m_pFirstBuffer = NULL;
}

// g_starmode.cpp:47
CGStarMode::~CGStarMode(void) {
	if (m_pSecondBuffer) { delete[] m_pSecondBuffer; m_pSecondBuffer = NULL; }
	if (m_pFirstBuffer) { delete[] m_pFirstBuffer; m_pFirstBuffer = NULL; }
}

// g_starmode.cpp:53
void CGStarMode::GStarModeInit(void) {
	SetPlayerData();

	for (int i = 0; i < 4; i++) {
		memset(&WSingleton<CSharedDoc>::Instance()->m_roomPlayers[i], 0, sizeof(sUserInfo));

		if (i < 2) {
			sprintf(WSingleton<CSharedDoc>::Instance()->m_roomPlayers[i].m_name, "PLAYER%d", i + 1);
		}
		else {
			WSingleton<CSharedDoc>::Instance()->m_roomPlayers[i].m_nickname[0] = 0;
			WSingleton<CSharedDoc>::Instance()->m_roomPlayers[i].m_name[0] = 0;
		}

		WSingleton<CSharedDoc>::Instance()->m_roomPlayers[i].m_level = WSingleton<CSharedDoc>::Instance()->m_myLevel;
		WSingleton<CSharedDoc>::Instance()->m_roomPlayers[i].m_mascotId = WSingleton<CSharedDoc>::Instance()->m_myMascotId;
		memset(CFamilyMain::ms_itemslotBackup[i], 0, sizeof(CFamilyMain::ms_itemslotBackup[i]));
	}

	WSingleton<CSharedDoc>::Instance()->m_shotTimeLimit = 0;
	SetCurMap(0);
	WSingleton<CSharedDoc>::Instance()->m_roomType = 0; strcpy(WSingleton<CSharedDoc>::Instance()->m_roomName, WSingleton<CSharedDoc>::Instance()->m_gameTypeNames[0].name);
	WSingleton<CSharedDoc>::Instance()->m_holes = 3;
	WSingleton<CSharedDoc>::Instance()->m_gameKind = 0;
	WSingleton<CSharedDoc>::Instance()->m_gameOver = false;
	WSingleton<CMouseCursor>::Instance()->SetActive(false);

	CTaskManager::Instance()->ChangeTask("CFamilyTask", "", false);
	CTaskManager::Instance()->PostMsg(NULL, "Family", 0, (intptr_t)"FAMILY", 1, 0, 0);
}

// g_starmode.cpp:92
void CGStarMode::SetPlayerData(void) {
	CPartTidList partTidList;
	char path[MAX_PATH]; // unused: the /GS cookie of the original comes from a char buffer left over from the compiled-out body

	// The rest of the original body (lines 100-156) was compiled out; only the clears remain.
	WSingleton<CSharedDoc>::Instance()->m_myGearList.clear();
	WSingleton<CSharedDoc>::Instance()->m_characterMap.clear();
	WSingleton<CSharedDoc>::Instance()->m_caddieMap.clear();
}

// g_starmode.cpp:183
void CGStarMode::GetAllItemFromItemManager(void) {
}

// g_starmode.cpp:344
void ErrorMessageToMyRoom(void *param) {
	CTaskManager::Instance()->PostMsg(NULL, "RealMyRoom", 0x23, (intptr_t)param, 0, 0, 0);
}

// g_starmode.cpp:352
bool CGStarMode::SavePartsInfoCharacterMap(const std::map<unsigned int, sCharacterInfo> &characters, const char *fileName) {
	std::fstream file(fileName, std::ios::out | std::ios::trunc);
	if (file.is_open()) {
		file << s_settingsHeader;
		file.close();
	}

	for (std::map<unsigned int, sCharacterInfo>::const_iterator it = characters.begin(); it != characters.end(); ++it) {
		if (!SavePartsInfoCharacter(it->second, fileName, false, ErrorMessageToMyRoom)) {
			std::fstream errorFile(fileName, std::ios::out | std::ios::trunc);
			if (errorFile.is_open()) {
				errorFile << s_errorHeader;
				errorFile.close();
			}
			return false;
		}
	}

	return true;
}

// g_starmode.cpp:380
bool CGStarMode::SavePartsInfoCharacter(const sCharacterInfo &character, const char *fileName, bool truncate, void (*onError)(void *)) {
	std::ios::openmode mode = std::ios::app;
	if (truncate) {
		mode = std::ios::trunc;
	}

	std::fstream file(fileName, mode | std::ios::out);
	if (!file.is_open()) {
		return false;
	}

	// One line per character: "<type id>|<part>...|<part>#<name>\n", each
	// worn part as its five decimal digits (a 0 for an empty slot).
	char line[101];
	IFF_STRUCT::sChar *charData = ItemManager()->FindChar(character.typeId);
	bool saved = true;
	if (charData) {
		if (_snprintf(line, 100, "%d", character.typeId & 0x3FFFFFF) < 0) {
			line[100] = 0;
		}
		int length = (int)strlen(line);

		for (int i = 0; i < 10; i++) {
			unsigned long part = character.partTypeIds[i];
			if (part) {
				if (((part >> 18) & 0xFF) > 9 || ((part >> 13) & 0x1F) > 9 || ((part >> 11) & 3) > 9
					|| ((part >> 9) & 3) > 9 || (part & 0x1FF) > 9) {
					saved = false;
					const char *partName = NULL;
					IFF_STRUCT::sPart *partData = ItemManager()->FindPart(character.partTypeIds[i]);
					if (partData) {
						partName = partData->m_name;
					}
					if (onError) {
						// "Cannot save the following.\n[ %s: %s ]\n"
						onError(MakeStr("\xb4\xd9\xc0\xbd\xc0\xbb \xc0\xfa\xc0\xe5\xc7\xd2 \xbc\xf6 \xbe\xf8\xbd\xc0\xb4\xcf\xb4\xd9.\n[ %s: %s ]\n", charData->m_name, partName));
					}
					break;
				}
				if (_snprintf(line + length, 100 - length, "|%d%d%d%d%d", (part >> 18) & 0xFF, (part >> 13) & 0x1F, (part >> 11) & 3, (part >> 9) & 3, part & 0x1FF) < 0) {
					line[100] = 0;
				}
			}
			else {
				if (_snprintf(line + length, 100 - length, "|%d", 0) < 0) {
					line[100] = 0;
				}
			}
			length = (int)strlen(line);
		}

		if (_snprintf(line + length, 100 - length, "#%s\n", charData->m_name) < 0) {
			line[100] = 0;
		}
		if (saved) {
			file << line;
		}
	}

	file.close();
	return saved;
}

// g_starmode.cpp:516
bool CGStarMode::LoadFile(const char *fileName) {
	bool loaded = false;
	char line[0x2800] = "";
	char delims[] = "\t\r\n|";

	FILE *fp = fopen(fileName, "rt");
	if (fp != NULL) {
		if (fgets(line, sizeof(line), fp) != NULL) {
			if (strcmp(line, s_errorHeader) != 0) {
				if (strcmp(line, s_settingsHeader) == 0) {
					while (fgets(line, sizeof(line), fp) != NULL) {
						char *token = strtok(line, delims);
						if (token == NULL)
							goto close; // a short line: the file stays not loaded
						int entry = atoi(token);

						for (int part = 0; part < 10; part++) {
							token = strtok(NULL, delims);
							if (token == NULL)
								goto close;
							Parse(entry, part, token);
						}
					}
					loaded = true;
				}
			}
		}
close:
		fclose(fp);
	}
	return loaded;
}

// g_starmode.cpp:573
void CGStarMode::Parse(int entry, int part, char *text) {
	if (atoi(text) == 0) {
		m_parts[entry][part] = 0;
		return;
	}

	unsigned char digits[5];
	char digit[12];
	for (int i = 0; i < 5; i++) {
		lstrcpynA(digit, text + i, 2);
		digits[i] = (unsigned char)atoi(digit);
	}

	m_parts[entry][part] = 0x08000000 | (digits[0] << 18) | (digits[1] << 13) | (digits[2] << 11) | (digits[3] << 9) | digits[4];
}

// g_starmode.cpp:591
void CGStarMode::SetParts(int entry, unsigned long *parts) {
	unsigned long sum = 0;
	for (int i = 0; i < STARMODE_PART_COUNT; i++) {
		sum += m_parts[entry][i];
	}

	if (sum != 0) {
		memcpy(parts, m_parts[entry], sizeof(m_parts[entry]));
	}
}

// g_starmode.cpp:604
void CGStarMode::SkipServer(void) {
	WNetworkSystem *pNetwork = WNetworkSystem::Instance();

	if (pNetwork->IsConnected(WNetworkSystem::NET_UNIT_DEFAULT)) {
		pNetwork->ForceShutDown(WNetworkSystem::NET_UNIT_DEFAULT);
	}
}

// g_starmode.cpp:630
void CGStarMode::Skip30vs(void) {
	WSendPacket packet(GCT_ENTER_CHANNEL);
	packet.Encode1(8);
	packet.Send(SEND_TO_DEFAULT);

	AfxGetTask()->GetActor("Lobby") << MsgObject(0, 1, 0, 0, 0, 0, 0);
}

// g_starmode.cpp:643
bool CGStarMode::IsInternetConnect(void) {
	DWORD flags;

	if (InternetGetConnectedState(&flags, 0)) {
		if (flags & INTERNET_CONNECTION_CONFIGURED)
			return true;
		else if (flags & INTERNET_CONNECTION_LAN)
			return true;
		else
			return false;
	}
	return false;
}
