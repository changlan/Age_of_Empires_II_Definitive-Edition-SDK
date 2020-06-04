#pragma once
#include <cstdint>

struct Vector2;
struct Vector3;
struct ImVec4;

class World;
class Unit;
class Game;
class MainScreen;
class Player;
class PlayerArray;

class Engine
{
	static Engine* instance;

	uint64_t base;
	uint32_t playerColors[8] = { 0xff0000ff, 0xffff0000,0xff00ff00,0xffffff00,0xff00ffff,0xffff00ff,0xff7f7f7f,0xffffb400 };

	//void __fastcall UnitMoveTo_7FF64AAE6F40(int64_t* that, int one, int64_t zero, int fourty, int a5, int a6)

	Engine();

public:
	static Engine* Get();
	World* GetWorld() const;

	Game* GetGame() const;
	MainScreen* GetMainScreen() const;
	int64_t GetTotalPlayers() const;
	PlayerArray* GetPlayerArray() const;

	Vector2 worldToScreen(Vector3 position) const;
	Vector2 worldToScreen(Unit* unit) const;

	uint32_t GetPlayerColor(int colorIndex) const;
	ImVec4 GetPlayerColorImGUI(int colorIndex) const;
	Player* GetPlayer(int index) const;
	Player* GetPlayerByName(char* playername) const;
	Player* GetLocalPlayer() const;

	void PauseGame() const;
	void SendChat(const char* message, bool teamchat = false) const;
	void PrintNotification(const char* message) const;
	void PrintBottomNotification(const char* message, unsigned int hexcolor) const;
	int64_t Flare(float xPos, float yPos) const;
};