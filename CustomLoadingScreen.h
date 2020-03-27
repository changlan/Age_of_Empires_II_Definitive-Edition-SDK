#pragma once
#pragma once
#include "Feature.h"

class CustomLoadingScreen : public Feature
{
private:
	CustomLoadingScreen();

	char* imagePath;

public:
	//Supports .gif, .bmp, .jpg, .png
	CustomLoadingScreen(char* imagePath);

	//Callbacks
	void OnInitialise();
	void OnMenuMainWindow();
	void OnShutdown();
};