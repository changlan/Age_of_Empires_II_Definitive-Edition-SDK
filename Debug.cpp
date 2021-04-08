#include "Debug.h"

#include "Engine.h"
#include "Renderer.h"
#include "Sdk.h"

void Debug::OnInitialise() {}
void Debug::OnMenuMainWindow() {
  int idleUnits = 0;

  PlayerArray* playerArray = Engine::Get()->GetPlayerArray();

  ImGui::Separator();
  ImGui::Text("Debug");
  // ImGui::Text("Idle: %d", idleUnit);
  if (ImGui::Button("nothing")) {
  }
  ImGui::Separator();
}

void Debug::OnShutdown() {}

void Debug::OnUnitCreated(Unit* unit) {
  // printf("Created %s\n", unit->pUnitData->name);
}
