// Original: client/Fresh/include/frcmdtarget.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRCMDTARGET_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRCMDTARGET_H

#include "defines.h"

class FrCmdTarget;
class FrForm;
struct sFRESH_MSGMAP;

// KR frcmdtarget.h's result callback, declared while FrCmdTarget is still
// incomplete as in KR (the general pointer-to-member representation). Not
// verified in JP: only declarations use it so far.
typedef bool (FrCmdTarget::*FRESH_RESULT_CALLBACK)(int, FrForm*);

// Receiver of Fresh commands (RTTI name FrCmdTarget), slots as in KR
// frcmdtarget.h: 0 the destructor, 1 GetMessageMap. The JP body of slot 1
// (0xc08430) returns null. Only the vtable is declared here; KR's message-map
// types and helpers come over when a JP body needs them.
class FrCmdTarget
{
public:
    FrCmdTarget(void);
    virtual ~FrCmdTarget(void);                               // 0

protected:
    virtual const sFRESH_MSGMAP* GetMessageMap(void) const;   // 1 (0xc08430)
};

CHECK_SIZE(FrCmdTarget, 0x4);

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRCMDTARGET_H
