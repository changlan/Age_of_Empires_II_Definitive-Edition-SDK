#include "Debug.h"

#include "Sdk.h"
#include "Renderer.h"
#include "Engine.h"


void Debug::OnInitialise()
{

}
void Debug::OnMenuMainWindow()
{
	int idleUnits = 0;

	PlayerArray* playerArray = Engine::Get()->GetPlayerArray();
	
	ImGui::Separator();
	ImGui::Text("Debug");
	//ImGui::Text("Idle: %d", idleUnit);
	if (ImGui::Button("Flare"))
	{
		Engine::Get()->Flare(100.f, 100.f);
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
