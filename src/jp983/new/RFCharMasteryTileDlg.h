// Original: unknown, JP-only RTTI class RFCharMasteryTileDlg (JP 983 exe)
#ifndef PG_JP983_NEW_RFCHARMASTERYTILEDLG_H
#define PG_JP983_NEW_RFCHARMASTERYTILEDLG_H

#include "RFWndEx.h"

// JP-only Refresh dialog (RTTI name RFCharMasteryTileDlg), vtable 0xd0f67c,
// RFWndEx's 34 slots. The RTTI puts RFFormBase<RFWndEx> between this class
// and RFWndEx; no Refresh header declares that template yet, so the class
// derives from RFWndEx directly. Layout unknown beyond the base.
class RFCharMasteryTileDlg : public RFWndEx {
public:
	RFCharMasteryTileDlg();
	virtual ~RFCharMasteryTileDlg(); // [1] 0x5c2280 (??_G 0x5c2990)
};

#endif // PG_JP983_NEW_RFCHARMASTERYTILEDLG_H
