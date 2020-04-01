#include "RelicManager.h"
#include "Sdk.h"
#include "Renderer.h"
#include "Engine.h"

void RelicManager::OnNeutralUnit(Unit* unit)
{
}

void RelicManager::OnMenuMainWindow()
{
	if (true) //TODO Need OnGameStart()
	{
		relics.clear();
		Player* gaia = Engine::Get()->GetPlayerByName("Gaia");
		for (int i = 0; i < gaia->pObjectManager->Count; i++)
		{
			Unit* unit = gaia->pObjectManager->units[i];
			if (!unit)
			{
				continue;
			}
			if (strcmp(unit->pUnitData->name, "RELIC") == 0)
			{
				relics.push_back(unit);
			}
		}
	}

	ImGui::Separator();
	ImGui::Text("Relics %d", relics.size());

	if (relics.size() != 0)
	{
		if (ImGui::Button("<"))
		{
			currentRelic = (currentRelic - 1) % relics.size();
			Engine::Get()->GetLocalPlayer()->SetCameraPosition(relics[currentRelic]->position);
		}
		ImGui::SameLine();
		ImGui::Text("%d/%d", currentRelic + 1, relics.size());
		ImGui::SameLine();
		if (ImGui::Button(">"))
		{
			currentRelic = (currentRelic + 1) % relics.size();
			Engine::Get()->GetLocalPlayer()->SetCameraPosition(relics[currentRelic]->position);
		}
	}
	ImGui::Separator();
	
}
