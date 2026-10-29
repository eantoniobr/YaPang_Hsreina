// Original: client/ProjectG/shareddoc.inl (JP 983 exe)
// Global accessors of the shared document, included by SharedDoc.h.

#include "jp983/client/ProjectG/GolfDoc.h"

// shareddoc.inl:328 (KR)
inline CItemManager *ItemManager(void)
{
	return &data_e47dbc->m_itemManager;
}

// shareddoc.inl:340 (KR)
inline sPlayerData *PLAYER(unsigned char index)
{
	CGolfDoc *golfDoc = data_e47dbc->m_pGolfDoc;
	return golfDoc->GetPlayer(index);
}

// shareddoc.inl:356 (KR)
inline CGolfDoc *GOLFDOC(void)
{
	return data_e47dbc->m_pGolfDoc;
}
