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
	if (!pathfindingSystem) {
		printf("Unable to find signature for pathfindingSystem\n");
		return;
	}
	pathfindingSystem += *(uint32_t*)(pathfindingSystem + 3) + 7;
	pathfindingSystem -= base;
	printf("pathfindingSystem: %llx\n", pathfindingSystem);

	mainScreen = Pattern::FindSignature("AoE2DE_s.exe", "48 8B 0D ? ? ? ? E8 ? ? ? ? C6 85");
	if (!mainScreen) {
		printf("Unable to find signature for mainScreen\n");
		return;
	}
	mainScreen += *(uint32_t*)(mainScreen + 3) + 7;
	mainScreen -= base;
	printf("mainScreen: %llx\n", mainScreen);

	tribePanelInven = Pattern::FindSignature("AoE2DE_s.exe", "48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 40");
	if (!tribePanelInven) {
		printf("Unable to find signature for tribePanelInven\n");
		return;
	}
	tribePanelInven += *(uint32_t*)(tribePanelInven + 3) + 7;
	tribePanelInven -= base;
	printf("tribePanelInven: %llx\n", tribePanelInven);

	tribePanelInven_localPlayer = Pattern::FindSignature("AoE2DE_s.exe", "48 8B 83 ? ? ? ? 48 8B 48 70 F3 0F 10");
	if (!tribePanelInven_localPlayer) {
		printf("Unable to find signature for tribePanelInven_localPlayer\n");
		return;
	}
	tribePanelInven_localPlayer = *(uint32_t*)(tribePanelInven_localPlayer + 3);
	tribePanelInven_localPlayer -= base;
	printf("tribePanelInven_localPlayer: %llx\n", tribePanelInven_localPlayer);

	playerArrayStart = Pattern::FindSignature("AoE2DE_s.exe", "48 8B 88 ? ? ? ? 8B 83 ? ? ? ? 48 8B 0C");
	if (!playerArrayStart) {
		printf("Unable to find signature for playerArrayStart\n");
		return;
	}
	playerArrayStart = *(int32_t*)(playerArrayStart + 3);
	printf("playerArrayStart: %llx\n", playerArrayStart);
	
	pAVGame = Pattern::FindSignature("AoE2DE_s.exe", "49 83 BF ? ? ? ? ? 0F 86 ? ? ? ? 48 8B") + 0xE;
	if (!pAVGame) {
		printf("Unable to find signature for pAVGame\n");
		return;
	}
	pAVGame += *(uint32_t*)(pAVGame + 3) + 7;
	pAVGame -= base;
	printf("pAVGame: %llx\n", pAVGame);

	minimapHookOffset = Pattern::FindSignature("AoE2DE_s.exe", "88 85 ? ? ? ? 41 8B 46 0C");
	if (!minimapHookOffset) {
		printf("Unable to find signature for minimapHookOffset\n");
		return;
	}
	minimapHookOffset -= base;
	printf("minimapHookOffset: %llx\n", minimapHookOffset);

	//Functions
	printNotification = Pattern::FindSignature("AoE2DE_s.exe", "48 83 EC 48 48 8B 05 ? ? ? ? 4C 8D");
	if (!printNotification) {
		printf("Unable to find signature for printNotification\n");
		return;
	}
	printNotification -= base;
	printf("printNotification: %llx\n", printNotification);
	
	printBottomText = Pattern::FindSignature("AoE2DE_s.exe", "48 8B C4 48 83 EC 78 F3 0F 10 05 ? ? ? ? 41");
	if (!printBottomText) {
		printf("Unable to find signature for printBottomText\n");
		return;
	}
	printBottomText -= base;
	printf("printBottomText: %llx\n", printBottomText);
		
	sendChat = Pattern::FindSignature("AoE2DE_s.exe", "E8 ? ? ? ? 90 48 8B 05 ? ? ? ? F2") - 0x94;
	if (!sendChat) {
		printf("Unable to find signature for sendChat\n");
		return;
	}
	sendChat -= base;
	printf("sendChat: %llx\n", sendChat);

	createUnitHook = Pattern::FindSignature("AoE2DE_s.exe", "48 89 74 24 ? B8 ? ? ? ? 4C 89 74") - 0x23;
	if (!createUnitHook) {
		printf("Unable to find signature for createUnitHook\n");
		return;
	}
	createUnitHook -= base;
	printf("createUnitHook: %llx\n", createUnitHook);

	printf("~~~~~~~~~~~~~~~\n");
}