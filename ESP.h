#pragma once
#include "Feature.h"

struct Vector2;
struct Vector3;
class ESP : public Feature
{
	bool gaiaESP = true;
	bool goldESP = true;
	bool stoneESP = true;
	bool trebuchetESP = true;
	bool siegeImpactLocation = true;

	bool playerUnitEsp[8] = { true,true,true,true,true,true,true,true };
	bool playerUnitDestinationEsp[8] = { false,false,false,false,false,false,false,false };

	bool playerUnitNameEsp[8] = { false,false,false,false,false,false,false,false };
	//bool playerBuildingEsp[8] = { false,true,true,true,true,true,true,true };
	//bool playerBuildingNameEsp[8] = { false,true,true,true,true,true,true,true };
	float colors[8][3] = { 0 };
	static uint32_t colors_hex[8];

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