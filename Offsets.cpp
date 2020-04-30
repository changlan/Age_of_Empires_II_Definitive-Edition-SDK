#include "Offsets.h"

namespace Offsets
{
	//48 8D 0D ? ? ? ? 41 B8 ? ? ? ? E8 ? ? ? ? 33 C0   //2
		//48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B6 C0			//2
	int64_t pathfindingSystem = 0x2961db0;

	//48 8B 0D ? ? ? ? E8 ? ? ? ? C6 85					//2
	int64_t mainScreen = 0x294fc50;

	//not updated
	//int64_t totalPlayers = 0x2793064;

	//48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 40		//1
	int64_t tribePanelInven = 0x29511b0;

	//48 8B 83 ? ? ? ? 48 8B 48 70 F3 0F 10 
	int64_t tribePanelInven_localPlayer = 0x208;

	//48 8B 0D ? ? ? ? E8 ? ? ? ? 48 3B 47 18 0F		//1
	int64_t pAVGame = 0x2941e70;

	//not updated
	//48 8B 8B ? ? ? ? E8 ? ? ? ? 48 85 FF
	//int64_t unit_actionlist = 0x278;

	//MinimapText 88 85 ? ? ? ? 41 8B 46 0C
	int64_t minimapHookOffset = 0xc10269;

	//Functions
	int64_t printNotification = 0xc06610;		//48 83 EC 48 48 8B 05 ? ? ? ? 4C 8D					//1
	int64_t printBottomText = 0xbf5a00;			//48 8B C4 48 83 EC 78 F3 0F 10 05 ? ? ? ? 41			//1
	int64_t pauseGame = 0x80cff0;				//48 89 5C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80	//1
	int64_t sendChat = 0x9972a0;				//E8 ? ? ? ? 33 FF 49 8B 04								//1
	int64_t createUnitHook = 0xdec390;			//48 89 5C 24 ? 48 89 6C 24 ? 57 48 83 EC 20 8B 41		//1

}