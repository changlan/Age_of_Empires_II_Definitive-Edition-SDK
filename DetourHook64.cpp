#include "DetourHook64.h"
#include <cstdio>



//Detours x64 functions. The shellcode passed is expected to be relocated already
BYTE* DetourHook64::Hook(BYTE* hookAddress, BYTE* shellcode, int shellcodeSize, uint64_t jmpBack, int length, int pageSize)
{
	//Save original to be able to unhook
	this->shellcodeSize = shellcodeSize;
	this->hookAddress = hookAddress;
	this->pageSize = pageSize;
	this->originalBytes = new BYTE[length];

	//Make original code writeable (.text segment usually read only). 
	DWORD oldProtection;
	if (!VirtualProtect(hookAddress, length, PAGE_EXECUTE_READWRITE, &oldProtection))
	{
		return NULL; //Couldn't make memory writeable
	}

	for (int i = 0; i < length; i++)
	{
		this->originalBytes[i] = hookAddress[i];
	}
	
	//Create VirtualMemoryPage somewhere (NULL) lets system decide
	trampoline = (BYTE*)VirtualAlloc(NULL, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	if (!trampoline)
	{
		return NULL; //Couldn't allocate virtual memory
	}

	//Copy shellcode into new memory page
	for (int i = 0; i < shellcodeSize; i++)
	{
		trampoline[i] = shellcode[i];
	}

	//Add jump back to original code into new memory
	trampoline[shellcodeSize] = 0xFF;								//opcodes = JMP [rip+0]
	trampoline[shellcodeSize + 1] = 0x25;							//opcodes = JMP [rip+0]
	*(uint32_t*)(&trampoline[shellcodeSize + 2]) = 0;				//relative distance from RIP (+0) 
	*(uint64_t*)(&trampoline[shellcodeSize + 2 + 4]) = jmpBack; 	//destination to jump to

	//Jump to allocated code
	hookAddress[0] = 0xFF;											//opcodes = JMP [rip+0]
	hookAddress[1] = 0x25;											//opcodes = JMP [rip+0]
	*(uint32_t*)(&hookAddress[2]) = 0;								//relative distance from RIP (+0) 
	*(uint64_t*)(&hookAddress[2 + 4]) = (uint64_t)trampoline;	//destination to jump to

	//Restore page protection
	if (!VirtualProtect(hookAddress, length, oldProtection, &oldProtection))
	{
		VirtualFree(trampoline, pageSize, MEM_RELEASE);
		return NULL; //Couldn't restore memory protection
	}

	return trampoline;
}



bool DetourHook64::Unhook()
{
	DWORD oldProtection;
	if (!VirtualProtect(hookAddress, 14, PAGE_EXECUTE_READWRITE, &oldProtection))
	{
		return false; //Couldn't make memory writeable
	}

	memcpy(hookAddress, originalBytes, 14);
	VirtualFree(trampoline, pageSize, MEM_RELEASE);
	delete[] originalBytes;

	if (!VirtualProtect(hookAddress, 14, oldProtection, &oldProtection))
	{
		return false; //Couldn't restore memory protection
	}

	return true;
}
