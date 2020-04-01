#include "CustomLoadingScreen.h"

#include "Patcher.h"


CustomLoadingScreen::CustomLoadingScreen(char* imagePath)
{
	this->imagePath = imagePath;
}

void CustomLoadingScreen::OnInitialise()
{
	//original string "/resources/loading_slash.png"
	Patcher().Patch((BYTE*)GetModuleHandle(NULL) + 0x1dff178,(int64_t)this->imagePath);

	//change LEA to MOV by changing 0x8d to 0x8b
	//E8 ? ? ? ? 90 48 8D 8D ? ? ? ? E8 ? ? ? ? 45 33 + 0x1c (location where string is loaded)
	Patcher().Patch((BYTE*)GetModuleHandle(NULL) + 0xe966a6 + 1, (int8_t)0x8b);
}

void CustomLoadingScreen::OnMenuMainWindow()
{

}

void CustomLoadingScreen::OnShutdown()
{
	//Restart the game
}