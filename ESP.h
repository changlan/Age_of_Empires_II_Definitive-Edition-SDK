#pragma once
#include "Feature.h"

#include <string>

struct Vector2;
struct Vector3;
class ESP : public Feature
{
	bool gaiaESP = true;
	bool goldESP = true;
	bool stoneESP = true;
	bool trebuchetESP = true;
	bool siegeImpactLocation = true;

	bool playerUnitEsp[9] = { true,true,true,true,true,true,true,true, true };
	bool playerUnitDestinationEsp[9] = { false,false,false,false,false,false,false,false, false };

	bool playerUnitNameEsp[9] = { false,false,false,false,false,false,false,false, false };
	//bool playerBuildingEsp[8] = { false,true,true,true,true,true,true,true };
	//bool playerBuildingNameEsp[8] = { false,true,true,true,true,true,true,true };
	float colors[8][3] = { 0 };
	static uint32_t colors_hex[8];

	std::vector<std::string>  namesFish = { "FISHS", "FISHX","FISH1","FISH2","FISH3","FISH4","turtles" };
	std::vector<std::string>  namesHeavyFood = { "BOARX", "RHINO","BOAR","BOARJ","WELEF" };
	std::vector<std::string>  namesLighthuntable = { "DEERX", "IBEX","ZEBRA","OSTRICH" };
	std::vector<std::string>  namesLightFood = { "SHEEPG", "GOOSE","PIG", "LLAMAG", "Cow Black", "Cow Brown", "Cow Black and White", "BUFFALO", "TURKYG", "GOAT" };
	std::vector<std::string>  namesDangerousAnimal = { "WOLFX", "KOMODO","GJAGR", "SLEOPA", "BEAR", "CROCO", "LION", "TIGER" };

	//Callbacks
	void LoadConfig() override;
	void SaveConfig() override;
	void OnUnitIteration(Unit* unit, Player* player, int playerIndex) override;
	void OnMenuPlayerTreenode(Player* player, int playerIndex) override;
	void OnNeutralUnit(Unit* unit) override;
	void OnMenuMainWindow() override;

	void DrawBox(Unit* unit, int32_t color, bool drawName);
	void DrawBox(Vector3 position, Vector2 edgeSize, int32_t color);

	void DrawCircle(Unit* unit, int radius, int32_t color, int smoothness , float thickness, bool drawName);
};