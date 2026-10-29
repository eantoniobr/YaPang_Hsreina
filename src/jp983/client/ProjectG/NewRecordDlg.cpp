// Original: d:\build\custom\temp\code\client\projectg\newrecorddlg.cpp (JP 983 exe)
#include "NewRecordDlg.h"

// 0xae3a10
const sFRESH_MSGMAP* FrNewRecordDlg::GetMessageMap(void) const
{
    return &FrNewRecordDlg::_MsgMap;
}

// 0xae3a20
IObject* FrNewRecordDlgMakeInstance(void)
{
    return new FrNewRecordDlg;
}

struct __sFrNewRecordDlg {
    // 0xae3a90
    __sFrNewRecordDlg(void)
    {
        ObjectFactory().AddObjectFunctor(FrNewRecordDlgMakeInstance, "FrNewRecordDlg");
    }
};
static __sFrNewRecordDlg s_registerFrNewRecordDlg;
