#pragma once
#include "Feature.h"

class DetourHook64;
class MinimapText : public Feature
{
	DetourHook64* minimapTextDetour;

	//Callbacks
	void OnInitialise();
	void OnMenuMainWindow();
	void OnShutdown();
};