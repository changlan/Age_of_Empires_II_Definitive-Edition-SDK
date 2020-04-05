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
	if (ImGui::Button("SendChat"))
	{
		Engine::Get()->SendChat("Testmessage", true);
	}
	if (ImGui::Button("SendChat2"))
	{
		Engine::Get()->SendChat("Testmessage2", false);
	}
	ImGui::Separator();
}

void Debug::OnShutdown()
{

}

void Debug::OnUnitCreated(Unit* unit)
{
	printf("Created %s\n", unit->pUnitData->name);
}
