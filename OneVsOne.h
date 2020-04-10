#pragma once
#pragma once
#include "Feature.h"

class OneVsOne : public Feature
{
	//Callbacks
	void OnDraw() override;
	void OnUnitIteration(Unit* unit, Player* player, int playerIndex) override;
	void OnMenuPlayerTreenode(Player* player, int playerIndex) override;
	void OnNeutralUnit(Unit* unit) override;
	void OnMenuMainWindow() override;
};