#include "RelicManager.h"

#include "Engine.h"
#include "Renderer.h"
#include "Sdk.h"

void RelicManager::OnNeutralUnit(Unit* unit) {}

void RelicManager::OnMenuMainWindow() {
  if (true) {
    relics.clear();
    Player* gaia = Engine::Get()->GetPlayerByName("Gaia");
    for (int i = 0; i < gaia->pObjectManager->Count; i++) {
      Unit* unit = gaia->pObjectManager->units[i];
      if (!unit) {
        continue;
      }
      if (strcmp(unit->GetUnitData()->GetName(), "RELIC") == 0) {
        relics.push_back(unit);
      }
    }
  }

  ImGui::Separator();
  ImGui::Text("Relics %d", relics.size());

  if (relics.size() != 0) {
    if (ImGui::Button("<")) {
      currentRelic = (currentRelic - 1) % relics.size();
      Engine::Get()->GetLocalPlayer()->SetCameraPosition(
          relics[currentRelic]->GetPosition());
    }
    ImGui::SameLine();
    ImGui::Text("%d/%d", currentRelic + 1, relics.size());
    ImGui::SameLine();
    if (ImGui::Button(">")) {
      currentRelic = (currentRelic + 1) % relics.size();
      Engine::Get()->GetLocalPlayer()->SetCameraPosition(
          relics[currentRelic]->GetPosition());
    }
  }
  ImGui::Separator();
}