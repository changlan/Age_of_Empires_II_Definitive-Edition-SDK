#include "Offsets.h"

namespace Offsets
{
	//48 8D 0D ? ? ? ? 41 B8 ? ? ? ? E8 ? ? ? ? 33 C0		//3
	//48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B6 C0					//3
	int64_t pathfindingSystem = 0x29a4ba0;

	//48 8B 0D ? ? ? ? E8 ? ? ? ? C6 85						//3
	int64_t mainScreen = 0x2992a40;

	//48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 40			//2
	int64_t tribePanelInven = 0x2993fa0;

	//48 8B 83 ? ? ? ? 48 8B 48 70 F3 0F 10					//2
	int64_t tribePanelInven_localPlayer = 0x208;

	//48 8B 05 ? ? ? ? 48 8B 88 ? ? ? ? 83 79 10 04 75 2E	//1
	int64_t pAVGame = 0x2984b90;

	//MinimapText 88 85 ? ? ? ? 41 8B 46 0C					//1
	int64_t minimapHookOffset = 0xC27079;

	//Functions
	int64_t printNotification = 0xc1d550;		//48 83 EC 48 48 8B 05 ? ? ? ? 4C 8D					//2
	int64_t printBottomText = 0xc0c8b0;			//48 8B C4 48 83 EC 78 F3 0F 10 05 ? ? ? ? 41			//2
	int64_t pauseGame = 0x81ddd0;				//48 89 5C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80	//1
	int64_t sendChat = 0x9abef0;				//not 100% sure if correct
	int64_t createUnitHook = 0xe064b0;			//48 89 5C 24 ? 48 89 6C 24 ? 57 48 83 EC 20 8B 41		//1

}