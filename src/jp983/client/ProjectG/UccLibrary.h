// Original: d:\build\custom\temp\code\client\projectg\ucclibrary.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_UCCLIBRARY_H
#define PG_JP983_CLIENT_PROJECTG_UCCLIBRARY_H

#include "defines.h"

class Bitmap;
class FrGraphicInterface;
struct sItemInfo;

namespace IFF_STRUCT {
struct sPart;
}

// UCC helpers (KR ucclibrary.h): only what JP bodies call so far.
FrGraphicInterface* GetGDI(void);                                   // 0x7e9040
void RefreshTexCache(Bitmap* bitmap);                               // 0x7e9080
void Convert24to32(Bitmap* src, Bitmap* dest, const Bitmap* mask);  // 0x7e90b0
bool IsSameClothes(unsigned long typeId, unsigned long otherTypeId);                 // 0x7e95d0
bool IsSameClothes(IFF_STRUCT::sPart* pPart, IFF_STRUCT::sPart* pOtherPart);         // 0x7e8830
sItemInfo* GetMyItemInfo(unsigned long serial);                                      // 0x7e9f80
sItemInfo* GetMyItemInfo(unsigned long typeId, const char* uccKey, unsigned short uccDrawCount);   // 0x7ea0b0

// An integer point of the UCC canvas (KR ucclibrary.h IPoint). KR's
// constructors and operator== are not modelled until a JP body needs them.
struct IPoint {
	int x;   // 0x0
	int y;   // 0x4
};

CHECK_SIZE(IPoint, 0x8);

#endif // PG_JP983_CLIENT_PROJECTG_UCCLIBRARY_H
