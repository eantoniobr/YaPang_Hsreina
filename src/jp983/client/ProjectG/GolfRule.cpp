// Original: client/ProjectG/GolfRule.cpp (JP 983 exe)
#include "jp983/client/ProjectG/GolfRule.h"

// 0x66e850
int CGolfRule::IsReloadFlagged(void)
{
	return 0;
}

// 0x66e860: a `ret 4` stub between two CGolfRule-range game functions
// (0x66e840, 0x66e870). Nothing in the readable code of the exe calls or
// references it (no call, no vtable slot, no function pointer), so neither
// its class nor its name is known.
void __stdcall UnreferencedEmpty_0066e860(int)
{
}
