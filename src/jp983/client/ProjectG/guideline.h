// Original: d:\build\custom\temp\code\client\projectg\guideline.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_GUIDELINE_H
#define PG_JP983_CLIENT_PROJECTG_GUIDELINE_H

#include "defines.h"
#include "padding.h"
#include "actor.h"
#include "scenemanager.h"
#include "wmath.h"
#include "wvideo.h"

class CFxSequence;
class IObject;
class WRTTI;

IObject* CGuideLineMakeInstance(void);

// The guide line actor (RTTI CGuideLine; bases IActor, IObject,
// CRenderFuncPtr), vtable 0xd21d3c, CRenderFuncPtr's vtable 0xd21d28 at
// +0x18. KR layout up to m_texture; JP's WTVertex is 0x58 bytes, so
// m_vertex and m_pVertex move, and a JP-only int follows (size 0xe30, the
// factory's operator new).
class CGuideLine : public IActor, public CRenderFuncPtr
{
    LAYOUT_CHECK_FRIEND;
    friend IObject* CGuideLineMakeInstance(void);
public:
    static const WRTTI m_RTTI;                                // 0xe79fbc

    // One segment of the line, 0x28 bytes.
    class sRoad {
    public:
        sRoad(void);                                          // 0x75b210

        WVector m_left;         // 0x0, left edge of the segment
        WVector m_right;        // 0xc, right edge of the segment
        WVector m_point;        // 0x18, centre point on the ground
        CFxSequence* m_pFx;     // 0x24
    };

    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x75b390)
    virtual ~CGuideLine(void);                                // 1 (0x75b3a0, ??_G 0x75b3c0)
    virtual void OnPreLoadInit(void);                         // 2 (0x75b220)
    virtual void OnLoad(void);                                // 3 (0x75b1e0)
    virtual void OnInit(void);                                // 4 (0x75b1f0)
    virtual void OnProcess(float elapsed);                    // 6 (0x75c3f0)
    virtual void OnDestroy(void);                             // 8 (0x75b2b0)
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x75c590)
    virtual void Display(void);                               // CRenderFuncPtr 1 (0x75b3f0)

protected:
    CGuideLine(void);                                         // 0x75b320

    bool m_bHidden;             // 0x1c
    bool m_bFading;             // 0x1d
    UNKNOWN(0x1e, 0x20);
    int m_segmentCount;         // 0x20
    float m_alpha;              // 0x24, 0..255, the line fades in
    bool m_bActive;             // 0x28
    UNKNOWN(0x29, 0x2c);
    float m_segmentTime;        // 0x2c
    bool m_bDirty;              // 0x30
    UNKNOWN(0x31, 0x34);
    sRoad m_road[80];           // 0x34
    int m_texture;              // 0xcb4
    WTVertex m_vertex[4];       // 0xcb8, one segment's quad
    WTVertex* m_pVertex[5];     // 0xe18, fan order into m_vertex, NULL-terminated
    int m_jpIndexE2C;           // 0xe2c, JP-only: OnInit sets -1; no reader in this unit
};

CHECK_SIZE(CGuideLine::sRoad, 0x28);
CHECK_FIELD(CGuideLine::sRoad, m_left, 0x0);
CHECK_FIELD(CGuideLine::sRoad, m_right, 0xc);
CHECK_FIELD(CGuideLine::sRoad, m_point, 0x18);
CHECK_FIELD(CGuideLine::sRoad, m_pFx, 0x24);
CHECK_SIZE(CGuideLine, 0xE30);
BEGIN_LAYOUT_CHECK(CGuideLine)
    CHECK_FIELD(CGuideLine, m_bHidden, 0x1c);
    CHECK_FIELD(CGuideLine, m_bFading, 0x1d);
    CHECK_FIELD(CGuideLine, m_segmentCount, 0x20);
    CHECK_FIELD(CGuideLine, m_alpha, 0x24);
    CHECK_FIELD(CGuideLine, m_bActive, 0x28);
    CHECK_FIELD(CGuideLine, m_segmentTime, 0x2c);
    CHECK_FIELD(CGuideLine, m_bDirty, 0x30);
    CHECK_FIELD(CGuideLine, m_road, 0x34);
    CHECK_FIELD(CGuideLine, m_texture, 0xcb4);
    CHECK_FIELD(CGuideLine, m_vertex, 0xcb8);
    CHECK_FIELD(CGuideLine, m_pVertex, 0xe18);
    CHECK_FIELD(CGuideLine, m_jpIndexE2C, 0xe2c);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_GUIDELINE_H
