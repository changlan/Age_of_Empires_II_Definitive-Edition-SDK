#pragma once
#include "Feature.h"

class CustomLoadingScreen : public Feature
{
private:
	char* imagePath;

public:
	CustomLoadingScreen() = delete;
	
	//Supports .gif, .bmp, .jpg, .png
	CustomLoadingScreen(char* imagePath);

	//Callbacks
	void OnInitialise() override;
	void OnMenuMainWindow() override;
	void OnShutdown() override;
};