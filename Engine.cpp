#include "Engine.h"

#include "Sdk.h"
#include "Offsets.h"
#include "Renderer.h"


Engine* Engine::instance = NULL;

Engine::Engine()
{
	base = (uint64_t)GetModuleHandle(NULL);
	printf("Base: %llu\n", base);
}

Engine* Engine::Get()
{
	if (!instance)
	{
		instance = new Engine();
	}
	return instance;
}

World* Engine::GetWorld() const
{
	PathfindingSystem* pathfindingSystem = reinterpret_cast<PathfindingSystem*>(base + Offsets::pathfindingSystem);
	if (!pathfindingSystem)
	{
		return NULL;
	}
	return pathfindingSystem->GetWorld();
}

Game* Engine::GetGame() const
{
	return *reinterpret_cast<Game**>(base + Offsets::pAVGame);
}

MainScreen* Engine::GetMainScreen() const
{
	return reinterpret_cast<MainScreen*>(base + Offsets::mainScreen);
}

int Engine::GetTotalPlayers() const
{
	World* world = GetWorld();
	if (!world)
	{
		return 0;
	}
	return (*(int64_t*)((int64_t)world + 0x2a8) - *(int64_t*)((int64_t)world + 0x2a0)) / 0x10;
}

PlayerArray* Engine::GetPlayerArray() const
{
	MainScreen* mainScreen = GetMainScreen();
	if (!mainScreen)
	{
		return NULL;
	}

	World* world = GetWorld();
	if (!world)
	{
		return NULL;
	}

	return world->pPlayerArray;
}

Vector2 Engine::worldToScreen(Vector3 position) const
{
	MainScreen* mainScreen = GetMainScreen();
	static int tileSize = GetWorld()->pMap->GetTileSize();
	int tile_width = tileSize * mainScreen->pGameScreen->pMainView->ScreenPosZ;
	int tile_height = tileSize * mainScreen->pGameScreen->pMainView->ScreenPosZ;
	
	float xDelta = position.x - mainScreen->pGameScreen->pMainView->ScreenPosX ;
	float yDelta = position.y - mainScreen->pGameScreen->pMainView->ScreenPosY;

	int xResolution = mainScreen->pGameScreen->ScreenResX;
	int yResolution = mainScreen->pGameScreen->ScreenResY;

	float screenXfinal = ((xDelta + yDelta) / 2) * tile_width + (xResolution / 2);
	float screenYfinal = (((xDelta - yDelta) / 2) * tile_height * -1) / 2 + (yResolution / 2);

	screenYfinal -= position.z * tileSize * mainScreen->pGameScreen->pMainView->ScreenPosZ / 4;

	return Vector2(screenXfinal,screenYfinal);
}

Vector2 Engine::worldToScreen(Unit* unit) const
{
	return worldToScreen(unit->position);
}

uint32_t Engine::GetPlayerColor(int colorIndex) const
{
	return playerColors[colorIndex];
}

ImVec4 Engine::GetPlayerColorImGUI(int colorIndex) const
{
	ImVec4 color;
	switch (colorIndex)
	{
	case 0:
		color = ImVec4(0, 0, 1, 1);
		break;
	case 1:
		color = ImVec4(1, 0, 0, 1);
		break;
	case 2:
		color = ImVec4(0, 1, 0, 1);
		break;
	case 3:
		color = ImVec4(1, 1, 0, 1);
		break;
	case 4:
		color = ImVec4(0, 1, 1, 1);
		break;
	case 5:
		color = ImVec4(1, 0, 1, 1);
		break;
	case 6:
		color = ImVec4(0.5, 0.5, 0.5, 1);
		break;
	case 7:
		color = ImVec4(1, 0.5, 0, 1);
		break;
	}
	return color;
}

Player* Engine::GetPlayer(int index) const
{
	const int totalPlayers = GetTotalPlayers();
	if (index > totalPlayers)
	{
		return nullptr;
	}
	
	MainScreen* mainScreen = GetMainScreen();
	if (!mainScreen)
	{
		return nullptr;
	}

	World* main = GetWorld();
	if (!main)
	{
		return nullptr;
	}

	PlayerArray* playerArray = main->pPlayerArray;
	if (!playerArray)
	{
		return nullptr;
	}
	
	return playerArray->playerData[index].player;
}

Player* Engine::GetPlayerByName(char* playerName) const
{
	MainScreen* mainScreen = GetMainScreen();
	if (!mainScreen)
	{
		return nullptr;
	}

	World* main = GetWorld();
	if (!main)
	{
		return nullptr;
	}

	PlayerArray* playerArray = main->pPlayerArray;
	if (!playerArray)
	{
		return nullptr;
	}
	int totalPlayers = GetTotalPlayers();

	for (int i = 0; i <= totalPlayers; i++)
	{
		Player* player = playerArray->playerData[i].player;
		if (!player)
		{
			continue;
		}
		if (strcmp(playerName, player->name) == 0)
		{
			return player;
		}
	}
	return nullptr;
}

Player* Engine::GetLocalPlayer() const
{
	const uint64_t tribePanelInven = *reinterpret_cast<uint64_t*>(base + Offsets::tribePanelInven);
	if (!tribePanelInven)
	{
		return NULL;
	}
	return *reinterpret_cast<Player**>(tribePanelInven + Offsets::tribePanelInven_localPlayer);
}

//
//Pauses the game
void Engine::PauseGame() const
{
	typedef int64_t(__fastcall* tPauseGame)(CommHandler* CommHandler);
	static tPauseGame fPauseGame = (tPauseGame)(base + Offsets::pauseGame);
	fPauseGame(Get()->GetGame()->pCommHandler);
}

//
//Sends a chat message. Only to be called from rendering thread
void Engine::SendChat(const char* message, bool teamchat) const
{
	typedef void(__fastcall* tSendChat) (int64_t game, const char* text);
	static tSendChat fSendChat = (tSendChat)(base + Offsets::sendChat);
	static int64_t game = *(int64_t*)(base + Offsets::pAVGame);

	if (teamchat)
	{
		std::string teammessage = ";" + std::string(message);
		fSendChat(game, teammessage.c_str());
	}
	else
	{
		fSendChat(game, message);
	}
}

void Engine::PrintNotification(const char* message) const
{
	typedef void(__fastcall* tPrintNotification) (GameScreen* AVGameScreen, const char* message, int unknown);
	static tPrintNotification fPrintNotification = (tPrintNotification)(base + Offsets::printNotification);
	fPrintNotification(GetMainScreen()->pGameScreen, message, 1);
}

void Engine::PrintBottomNotification(const char* message, unsigned int hexcolor) const
{
	typedef void(__fastcall* tPrintBottomText) (GameScreen* AVGameScreen, const char* message, unsigned int hexcolor, int64_t unused);
	static tPrintBottomText fPrintBottomText = (tPrintBottomText)(base + Offsets::printBottomText);
	fPrintBottomText(GetMainScreen()->pGameScreen, message, hexcolor, 0xffffffffffffffff); //Color format: RBGA
}

int64_t Engine::Flare(float xPos, float yPos) const
{
	typedef __int64(__fastcall* tCreateFlare) (Player* player, __int64 hundert12, __int64 zero1, __int64 zero2, float xPos, float yPos, int64_t zero3, int64_t zero4);
	static tCreateFlare fCreateFlare = (tCreateFlare)(base + 0xc31270);
	
	return fCreateFlare(GetLocalPlayer(), 0x112, 0, 0, 220.f, 220.f, 0, 0);
	//__usercall fhsCreateFlare_MAYBE_7FF718CF1270@<rax>( __int64 a3_zero@<r8>, __int64 a4_zero@<r9>, float xPos@<xmm2>, float yPos@<xmm3>, __int64 a5_zero, int a6_Zero)
}
