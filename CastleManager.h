#pragma once
#include "Feature.h"


class CastleManager : public Feature
{
	//Callbacks
	void OnUnitCreated(Unit* unit) override;
	void OnMenuMainWindow() override;
};