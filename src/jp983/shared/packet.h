// Original: shared/packet.h (JP 983 exe)
#ifndef PG_JP983_SHARED_PACKET_H
#define PG_JP983_SHARED_PACKET_H

// Packet identifiers (KR shared/packet.h names). Only the values a JP call
// site verifies are listed; JP values differ from KR's.
enum enumClientPacket {
    GCT_USE_SP_ITEM = 0xC,            // Avatar_Avatar 0x7a4195 (push 0Ch to WSendPacket)
    GCT_UCC_INFO_REQUEST = 0xB9,      // UccManager 0x7ee544 (KR 0xB1)
    GCT_USE_CARD_REMOVE_REQ = 0xE0    // CardRemove 0x7fe551 (KR 0xE2)
};

#endif // PG_JP983_SHARED_PACKET_H
