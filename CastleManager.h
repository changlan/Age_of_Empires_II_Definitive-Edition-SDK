#pragma once
#include "Feature.h"

class CastleManager : public Feature {
  // Callbacks
  void LoadConfig() override;
  void SaveConfig() override;
  void OnUnitIteration(Unit* unit, Player* player, int playerIndex) override;
  void OnUnitCreated(Unit* unit) override;
  void OnMenuMainWindow() override;
  void OnDraw() override;
  void OnPlayerIteration(Player* player, int playerIndex) override;
};