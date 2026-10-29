// Original: client/Fresh/include/frlistbox.h (JP 983 exe, FreshNext)
#ifndef PG_CLIENT_FRESHNEXT_INCLUDE_FRLISTBOX_H
#define PG_CLIENT_FRESHNEXT_INCLUDE_FRLISTBOX_H

#include "defines.h"
#include "padding.h"

#include "jp983/client/Wangreal/include/wtypes.h"
#include "client/FreshNext/include/frwnd.h"

class Bitmap;
class FrListBox;

// One row of a Fresh list box (KR frlistbox.h): the members JP bodies read
// (UccCopyDlg, JukeBoxDlg owner-draw handlers), at the KR offsets. KR's
// constructor, destructor and later members are not modelled.
struct FrListItem {
	void* pData;          // 0x0
	WPoint pos;           // 0x4
	bool underCursor;     // 0xc
	bool selected;        // 0xd
};

BEGIN_LAYOUT_CHECK(FrListItem)
	CHECK_FIELD(FrListItem, pos, 0x4);
	CHECK_FIELD(FrListItem, underCursor, 0xc);
	CHECK_FIELD(FrListItem, selected, 0xd);
END_LAYOUT_CHECK

// A Fresh list box (KR frlistbox.h, FrListBox : FrWnd): only what JP bodies
// call. m_RTTI: its initializer 0xcf7890 builds ("FrListBox", &FrWnd::m_RTTI)
// there. JP offsets, from the out-of-line members: the item list's
// head/size at 0xd0/0xd4 (AddItem 0xbf0b60, ClearItem 0xbf0e50), m_itemSize
// 0xe0 (SelectItem 0xbefc00, sub_beffc0), m_useRightButton a dword at 0xfc
// and m_rollOver a byte at 0x100 (OnSetCursor 0xbf1500: KR bools at
// 0xfd/0xfe), m_pItemUnderCursor 0x104 (OnSetCursor, cleared by ClearItem),
// m_pSelected 0x108 (SelectItem stores the item, moving the old one to 0x10c).
// The JP type of m_useRightButton is not known: an int holds the dword.
class FrListBox : public FrWnd {
	LAYOUT_CHECK_FRIEND;
public:
	struct sSize {
		int w;   // 0x0
		int h;   // 0x4
	};

	static const WRTTI m_RTTI;                                                 // 0xf1aae0

	void UseRightButton(bool useRightButton) { m_useRightButton = useRightButton; }
	const Bitmap* GetBitmap(const char* name);                                 // 0xbf1170
	FrListItem* GetItemUnderCursor(void) { return m_pItemUnderCursor; }
	FrListItem* GetSelected(void) { return m_pSelected; }
	int GetItemWidth(void) { return m_itemSize.w; }
	int GetItemHeight(void) { return m_itemSize.h; }
	FrListItem* AddItem(void* pData);                                          // 0xbf0b60
	FrListItem* GetItem(int iLineNum);                                         // 0xbeff00
	void ClearItem(void);                                                      // 0xbf0e50
	void SortItem(bool (*compare)(const void*, const void*));                  // 0xbf19d0

protected:
	PADDING(0x044, 0x0e0);
	sSize m_itemSize;                 // 0xe0
	PADDING(0x0e8, 0x0fc);
	int m_useRightButton;             // 0xfc (KR bool at 0xfd)
	bool m_rollOver;                  // 0x100
	PADDING(0x101, 0x104);
	FrListItem* m_pItemUnderCursor;   // 0x104
	FrListItem* m_pSelected;          // 0x108
};

BEGIN_LAYOUT_CHECK(FrListBox)
	CHECK_FIELD(FrListBox, m_itemSize, 0xe0);
	CHECK_FIELD(FrListBox, m_useRightButton, 0xfc);
	CHECK_FIELD(FrListBox, m_rollOver, 0x100);
	CHECK_FIELD(FrListBox, m_pItemUnderCursor, 0x104);
	CHECK_FIELD(FrListBox, m_pSelected, 0x108);
END_LAYOUT_CHECK

#endif // PG_CLIENT_FRESHNEXT_INCLUDE_FRLISTBOX_H
