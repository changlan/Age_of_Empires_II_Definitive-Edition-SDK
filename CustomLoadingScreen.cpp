#include "CustomLoadingScreen.h"

#include "Patcher.h"


CustomLoadingScreen::CustomLoadingScreen(char* imagePath)
{
	this->imagePath = imagePath;
}

void CustomLoadingScreen::OnInitialise()
{
	//char* newLoadScreen = "C:\\Users\\Fahersto\\Pictures\\wallpaper.jpg";
	//char* newLoadScreen = "C:\\Users\\Fahersto\\Pictures\\wallpaper.jpg";

	//original string "/resources/loading_slash.png"
	Patcher().Patch((BYTE*)GetModuleHandle(NULL) + 0x2088328,(int64_t)this->imagePath);

	//change LEA to MOV by changing 0x8d to 0x8b
	//E8 ? ? ? ? 4C 89 A5 ? ? ? ? 48 8D 15 ? ? ? ? 48 + 0xC (location where string is loaded)
	Patcher().Patch((BYTE*)GetModuleHandle(NULL) + 0xD10DDA + 1, (int8_t)0x8b);
}

void CustomLoadingScreen::OnMenuMainWindow()
{

}

void CustomLoadingScreen::OnShutdown()
{
	//Restart the game
}