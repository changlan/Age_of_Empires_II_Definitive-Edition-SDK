#pragma once
#include "Feature.h"

struct Vector2;
struct Vector3;
class RelicManager : public Feature
{
	uint32_t color;
	int radius = 20;

	std::vector<Unit*> relics;
	int currentRelic = 0;

	//Callbacks
	void OnNeutralUnit(Unit* unit);
	void OnMenuMainWindow();
};