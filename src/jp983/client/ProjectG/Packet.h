// Original: client/ProjectG/packet.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_PACKET_H
#define PG_JP983_CLIENT_PROJECTG_PACKET_H

#include <string>

#include "defines.h"

#include "jp983/shared/packet.h"

// Destination of WSendPacket::Send (KR names); only SEND_TO_DEFAULT is
// verified in JP (Avatar_Avatar 0x7a41d6 pushes 0).
enum eSendTo {
    SEND_TO_DEFAULT = 0     // TO_GAME (GameUnit)
};

// The outgoing packet, as far as the JP bodies use it (0xc bytes on the JP
// stack). The two fields are KR WMemBlock's first two, unverified in JP;
// they are not char padding because a char array would make /GS guard
// every frame holding a packet, which the original does not.
class WSendPacket
{
public:
    WSendPacket(enumClientPacket type);                       // 0xa4e800
    virtual ~WSendPacket(void);                               // 0xa4e590

    // The encoders forward to the WSendPacketImpl at +4 (JP RTTI class
    // _private::WSendPacketImpl); the argument sizes are the impl's.
    void Send(eSendTo to);                                    // 0xa4dab0
    void Encode1(unsigned char value);                        // 0xa4dd50 (impl 0x5ab3f0)
    void Encode2(unsigned short value);                       // 0xa4dd60 (impl 0x5ab420)
    void Encode4(unsigned long value);                        // 0xa4dd70 (impl 0x5ab450, 4x Encode1)
    void Encode8(__int64 value);                              // 0xa4dd80 (impl 0x5ab490)
    void EncodeStr(const std::string& value);                 // 0xa4dda0 (impl 0x5ab950, Encode2 length + bytes)
    void EncodeBuffer(const void* data, unsigned short length); // 0xa4ddc0 (impl 0x5ab540)

private:
    unsigned char* m_buffer;                                  // 0x04
    unsigned int m_bufferSize;                                // 0x08
};

CHECK_SIZE(WSendPacket, 0xc);

// The incoming packet, opaque: the JP bodies take it by reference and call
// its decoders, which forward to the _private::WReceivedPacketImpl at +4
// (read position at impl+0xc). Layout not modelled.
class WReceivedPacket
{
public:
    unsigned char Decode1(void);                              // 0xa4deb0 (impl 0x5ab140)
    unsigned short Decode2(void);                             // 0xa4dec0 (impl 0x5ab150)
    unsigned long Decode4(void);                              // 0xa4ded0 (impl 0x5ab180, 2x Decode2)
    __int64 Decode8(void);                                    // 0xa4dee0 (impl 0x5ab1a0, 2x Decode4)
    bool DecodeStr(std::string& value);                       // 0xa4def0 (impl 0x5abce0)
    void DecodeBuffer(void* data, int length);                // 0xa4df00 (impl 0x5ab1c0, memcpy)
    std::string DecodeStr(void);                              // 0xa4e1f0 (impl 0x5abbc0)
};

#endif // PG_JP983_CLIENT_PROJECTG_PACKET_H
