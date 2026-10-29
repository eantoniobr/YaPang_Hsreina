// Original: d:\build\custom\temp\code\client\projectg\sky.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_SKY_H
#define PG_JP983_CLIENT_PROJECTG_SKY_H

#include "defines.h"
#include "padding.h"
#include "wvideo.h"

class WView;

// The sky dome, clouds, stars, moons and lens flare of a course (KR
// sky.h). Only the members the JP unit's bodies need are declared, at their
// JP offsets (m_batch at 0x40, KR 0x3c; m_cloudTex at 0x1c8, KR 0x1b8).
class CSky {
	LAYOUT_CHECK_FRIEND;
public:
	~CSky(void);
	void Clear(void);
	void ClearClouds(void);
	void RegisterCloud(char* name);
	void UpdateBright(void);

private:
	void SetSkyTex(int texhandle, unsigned char layer, unsigned char batch);
	float CalcScaleByView(WView* view) const;
	float CalcClipFarByView(WView* view) const;

	PADDING(0x0, 0x40);
	WxBatchState m_batch[4];  // 0x40: far, near, up, down
	PADDING(0x1C0, 0x1C8);
	int m_cloudTex;           // 0x1c8
};
BEGIN_LAYOUT_CHECK(CSky)
	CHECK_FIELD(CSky, m_batch, 0x40);
	CHECK_FIELD(CSky, m_cloudTex, 0x1C8);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_SKY_H
