// Original: d:\build\custom\temp\code\client\projectg\river.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_RIVER_H
#define PG_JP983_CLIENT_PROJECTG_RIVER_H

#include "defines.h"
#include "padding.h"
#include "wmath.h"
#include <vector>

// The river surfaces of a course (KR river.h). Layouts as KR: the JP
// constructors and destructors touch the same offsets (VS 2010's
// std::vector is 0x10 here too).
class ntRiver {
public:
	virtual ~ntRiver(void) {}

	virtual void Setup(const std::vector<WVector>& points, const char* name) = 0;
	virtual void Process(float fDelta) = 0;
	virtual void Render(void) = 0;
};
CHECK_SIZE(ntRiver, 0x4);

// River surface: a strip of sRiver segments along the points given to
// Setup, drawn with two scrolling texture layers. Vtable 0xd1c5b0.
class CRiver : public ntRiver {
	LAYOUT_CHECK_FRIEND;
public:
	struct sRiver {
		WVector bank[2];        // 0x0, the strip's two edge points
		float texV[2];          // 0x18, v coordinate of each layer
	};

	// One scrolling texture layer.
	struct sLayer {
		float offset;           // 0x0
		float speed;            // 0x4
		int texture;            // 0x8, WResourceManager handle
		float tileHead;         // 0xc
		float tileSide;         // 0x10
		float depth;            // 0x14
		bool enabled;           // 0x18
	};

	CRiver(void);
	virtual ~CRiver(void);

	virtual void Setup(const std::vector<WVector>& points, const char* name);
	virtual void Process(float fDelta);
	virtual void Render(void);

protected:
	void ReadAttribute(const char* name);

private:
	float m_width;                  // 0x4, half width of the strip (Setup)
	std::vector<sRiver> m_rivers;   // 0x8
	sLayer m_layers[2];             // 0x18
	std::vector<WVector> m_points;  // 0x50
};
CHECK_SIZE(CRiver::sRiver, 0x20);
CHECK_SIZE(CRiver::sLayer, 0x1c);
CHECK_FIELD(CRiver::sLayer, enabled, 0x18);
CHECK_SIZE(CRiver, 0x60);
BEGIN_LAYOUT_CHECK(CRiver)
	CHECK_FIELD(CRiver, m_width, 0x4);
	CHECK_FIELD(CRiver, m_rivers, 0x8);
	CHECK_FIELD(CRiver, m_layers, 0x18);
	CHECK_FIELD(CRiver, m_points, 0x50);
END_LAYOUT_CHECK

// Lava surface: the CRiver strip with its own segment and layer types.
// Vtable 0xd1c5c4.
class ntRiver_Lava : public ntRiver {
	LAYOUT_CHECK_FRIEND;
public:
	struct sRiver {
		WVector bank[2];        // 0x0, the strip's two edge points
		float texV[2];          // 0x18, v coordinate of each layer
	};

	// One scrolling texture layer.
	struct sLayer {
		float offset;           // 0x0
		float speed;            // 0x4
		int texture;            // 0x8, WResourceManager handle
		float tileHead;         // 0xc
		float tileSide;         // 0x10
		float depth;            // 0x14
		bool enabled;           // 0x18
	};

	ntRiver_Lava(void);
	virtual ~ntRiver_Lava(void);

	virtual void Setup(const std::vector<WVector>& points, const char* name);
	virtual void Process(float fDelta);
	virtual void Render(void);

protected:
	void ReadAttribute(const char* name);

private:
	UNKNOWN(0x4, 0x8);
	sLayer m_layers[2];             // 0x8
	std::vector<sRiver> m_rivers;   // 0x40
	std::vector<WVector> m_points;  // 0x50
};
CHECK_SIZE(ntRiver_Lava::sRiver, 0x20);
CHECK_SIZE(ntRiver_Lava::sLayer, 0x1c);
CHECK_SIZE(ntRiver_Lava, 0x60);
BEGIN_LAYOUT_CHECK(ntRiver_Lava)
	CHECK_FIELD(ntRiver_Lava, m_layers, 0x8);
	CHECK_FIELD(ntRiver_Lava, m_rivers, 0x40);
	CHECK_FIELD(ntRiver_Lava, m_points, 0x50);
END_LAYOUT_CHECK

// Extended river: the CRiver strip with its own segment and layer types.
// Vtable 0xd1c5d8.
class CRiver_ex : public ntRiver {
	LAYOUT_CHECK_FRIEND;
public:
	struct sRiver {
		WVector bank[2];        // 0x0, the strip's two edge points
		float texV[2];          // 0x18, v coordinate of each layer
	};

	// One scrolling texture layer.
	struct sLayer {
		float offset;           // 0x0
		float speed;            // 0x4
		int texture;            // 0x8, WResourceManager handle
		float tileHead;         // 0xc
		float tileSide;         // 0x10
		float depth;            // 0x14
		bool enabled;           // 0x18
	};

	CRiver_ex(void);
	virtual ~CRiver_ex(void);

	virtual void Setup(const std::vector<WVector>& points, const char* name);
	virtual void Process(float fDelta);
	virtual void Render(void);

protected:
	void ReadAttribute(const char* name);

private:
	std::vector<sRiver> m_rivers;   // 0x4
	sLayer m_layers[2];             // 0x14
	std::vector<WVector> m_points;  // 0x4c
};
CHECK_SIZE(CRiver_ex::sRiver, 0x20);
CHECK_SIZE(CRiver_ex::sLayer, 0x1c);
CHECK_SIZE(CRiver_ex, 0x5c);
BEGIN_LAYOUT_CHECK(CRiver_ex)
	CHECK_FIELD(CRiver_ex, m_rivers, 0x4);
	CHECK_FIELD(CRiver_ex, m_layers, 0x14);
	CHECK_FIELD(CRiver_ex, m_points, 0x4c);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_RIVER_H
