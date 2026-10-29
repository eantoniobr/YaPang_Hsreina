// Original: unknown, JP-only RTTI class CTutorGuide (JP 983 exe)
#ifndef PG_JP983_NEW_CTUTORGUIDE_H
#define PG_JP983_NEW_CTUTORGUIDE_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/actor.h"
#include "jp983/client/ProjectG/scenemanager.h"
#include "jp983/client/ProjectG/Packet.h"

// The application object behind the global pointer at 0xe47db0 (KR
// WSingleton<CProjectG>); only the field CTutorGuide reads is declared.
class TutorGuideApp
{
public:
    PADDING(0x00, 0x0c);
    float m_timeScale; // 0x0c, CTutorGuide divides the elapsed time by it

    LAYOUT_CHECK_FRIEND;
};

BEGIN_LAYOUT_CHECK(TutorGuideApp)
    CHECK_FIELD(TutorGuideApp, m_timeScale, 0x0c);
END_LAYOUT_CHECK

// The three values messages 0x30f and 0x310 carry (copied as a whole and
// sent field by field; a position, judging by its size, like KR WVector).
// It has a constructor: as a plain struct, cl 16 /GS guards the address-taken
// local copy in HandleMsg with a cookie the original lacks.
struct TutorGuidePos
{
    TutorGuidePos() {}

    float x; // 0x00
    float y; // 0x04
    float z; // 0x08
};

CHECK_SIZE(TutorGuidePos, 0xc);

// One of the four guide entries CTutorGuide holds (class name unknown,
// 0x1bc bytes). Its member bodies are outside this unit (unplaced).
class TutorGuideEntry
{
public:
    TutorGuideEntry();
    ~TutorGuideEntry();                                       // 0x6b20c0

    void Release();                                           // 0x6b1ee0
    void Load(int index);                                     // 0x6b20d0
    void Process(float elapsed);                              // 0x6b2540
    void Display();                                           // 0x6b28f0
    void SetTarget(const TutorGuidePos& pos, int index);      // 0x6b2210

private:
    PADDING(0x000, 0x1bc);
};

CHECK_SIZE(TutorGuideEntry, 0x1bc);

// JP-only actor (RTTI name CTutorGuide; bases IActor, IObject,
// CRenderFuncPtr), vtable at 0xd19e14, IActor's 15 slots; CRenderFuncPtr's
// vtable 0xd19e00 at +0x18.
class CTutorGuide : public IActor, public CRenderFuncPtr
{
    LAYOUT_CHECK_FRIEND;
public:
    static const WRTTI m_RTTI;                                // 0xe78fdc

    CTutorGuide(void);
    virtual const WRTTI* GetRTTI(void) const;                 // 0 (0x6b29f0)
    virtual ~CTutorGuide(void);                               // 1 (??_G 0x6b2a80)
    virtual void OnPreLoadInit(void);                         // 2 (0x6b2490)
    virtual void OnLoad(void);                                // 3 (0x6b24c0)
    virtual void OnInit(void);                                // 4 (0x6b1f60)
    virtual void OnProcess(float elapsed);                    // 6 (0x6b26e0)
    virtual void OnDisplay(void);                             // 7 (0x6b1fa0)
    virtual void OnDestroy(void);                             // 8 (0x6b1f70)

protected:
    virtual void HandleMsg(const MsgObject& msg);             // 11 (0x6b2740)

public:

    // CRenderFuncPtr slot 1 (0x6b2b10).
    virtual void Display(void);

private:
    // Handlers of HandleMsg (bodies elsewhere, not split; names ours).
    void OnMsg97(void);                                       // 0x6b1fb0
    void OnMsg1CE(void);                                      // 0x6b1fd0
    bool IsBusy(float time);                                  // 0x6b2010
    void OnMsg311(void);                                      // 0x6b24e0

    TutorGuideEntry m_entries[4];                             // 0x1c
    float m_elapsed;                                          // 0x70c, scaled time accumulated by OnProcess
};

CHECK_SIZE(CTutorGuide, 0x710);
BEGIN_LAYOUT_CHECK(CTutorGuide)
    CHECK_FIELD(CTutorGuide, m_entries, 0x1c);
    CHECK_FIELD(CTutorGuide, m_elapsed, 0x70c);
END_LAYOUT_CHECK

#endif // PG_JP983_NEW_CTUTORGUIDE_H
