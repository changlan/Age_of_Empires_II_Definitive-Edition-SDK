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

	int64_t AVGame = 0x2902590;

	//ESP
	//48 8B 8B ? ? ? ? E8 ? ? ? ? 48 85 FF
	int64_t unit_actionlist = 0x278;

	//MinimapText
	int64_t minimapHookOffset = 0xBE6F99;

	int64_t printNotification = 0xbdd670;
	int64_t printBottomText = 0xbcdc00;

	int64_t sendChat = 0x96f300;
}