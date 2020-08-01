#include "InitialiseOffsets.h"


#include "Pattern.h"
#include "Offsets.h"

#include <Windows.h>

void InitialiseOffsets::OnInitialise()
{
	using namespace Offsets;
	

	printf("~~ Initialising Offsets ~~\n");

	uint64_t base = (uint64_t)GetModuleHandle(NULL);

	pathfindingSystem = Pattern::FindSignature("AoE2DE_s.exe", "48 8D 0D ? ? ? ? 41 B8 ? ? ? ? E8 ? ? ? ? 33 C0");
	pathfindingSystem += *(uint32_t*)(pathfindingSystem + 3) + 7;
	pathfindingSystem -= base;
	printf("pathfindingSystem: %x\n", pathfindingSystem);

	mainScreen = Pattern::FindSignature("AoE2DE_s.exe", "48 8B 0D ? ? ? ? E8 ? ? ? ? C6 85");
	mainScreen += *(uint32_t*)(mainScreen + 3) + 7;
	mainScreen -= base;
	printf("mainScreen: %x\n", mainScreen);

	tribePanelInven = Pattern::FindSignature("AoE2DE_s.exe", "48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 40");
	tribePanelInven += *(uint32_t*)(tribePanelInven + 3) + 7;
	tribePanelInven -= base;
	printf("tribePanelInven: %x\n", tribePanelInven);

	tribePanelInven_localPlayer = Pattern::FindSignature("AoE2DE_s.exe", "48 8B 83 ? ? ? ? 48 8B 48 70 F3 0F 10");
	tribePanelInven_localPlayer = *(uint32_t*)(tribePanelInven_localPlayer + 3);
	tribePanelInven_localPlayer -= base;
	printf("tribePanelInven_localPlayer: %x\n", tribePanelInven_localPlayer);

	playerArrayStart = Pattern::FindSignature("AoE2DE_s.exe", "48 8B 88 ? ? ? ? 8B 83 ? ? ? ? 48 8B 0C");
	playerArrayStart = *(int32_t*)(playerArrayStart + 3);
	printf("playerArrayStart: %x\n", playerArrayStart);
	
	pAVGame = Pattern::FindSignature("AoE2DE_s.exe", "49 83 BF ? ? ? ? ? 0F 86 ? ? ? ? 48 8B") + 0xE;
	pAVGame += *(uint32_t*)(pAVGame + 3) + 7;
	pAVGame -= base;
	printf("pAVGame: %x\n", pAVGame);


	minimapHookOffset = Pattern::FindSignature("AoE2DE_s.exe", "88 85 ? ? ? ? 41 8B 46 0C");
	minimapHookOffset -= base;
	printf("minimapHookOffset: %x\n", minimapHookOffset);

	//Functions
	printNotification = Pattern::FindSignature("AoE2DE_s.exe", "48 83 EC 48 48 8B 05 ? ? ? ? 4C 8D");
	printNotification -= base;
	printf("printNotification: %x\n", printNotification);
	
	printBottomText = Pattern::FindSignature("AoE2DE_s.exe", "48 8B C4 48 83 EC 78 F3 0F 10 05 ? ? ? ? 41");
	printBottomText -= base;
	printf("printBottomText: %x\n", printBottomText);
		
	sendChat = Pattern::FindSignature("AoE2DE_s.exe", "E8 ? ? ? ? 90 48 8B 05 ? ? ? ? F2") - 0x94;
	sendChat -= base;
	printf("sendChat: %x\n", sendChat);


	createUnitHook = Pattern::FindSignature("AoE2DE_s.exe", "48 89 74 24 ? B8 ? ? ? ? 4C 89 74") - 0x23;
	createUnitHook -= base;
	printf("createUnitHook: %x\n", createUnitHook);



	printf("~~~~~~~~~~~~~~~\n");
}