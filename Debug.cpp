#include "Debug.h"

#include "Sdk.h"
#include "Renderer.h"
#include "Engine.h"


void Debug::OnInitialise()
{

}
void Debug::OnMenuMainWindow()
{
	ImGui::Separator();
	ImGui::Text("Debug");
	if (ImGui::Button("Annoy @Kleon"))
	{
		Engine::Get()->PrintNotification("When DOOM Eternal hack? ");
	}
	if (ImGui::Button("Annoy @Timb3r"))
	{
		Engine::Get()->PrintBottomNotification("I do miss the meme war :(", 0xffffffff);
	}
	ImGui::Separator();
}

void Debug::OnShutdown()
{

}