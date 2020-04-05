#include "Offsets.h"

namespace Offsets
{
	//48 8D 0D ? ? ? ? 41 B8 ? ? ? ? E8 ? ? ? ? 33 C0   //1
	//48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B6 C0				//1
	int64_t pathfindingSystem = 0x2921690;

	//48 8B 0D ? ? ? ? E8 ? ? ? ? C6 85					//1
	int64_t mainScreen = 0x290f160;

	//44 89 25 ? ? ? ? 2B								//1
	//41 8B 45 28 99 + c								//1
	int64_t totalPlayers = 0x2793064;

	//48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 40
	int64_t tribePanelInven = 0x2910550;

	//48 8B 83 ? ? ? ? 48 8B 48 70 F3 0F 10 
	int64_t tribePanelInven_localPlayer = 0x208;

	int64_t pAVGame = 0x2902590;

	//48 8B 8B ? ? ? ? E8 ? ? ? ? 48 85 FF
	int64_t unit_actionlist = 0x278;

	//MinimapText
	int64_t minimapHookOffset = 0xBE6F99;

	//Functions
	int64_t printNotification = 0xbdd670;		//48 83 EC 48 48 8B 05 ? ? ? ? 4C 8D
	int64_t printBottomText = 0xbcdc00;			//48 8B C4 48 83 EC 78 F3 0F 10 05 ? ? ? ? 41
	int64_t pauseGame = 0x7f5740;				//48 89 5C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 80
	int64_t sendChat = 0x96f300;				//E8 ? ? ? ? 33 FF 49 8B 04
}