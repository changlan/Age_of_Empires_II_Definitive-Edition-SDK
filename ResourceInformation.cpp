#include "ResourceInformation.h"

#include "Engine.h"
#include "Renderer.h"
#include "Sdk.h"

void ResourceInformation::OnMenuPlayerTreenode(Player* player,
                                               int playerIndex) {
  ImGui::Text("Resources: %p", player->pResources);
  ImGui::Text("Wood: %.f", player->pResources->wood);
  ImGui::Text("Food: %.f", player->pResources->food);
  ImGui::Text("Gold: %.f", player->pResources->gold);
  ImGui::Text("Stone: %.f", player->pResources->stone);
  ImGui::Text(
      "PopSpaceLeft: %.f/%.f", player->pResources->currentPop,
      player->pResources->currentPop + player->pResources->popSpaceLeft);
}