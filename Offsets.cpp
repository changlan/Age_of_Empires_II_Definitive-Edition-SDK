#include "Offsets.h"

namespace Offsets
{
	//48 8D 0D ? ? ? ? 41 B8 ? ? ? ? E8 ? ? ? ? 33 C0		//4
	//48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B6 C0					//4
	int64_t pathfindingSystem = 0x29A3AE0;

	//48 8B 0D ? ? ? ? E8 ? ? ? ? C6 85						//4
	int64_t mainScreen = 0x2991980;

	//48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 40			//3
	int64_t tribePanelInven = 0x2992EE0;

	//48 8B 83 ? ? ? ? 48 8B 48 70 F3 0F 10					//3
	int64_t tribePanelInven_localPlayer = 0x208;

	//49 83 BF ? ? ? ? ? 0F 86 ? ? ? ? 48 8B + 0xE
	int64_t pAVGame = 0x2983AD0;

	//MinimapText 88 85 ? ? ? ? 41 8B 46 0C					//2
	int64_t minimapHookOffset = 0xc26e49;

	//Functions
	int64_t printNotification = 0xc1d320;		//48 83 EC 48 48 8B 05 ? ? ? ? 4C 8D					//3
	int64_t printBottomText = 0xc0c680;			//48 8B C4 48 83 EC 78 F3 0F 10 05 ? ? ? ? 41			//3
	int64_t pauseGame = 0x81ddd0;				//48 89 5C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80	//2
	
	//E8 ? ? ? ? 90 48 8B 05 ? ? ? ? F2  - 0x94															//0
	int64_t sendChat = 0x9AC090;
	
	int64_t createUnitHook = 0xE06260;			//48 89 5C 24 ? 48 89 6C 24 ? 57 48 83 EC 20 8B 41		//2

	int64_t playerArrayStart = 0x2a8;

	//Manual Update
	//CustomLoadingScreen
	int64_t pathToLoadScreen = 0x1E72D20;		// /resources/loading_slash.png
	int64_t loadPathToLoadScreen = 0xEEA8EE;	// x-ref /resources/loading_slash.png
}