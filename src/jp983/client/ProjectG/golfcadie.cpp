// Original: client/ProjectG/golfcadie.cpp (JP 983 exe)
#include "golfcadie.h"

#include "jp983/client/ProjectG/PetBody.h"

// The scene manager instance (KR CSceneManager::Instance()), unnamed global.
extern "C" CSceneManager* data_e741c0;
// The frame time (KR g_CurrentTime), unnamed global.
extern "C" unsigned long data_f022d4;
// The camera pivot (KR g_camera.pivot), unnamed global.
extern "C" WVector data_f02454;

// 0x730e40
void CGolfCaddie::ResetTalk(void)
{
    m_bubbleTalkType = 0;
    for (int i = 0; i < 36; i++)
        m_talked[i] = false;

    m_talkFlag = false;
    m_talkResetTime = data_f022d4;
}

// 0x730f00
void CGolfCaddie::DontLookUp(void)
{
    if (m_pCaddie)
        m_pCaddie->m_pBody->LookUp(0, true);
}

// 0x731e20
void CGolfCaddie::OnPreLoadInit(void)
{
    data_e741c0->RegisterElement((eObjType)4, 0, this, "\xc4\xb3\xb5\xf0", 0x18, 0);
}

// 0x732020: JP rewrite of the KR token reader. Skips leading blanks and
// line feeds, copies up to the ':' that ends the token (dropping spaces and
// keeping Shift-JIS double-byte characters whole) and returns the character
// after it, or 0 when the text ends first.
char* CGolfCaddie::GetBehaviorEndToken(char* token, char* src)
{
    while (*src == ' ' || *src == '\n')
        src++;

    while (*src) {
        if (*src == ' ') {
            src++;
            continue;
        }

        unsigned char c = *src;
        if ((c >= 0x80 && c < 0xa0) || (c >= 0xe0 && c <= 0xfc))
            *token++ = *src++;
        *token++ = *src++;

        if (*src == ':') {
            *token = '\0';
            return src + 1;
        }
    }

    return 0;
}

// 0x732080
bool CGolfCaddie::ShouldDisplay(void)
{
    if (!m_visible || !m_pCaddie)
        return false;

    float dist = (data_f02454 - m_position).Magnitude();
    if (dist > 640.0f)
        return false;

    return true;
}

// 0x739c10
const WRTTI* CGolfCaddie::GetRTTI(void) const
{
    return &m_RTTI;
}
