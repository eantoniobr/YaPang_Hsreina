// Original: d:\build\custom\temp\code\client\wangreal\include\bitmap.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_WANGREAL_INCLUDE_BITMAP_H
#define PG_JP983_CLIENT_WANGREAL_INCLUDE_BITMAP_H

#include <windows.h>

#include "defines.h"

// A DIB in system memory (KR bitmap.h, size 0x14). JP-verified layout: the
// constructors 0xbb82d0 / 0xbb8b40 store the vtable 0xd56348 and clear bi
// (0x4), vram (0xc) and m_lock (0x10); Create 0xbb87e0 sets pitch (0x8).
// Vtable: [0] the destructor 0xbb8300, [1] Update 0xbb82f0 (`ret`).
class Bitmap {
	LAYOUT_CHECK_FRIEND;
public:
	Bitmap(void);                                                                // 0xbb82d0
	Bitmap(int width, int height, int bpp);                                      // 0xbb8b40
	virtual ~Bitmap(void);                                                       // 0 (0xbb8300)
	virtual void Update(void) {}                                                 // 1 (0xbb82f0)

	Bitmap& operator=(Bitmap& src);                                              // 0xbb8b80
	void Create(int width, int height, int bpp);                                 // 0xbb87e0
	void GetPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a) const;   // 0xbb8320
	void GetPixel(int x, int y, unsigned char& r, unsigned char& g, unsigned char& b) const;                     // 0xbb83d0
	void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);             // 0xbb84e0
	unsigned char* GetVram(int y) { return vram + pitch * y; }
	unsigned int Width(void) const { return bi->bmiHeader.biWidth; }
	unsigned int Height(void) const { return bi->bmiHeader.biHeight; }
	unsigned int BitsPerPixel(void) const { return bi->bmiHeader.biBitCount; }

	tagBITMAPINFO* bi;       // 0x4
	int pitch;               // 0x8
	unsigned char* vram;     // 0xc

private:
	bool m_lock;             // 0x10
};

CHECK_SIZE(Bitmap, 0x14);
BEGIN_LAYOUT_CHECK(Bitmap)
	CHECK_FIELD(Bitmap, bi, 0x4);
	CHECK_FIELD(Bitmap, pitch, 0x8);
	CHECK_FIELD(Bitmap, vram, 0xc);
	CHECK_FIELD(Bitmap, m_lock, 0x10);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_WANGREAL_INCLUDE_BITMAP_H
