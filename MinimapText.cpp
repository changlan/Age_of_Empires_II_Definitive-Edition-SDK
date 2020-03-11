


#include "MinimapText.h"

#include "Engine.h"
#include "Sdk.h"
#include "Renderer.h"
#include "Utility.h"

#include "DetourHook64.h"

#include <map>

#pragma warning( disable : 4244 )


char* name = "NewName";


typedef int(__fastcall* printMinimap)(void* that, char* format, ...);
printMinimap oPrintMinimap;

int __fastcall  hookedWrapper(void* that, char* format, char* playername, int currentPoints, int maxPoints)
{
	printf("In da Hook\n");

	return oPrintMinimap(that, format, playername, currentPoints, maxPoints); //call original call
}

void MinimapText::OnInitialise()
{
	//Working
	//const int shellcodeSize = 29;
	//BYTE shellcode[shellcodeSize] = { 0x8B, 0x84, 0xF5, 0x24, 0x1, 0x0, 0x0,			// mov     eax, [rbp+rsi*8+5F8h+var_4D4] <-- orginal code 
	//									0x89, 0x44, 0x24, 0x20,							// mov     dword ptr[rsp + 6D0h + var_6B0], eax  <-- orginal code 
	//									0x44, 0x8B, 0x8C, 0xF5, 0x20, 0x1, 0x0, 0x0,	// mov     r9d, dword ptr[rbp + rsi * 8 + 5F8h + var_4DC + 4]  <-- orginal code 
	//									0x49, 0xB8, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11 };	//MOV R8, 0x1122334455667788 <-- new code (replaces string to print)
	//*(uint64_t*)(&shellcode[21]) = (uint64_t)name;

	////8B 84 F5 ? ? ? ? 89 
	//BYTE* hookAddress = (BYTE*)Utility::Scan("\x8B\x84\xF5\x00\x00\x00\x00\x89", "xxx????x", (char*)0x7ff000000000, 0x800000000000 - 0x7ff000000000);
	//printf("hookAddress: %p\n", hookAddress);
	//minimapTextDetour = new DetourHook64();
	//minimapTextDetour->Hook(hookAddress, shellcode, shellcodeSize, (uint64_t)(hookAddress + 23), 19);

	BYTE* callAddress = (BYTE*)Utility::Scan("\xE8\x00\x00\x00\x00\x49\x8B\x9D\x00\x00\x00\x00\x33\xD2\x44", "x????xxx????xxx", (char*)0x7ff000000000, 0x800000000000 - 0x7ff000000000);
	
	BYTE* function = (BYTE*)Utility::Scan("\xFF\x15\x00\x00\x00\x00\x85\xC0\x0F\x48", "xx????xxxx", (char*)0x7ff000000000, 0x800000000000 - 0x7ff000000000);
	
	function = function - 0x4b;
	printf("callAddress: %p\n", callAddress);
	printf("function: %p\n", function);
	printf("hookedWrapper: %p\n", hookedWrapper);


	oPrintMinimap = (printMinimap)(function);

	int32_t callRelativeOffset = (int64_t)hookedWrapper - (int64_t)callAddress - 5;


	getchar();
	//*(int32_t*)(callAddress + 1) = callRelativeOffset; //override original call

	//TO CALL E8 ? ? ? ? 49 8B 9D ? ? ? ? 33 D2 44
}

void MinimapText::OnShutdown()
{
	//minimapTextDetour->Unhook();
}

void MinimapText::OnMenuMainWindow()
{
	//ImGui::Checkbox("Minimap Ressource Information", &hookEnabled);
}