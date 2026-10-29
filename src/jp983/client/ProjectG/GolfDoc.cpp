// Original: client/ProjectG/GolfDoc.cpp (JP 983 exe)

// Empty functions (a lone `ret`) the split places in GolfDoc's address range.
// Nothing in the readable code of the exe calls or references them (no call,
// no vtable slot, no function pointer), so neither their class nor their name
// is known; they are kept as free functions with the address in the name.
// The ones right after a `test ecx,ecx; je; mov eax,[edx]; mov [ecx],eax`
// construct helper (0x660780, 0x6607a0, 0x660980, 0x6609a0) are probably the
// matching destroy helper of a VS 2010 container of a 4-byte type.

// 0x49dce0
void UnreferencedEmpty_0049dce0(void)
{
}

// 0x49de40
void UnreferencedEmpty_0049de40(void)
{
}

// 0x4a3aa0
void UnreferencedEmpty_004a3aa0(void)
{
}

// 0x4a3c60
void UnreferencedEmpty_004a3c60(void)
{
}

// 0x4a4080
void UnreferencedEmpty_004a4080(void)
{
}

// 0x4a5d50
void UnreferencedEmpty_004a5d50(void)
{
}

// 0x4a61d0
void UnreferencedEmpty_004a61d0(void)
{
}

// 0x65fd60
void UnreferencedEmpty_0065fd60(void)
{
}

// 0x660780
void UnreferencedEmpty_00660780(void)
{
}

// 0x6607a0
void UnreferencedEmpty_006607a0(void)
{
}

// 0x660980
void UnreferencedEmpty_00660980(void)
{
}

// 0x6609a0
void UnreferencedEmpty_006609a0(void)
{
}
