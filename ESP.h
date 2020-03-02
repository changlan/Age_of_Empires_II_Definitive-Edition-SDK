#pragma once
#include "Feature.h"

class ESP : public Feature
{
	bool gaiaEsp = true;
	bool goldESP = true;
	bool stoneESP = true;
	bool playerUnitEsp[8] = { false,false,true,true,true,true,true,true };

	bool playerUnitNameEsp[8] = { false,false,false,false,false,false,false,false };
	//bool playerBuildingEsp[8] = { false,true,true,true,true,true,true,true };
	//bool playerBuildingNameEsp[8] = { false,true,true,true,true,true,true,true };
	float colors[8][3];
	static uint32_t colors_hex[8];

	//Callbacks
	void OnUnitIteration(Unit* unit, Player* player, int playerIndex);
	void OnMenuPlayerTreenode(Player* player, int playerIndex);
	void OnNeutralUnit(Unit* unit);
	void OnMenuMainWindow();

	void DrawBox(Unit* unit, int32_t color, bool drawName);
};