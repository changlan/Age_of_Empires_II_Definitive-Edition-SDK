#pragma once
#include "Feature.h"

class Debug : public Feature
{
	//Callbacks
	void OnInitialise() override;
	void OnMenuMainWindow() override;
	void OnShutdown() override;
};