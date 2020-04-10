#pragma once
#include "Feature.h"

class DetourHook64;
class MinimapText : public Feature
{
	//Callbacks
	void LoadConfig() override;
	void SaveConfig() override;
	void OnInitialise() override;
	void OnMenuMainWindow() override;
	void OnShutdown() override;
};