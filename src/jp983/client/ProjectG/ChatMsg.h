// Original: d:\build\custom\temp\code\client\projectg\chatmsg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_CHATMSG_H
#define PG_JP983_CLIENT_PROJECTG_CHATMSG_H

#include <string>

#include "defines.h"

class CChatMsg;

// WSingleton<CChatMsg>::m_pInstance of the JP exe (0xe73e8c), unnamed there.
extern "C" CChatMsg *data_e73e8c;

// The chat window singleton (KR CChatMsg : WSingleton<CChatMsg>). The base
// and the layout are not modelled; only the members the JP units call are
// declared.
class CChatMsg {
public:
    // KR WSingleton<CChatMsg>::Instance(): the JP callers load the instance
    // pointer straight from 0xe73e8c (`mov ecx,ds:[0E73E8Ch]`).
    static CChatMsg *Instance(void) { return data_e73e8c; }

    // KR names (alwaysShow, removeColor); CGolfRule::AddExtPrize 0x6846ca
    // pushes 0, 0, 0xFFFF7878 and a std::string.
    void AddChatMsg(const std::string& msg, unsigned long color, bool alwaysShow, bool removeColor); // 0x9a1600
};

#endif // PG_JP983_CLIENT_PROJECTG_CHATMSG_H
