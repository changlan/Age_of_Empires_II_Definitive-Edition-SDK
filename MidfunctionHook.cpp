#include "MidfunctionHook.h"

#include <cassert>


//
//Overwrites the VALUE of a register. To be used inside a proxy function.
//This function is required because changes like: registers->rdi = 0xdeadbeef will get restored by the trampoline (pop rdi)
//To change the value pointed to by a register just dereference it instead: *(int64*)registers->rdi = 0x4711 (usage of this function not required)
void MidfunctionHook::OverwriteRegister(int64_t rsp, Register reg, int64_t value)
{
	*((int64_t*)rsp + (int)reg) = value;
}

//
//Hooks a function anywhere by placing jumping to a trampoline. The trampoline saves all registers and then calls the proxy function
//0xff, 0x25, 0x0, 0x0, 0x0, 0x0					JMP[rip + 0]
//0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88	absolute address of jump
//The proxy functions signature is expected to be: void __fastcall proxyFunction(registers* registers)
//Important: the overwritten bytes are NOT relocated meaning only position independet instructions can be overwritten
//
//TODO: 
//When hooking within prologe or epicloge of a function the stack may not be aligned 
//use BTR RSP, 3 to align stack and save RSP to then later restore it
void MidfunctionHook::Hook(BYTE* sourceAddress, BYTE* targetAddress, const int hookLength)
{
	const int stubLength = 380;
	const int stubJumpBackLength = 14;
	const int proxyFunctionAddressIndex = 186;

	//14 bytes are required to place JMP[rip+0x] 0x1122334455667788
	assert(hookLength >= stubJumpBackLength);

	//1. save xmm registers
	//2. save general purpose registers
	//3. call proxy function
	//4. restore all registers
	//5. jump back to orignal function
	BYTE stub[stubLength] = {
		0x9C,														//pushfq
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x44, 0x0F, 0x7F, 0x3C, 0x24,							//movdqu XMMWORD PTR [rsp],xmm15
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x44, 0x0F, 0x7F, 0x34, 0x24,							//movdqu XMMWORD PTR [rsp],xmm14
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x44, 0x0F, 0x7F, 0x2C, 0x24,							//movdqu XMMWORD PTR [rsp],xmm13
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x44, 0x0F, 0x7F, 0x24, 0x24,							//movdqu XMMWORD PTR [rsp],xmm12
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x44, 0x0F, 0x7F, 0x1C, 0x24,							//movdqu XMMWORD PTR [rsp],xmm11
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x44, 0x0F, 0x7F, 0x14, 0x24,							//movdqu XMMWORD PTR [rsp],xmm10
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x44, 0x0F, 0x7F, 0x0C, 0x24,							//movdqu XMMWORD PTR [rsp],xmm9
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x44, 0x0F, 0x7F, 0x04, 0x24,							//movdqu XMMWORD PTR [rsp],xmm8
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x0F, 0x7F, 0x3C, 0x24,								//movdqu XMMWORD PTR [rsp],xmm7
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x0F, 0x7F, 0x34, 0x24,								//movdqu XMMWORD PTR [rsp],xmm6
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x0F, 0x7F, 0x2C, 0x24,								//movdqu XMMWORD PTR [rsp],xmm5
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x0F, 0x7F, 0x24, 0x24,								//movdqu XMMWORD PTR [rsp],xmm4
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x0F, 0x7F, 0x1C, 0x24,								//movdqu XMMWORD PTR [rsp],xmm3
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x0F, 0x7F, 0x14, 0x24,								//movdqu XMMWORD PTR [rsp],xmm2
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x0F, 0x7F, 0x0C, 0x24,								//movdqu XMMWORD PTR [rsp],xmm1
		0x48, 0x83, 0xEC, 0x10,										//sub    rsp,0x10
		0xF3, 0x0F, 0x7F, 0x04, 0x24,								//movdqu XMMWORD PTR [rsp],xmm0
		0x41, 0x57,													//push   r15
		0x41, 0x56,													//push   r14
		0x41, 0x55,													//push   r13
		0x41, 0x54,													//push   r12
		0x41, 0x53,													//push   r11
		0x41, 0x52,													//push   r10
		0x41, 0x51,													//push   r9
		0x41, 0x50,													//push   r8
		0x57,														//push   rdi
		0x56,														//push   rsi
		0x55,														//push   rbp
		0x53,														//push   rbx
		0x52,														//push   rdx
		0x51,														//push   rcx
		0x50,														//push   rax
		0x54,														//push	 rsp
		0x48, 0x89, 0xE1,											//mov    rcx,rsp
		0x48, 0x83, 0xEC, 0x28,										//sub    rsp,0x20					(allocate shadow space)
		0x48, 0xB8, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, //movabs rax,0x1122334455667788		(use register to have an absolute 8 byte call)
		0xFF, 0xD0,													//call   rax						(call proxy function)
		0x48, 0x83, 0xC4, 0x28,										//add    rsp,0x20					(deallocate shadow space)
		0x48, 0x83, 0xC4, 0x08,										//add	 rsp, 0x8
		0x58,														//pop    rax
		0x59,														//pop    rcx
		0x5A,														//pop    rdx
		0x5B,														//pop    rbx
		0x5D,														//pop    rbp
		0x5E,														//pop    rsi
		0x5F,														//pop    rdi
		0x41, 0x58,													//pop    r8
		0x41, 0x59,													//pop    r9
		0x41, 0x5A,													//pop    r10
		0x41, 0x5B,													//pop    r11
		0x41, 0x5C,													//pop    r12
		0x41, 0x5D,													//pop    r13
		0x41, 0x5E,													//pop    r14
		0x41, 0x5F,													//pop    r15
		0xF3, 0x0F, 0x6F, 0x04, 0x24,								//movdqu xmm0,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x0F, 0x6F, 0x0C, 0x24,								//movdqu xmm1,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x0F, 0x6F, 0x14, 0x24,								//movdqu xmm2,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x0F, 0x6F, 0x1C, 0x24,								//movdqu xmm3,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x0F, 0x6F, 0x24, 0x24,								//movdqu xmm4,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x0F, 0x6F, 0x2C, 0x24,								//movdqu xmm5,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x0F, 0x6F, 0x34, 0x24,								//movdqu xmm6,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x0F, 0x6F, 0x3C, 0x24,								//movdqu xmm7,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x44, 0x0F, 0x6F, 0x04, 0x24,							//movdqu xmm8,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x44, 0x0F, 0x6F, 0x0C, 0x24,							//movdqu xmm9,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x44, 0x0F, 0x6F, 0x14, 0x24,							//movdqu xmm10,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x44, 0x0F, 0x6F, 0x1C, 0x24,							//movdqu xmm11,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x44, 0x0F, 0x6F, 0x24, 0x24,							//movdqu xmm12,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x44, 0x0F, 0x6F, 0x2C, 0x24,							//movdqu xmm13,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x44, 0x0F, 0x6F, 0x34, 0x24,							//movdqu xmm14,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0xF3, 0x44, 0x0F, 0x6F, 0x3C, 0x24,							//movdqu xmm15,XMMWORD PTR[rsp]
		0x48, 0x83, 0xC4, 0x10,										//add    rsp,0x10
		0x9D														//popfq
	};



	BYTE stubJumpBack[stubJumpBackLength] = {
		0xff, 0x25, 0x0, 0x0, 0x0,0x0,					//JMP[rip + 0]
		0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88	//absolute address of jump
	};

	//remember for unhooking
	this->hookLength = hookLength;
	this->sourceAddress = sourceAddress;

	//save original bytes
	originalBytes = new BYTE[hookLength];
	memcpy(originalBytes, sourceAddress, hookLength);

	//allocate space for stub + space for overwritten bytes + jumpback
	trampoline = (BYTE*)VirtualAlloc(NULL, stubLength + hookLength + stubJumpBackLength, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	//copy stub to trampoline
	memcpy(trampoline, stub, stubLength);

	//copy original bytes to trampoline
	memcpy(&trampoline[stubLength], originalBytes, hookLength);

	//copy jump back to original code
	memcpy(&trampoline[stubLength + hookLength], stubJumpBack, hookLength);

	//insert address of proxy function to call instruction
	*(int64_t*)&trampoline[proxyFunctionAddressIndex] = (int64_t)targetAddress;

	//write jump from trampoline to original code
	*(int64_t*)&trampoline[stubLength + hookLength + 6] = (int64_t)&sourceAddress[hookLength];

	//make trampoline executable
	//DWORD pageProtection;
	//VirtualProtect(trampoline, stubLength + hookLength + stubJumpBackLength, PAGE_EXECUTE_READWRITE, &pageProtection);

	//make page of original code writeable
	DWORD pageProtection;
	VirtualProtect(sourceAddress, hookLength, PAGE_READWRITE, &pageProtection);

	//write JMP from original code to trampoline
	sourceAddress[0] = 0xFF;										//opcodes = JMP [rip+0]
	sourceAddress[1] = 0x25;										//opcodes = JMP [rip+0]
	*(uint32_t*)(&sourceAddress[2]) = 0;							//relative distance from RIP (+0) 
	*(uint64_t*)(&sourceAddress[2 + 4]) = (uint64_t)(trampoline);	//destination to jump to

	//NOP left over bytes
	for (int i = stubJumpBackLength; i < hookLength; i++)
	{
		sourceAddress[i] = 0x90;
	}

	//restore page protection of original code
	VirtualProtect(sourceAddress, hookLength, pageProtection, &pageProtection);
}

//
//Unhooks a previously hooked function by copying back the original bytes
void MidfunctionHook::Unhook()
{
	//make page writeable
	DWORD dwback;
	VirtualProtect(sourceAddress, hookLength, PAGE_READWRITE, &dwback);

	//copy back original bytes
	memcpy(sourceAddress, originalBytes, hookLength);

	//restore page protection
	VirtualProtect(sourceAddress, hookLength, dwback, &dwback);

	//clean up allocated memory
	delete[] originalBytes;

	//memory leak but enables unhooking inside hooked function and makes it threadsafe?
	//delete[] trampoline;
}
