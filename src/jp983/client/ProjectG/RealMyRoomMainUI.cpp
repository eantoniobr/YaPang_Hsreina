// Original: client/ProjectG/RealMyRoomMainUI.cpp (JP 983 exe)

// Trivial functions the split places in RealMyRoomMainUI's address range,
// between game functions of the unit. Nothing in the readable code of the exe
// calls or references them (no call, no vtable slot, no function pointer), so
// neither their class nor their name is known; they are kept as free
// (`__fastcall`, the /Gr default) functions with the address in the name.

// 0x604710
int UnreferencedLoad_00604710(const int* value)
{
    return *value;
}

// 0x604920
void* UnreferencedIdentity_00604920(void* object)
{
    return object;
}

// 0x604930
void UnreferencedEmpty_00604930(void)
{
}

// 0x605bc0
// `ret 4`: one stack argument after the two register ones.
void UnreferencedEmpty_00605bc0(int, int, int)
{
}

// 0x607d30
void UnreferencedEmpty_00607d30(void)
{
}
