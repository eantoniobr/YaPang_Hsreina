// Original: d:\build\custom\temp\code\client\wangreal\include\wresrcmng.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_WANGREAL_INCLUDE_WRESRCMNG_H
#define PG_JP983_CLIENT_WANGREAL_INCLUDE_WRESRCMNG_H

// windows.h renames LoadBitmap to LoadBitmapA, as the JP exe's name
// (?LoadBitmapA@WResourceManager@@...) shows: included here so every
// includer declares the same name.
#include <windows.h>

class Bitmap;
class WPuppet;
class WResource;
class WTitleFont;

// The texture, mesh and sound resource manager (KR wresrcmng.h). Only the
// members the JP units call are declared, KR signatures at the JP addresses
// (ret sizes checked: GetPuppet `ret 10h`, Release(WPuppet*, bool) `ret 8`,
// LoadBitmap `ret 0Ch`).
class WResourceManager {
public:
	WTitleFont* GetTitleFont(void);                                       // 0xb55c10
	WPuppet* GetPuppet(const char* name, bool a, bool b, bool c);         // 0xb5b350

	void Release(WTitleFont* font);                                       // 0xb55c80
	void Release(int texhandle);                                          // 0xb5a790
	void Release(WPuppet* puppet, bool a);                                // 0xb5b680
	void Release(WResource* resource);                                    // 0xb55a50

	int LoadTexture(const char* filename, unsigned long type, int level, const char* texname);
	Bitmap* LoadBitmap(const char* filename, int a, bool b);              // 0xb5cea0 (LoadBitmapA)
};

// KR g_resrcmng; the JP exe has no symbol for it (0xf023f0).
extern "C" WResourceManager* data_f023f0;

#endif // PG_JP983_CLIENT_WANGREAL_INCLUDE_WRESRCMNG_H
