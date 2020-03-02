#pragma once
#include <Windows.h>
#include <cstdint>


class DetourHook64
{
	BYTE* originalBytes;
	BYTE* hookAddress;
	BYTE* trampoline;

	int shellcodeSize;
	int length = 14;
	int pageSize = 4096;

public:
	//Detours x64 functions. The shellcode passed is expected to be relocated already
	BYTE* Hook(BYTE* hookAddress, BYTE* shellcode, int shellcodeSize, uint64_t jmpBack, int length = 14, int pageSize = 4096);
	bool Unhook();

};