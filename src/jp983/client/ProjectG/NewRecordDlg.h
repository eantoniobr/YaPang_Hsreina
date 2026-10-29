// Original: d:\build\custom\temp\code\client\projectg\newrecorddlg.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_NEWRECORDDLG_H
#define PG_JP983_CLIENT_PROJECTG_NEWRECORDDLG_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/ProjectG/ObjectFactory.h"
#include "jp983/client/ProjectG/RTTI.h"
#include "client/FreshNext/include/frform.h"

class FrListBox;
struct sFRESH_ENTRY;

IObject* FrNewRecordDlgMakeInstance(void);                    // 0xae3a20

// New course record dialog (RTTI FrNewRecordDlg; vtables 0xd05ec4 (38
// slots, only GetRTTI and the destructor overridden), 0xd05eb4 (FrCmdTarget)
// and 0xd05eac (FrModalRenderer)). Size 0x120, the `new` of
// FrNewRecordDlgMakeInstance (KR 0x118). The constructor and destructor are
// the compiler's: MakeInstance inlines the constructor, ??_G (0x502950) the
// destructor.
class FrNewRecordDlg : public FrForm
{
    LAYOUT_CHECK_FRIEND;

public:
    static const WRTTI m_RTTI;                                // 0xf03284
    virtual const WRTTI* GetRTTI(void) const { return &m_RTTI; }   // 0 (0x4ffd30)

private:
    static sFRESH_ENTRY _MsgEntries[];

protected:
    static sFRESH_MSGMAP _MsgMap;                             // 0xe3a1a8
    virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // FrCmdTarget 1 (0xae3a10)

    void OnCourseListOwnerDraw(int param);
    void OnCourseListInit(int param);

private:
    PADDING(0x110, 0x120);
};

CHECK_SIZE(FrNewRecordDlg, 0x120);

#endif // PG_JP983_CLIENT_PROJECTG_NEWRECORDDLG_H
