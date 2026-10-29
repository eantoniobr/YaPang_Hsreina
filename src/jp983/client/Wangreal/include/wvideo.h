// Original: d:\build\custom\temp\code\client\wangreal\include\wvideo.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_WANGREAL_INCLUDE_WVIDEO_H
#define PG_JP983_CLIENT_WANGREAL_INCLUDE_WVIDEO_H

#include "defines.h"
#include "padding.h"

// The render state of one batch (KR wvideo.h). JP: 0x60 bytes (KR 0x5c);
// only the members the JP units read are declared.
struct WxBatchState {
	int xiFlag0;  // 0x0
	int xiFlag1;  // 0x4
	PADDING(0x8, 0x60);
};
CHECK_SIZE(WxBatchState, 0x60);
CHECK_FIELD(WxBatchState, xiFlag0, 0x0);
CHECK_FIELD(WxBatchState, xiFlag1, 0x4);

// A transformed, lit vertex (KR wvideo.h WTVertex, 0x28 bytes). JP: 0x58
// bytes (CBallTrace's constructor 0x79d170 places four of them 0x58 apart;
// CComet's constructor 0x79f590 writes diffuse at 0x10). Only the members
// the JP units use are declared.
struct WTVertex {
	float x, y, z;              // 0x0
	float rhw;                  // 0xc
	unsigned long diffuse;      // 0x10
	PADDING(0x14, 0x58);
};
CHECK_SIZE(WTVertex, 0x58);
CHECK_FIELD(WTVertex, diffuse, 0x10);

#endif // PG_JP983_CLIENT_WANGREAL_INCLUDE_WVIDEO_H
