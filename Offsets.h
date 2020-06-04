#pragma once
#include <cstdint>

namespace Offsets
{
	extern int64_t pathfindingSystem;
	extern int64_t mainScreen;
	extern int64_t totalPlayers;
	extern int64_t pausesLeft;
	extern int64_t pAVGame;
	extern int64_t playerArrayStart;

	extern int64_t tribePanelInven;
	extern int64_t tribePanelInven_localPlayer;

	extern int64_t minimapHookOffset;

	//Functions
	extern int64_t printNotification;
	extern int64_t printBottomText;
	extern int64_t pauseGame;
	extern int64_t sendChat;
	extern int64_t createUnitHook;

	//CustomLoadingScreen
	extern int64_t pathToLoadScreen;
	extern int64_t loadPathToLoadScreen;
}
