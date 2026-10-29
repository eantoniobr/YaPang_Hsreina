// Original: unknown, JP-only RTTI class _gateway::_controller::CControllerDoc (JP 983 exe)
#ifndef PG_JP983_NEW__GATEWAY__CONTROLLER_CCONTROLLERDOC_H
#define PG_JP983_NEW__GATEWAY__CONTROLLER_CCONTROLLERDOC_H

#include "defines.h"
#include "padding.h"

// The RTTI names the hierarchy CControllerDoc -> _gateway::CGatewayControlDoc
// -> IContentsDataContainer; slot names are KR's (client/ProjectG/icontentsdoc.h,
// GatewayDoc.h). No jp983 copy of those headers exists yet, so the bases are
// declared here with only the slots the vtable 0xd026c8 needs.
struct IContentsDataContainer {
    IContentsDataContainer(void) {}
    virtual ~IContentsDataContainer(void) {}

    virtual bool Initialize(void) = 0;
    virtual bool Release(void) = 0;

    virtual bool Reset(void) { return true; }
};

namespace _gateway {

class CGatewayHandler;

// Vtable 0xd023a8.
class CGatewayControlDoc : public IContentsDataContainer {
public:
    CGatewayControlDoc(void) {}
    virtual ~CGatewayControlDoc(void) {}

    virtual CGatewayHandler* GetGatewayHandler(void) { return 0; }
};

namespace _controller {

// Vtable 0xd026c8. The members at 0x0c, 0x1c and 0x2c are std containers the
// destructor (0x4ba950) clears; the layout is known only as far as the
// bodies read it.
class CControllerDoc : public CGatewayControlDoc {
    LAYOUT_CHECK_FRIEND;
public:
    CControllerDoc(void);
    virtual ~CControllerDoc(void);                                       // 0 (??_G 0x4baa20, dtor 0x4ba950)

    virtual bool Initialize(void);                                       // 1 (0x4baac0)
    virtual bool Release(void);                                          // 2 (0x4b9e70)
    virtual bool Reset(void) { return true; }                            // 3 (0x4b51e0)
    virtual CGatewayHandler* GetGatewayHandler(void) { return m_pGatewayHandler; } // 4 (0x4ba940)

private:
    PADDING(0x04, 0x3c);
    CGatewayHandler* m_pGatewayHandler;                                  // 0x3c
};

BEGIN_LAYOUT_CHECK(CControllerDoc)
    CHECK_FIELD(CControllerDoc, m_pGatewayHandler, 0x3c);
END_LAYOUT_CHECK

} // namespace _controller
} // namespace _gateway

#endif // PG_JP983_NEW__GATEWAY__CONTROLLER_CCONTROLLERDOC_H
