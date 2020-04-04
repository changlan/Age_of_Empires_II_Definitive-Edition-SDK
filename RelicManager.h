#pragma once
#include "Feature.h"

struct Vector2;
struct Vector3;
class RelicManager : public Feature
{
	std::vector<Unit*> relics;
	int currentRelic = 0;

	//Callbacks
	void OnNeutralUnit(Unit* unit) override;
	void OnMenuMainWindow() override;
};