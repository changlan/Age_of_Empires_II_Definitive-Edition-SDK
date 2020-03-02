


#include "MinimapText.h"

#include "Engine.h"
#include "Sdk.h"
#include "Renderer.h"
#include "Utility.h"

#include "DetourHook64.h"

#pragma warning( disable : 4244 )


bool hookEnabled = true;


char* name = "NewName";


void MinimapText::OnInitialise()
{
	const int shellcodeSize = 29;
	BYTE shellcode[shellcodeSize] = {	0x8B, 0x84, 0xF5, 0x24, 0x1, 0x0, 0x0,			// mov     eax, [rbp+rsi*8+5F8h+var_4D4] <-- orginal code 
										0x89, 0x44, 0x24, 0x20,							// mov     dword ptr[rsp + 6D0h + var_6B0], eax  <-- orginal code 
										0x44, 0x8B, 0x8C, 0xF5, 0x20, 0x1, 0x0, 0x0,	// mov     r9d, dword ptr[rbp + rsi * 8 + 5F8h + var_4DC + 4]  <-- orginal code 
										0x49, 0xB8, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11 };	//MOV R8, 0x1122334455667788 <-- new code (replaces string to print)
	*(uint64_t*)(&shellcode[21]) = (uint64_t)name;
	
	//8B 84 F5 ? ? ? ? 89 
	BYTE* hookAddress = (BYTE*)((int64_t)GetModuleHandle(NULL)+0xA429FD);

	minimapTextDetour = new DetourHook64();
	minimapTextDetour->Hook(hookAddress, shellcode, shellcodeSize, (uint64_t)(hookAddress + 23), 19);
}

void MinimapText::OnShutdown()
{
	minimapTextDetour->Unhook();
}

void MinimapText::OnMenuMainWindow()
{
	ImGui::Checkbox("Minimap Ressource Information", &hookEnabled);
}