#include "CustomLoadingScreen.h"

#include "Patcher.h"


CustomLoadingScreen::CustomLoadingScreen(char* imagePath)
{
	this->imagePath = imagePath;
}

void CustomLoadingScreen::OnInitialise()
{
	//original string "/resources/loading_slash.png"
	Patcher().Patch((BYTE*)GetModuleHandle(NULL) + 0x1E73E40,(int64_t)this->imagePath);

	//change LEA to MOV by changing 0x8d to 0x8b
	Patcher().Patch((BYTE*)GetModuleHandle(NULL) + 0xEEAB6E + 1, (int8_t)0x8b);
}

void CustomLoadingScreen::OnMenuMainWindow()
{

}

void CustomLoadingScreen::OnShutdown()
{
	//Restart the game
}