#include "InitialiseOffsets.h"

#include <Windows.h>

#include "Offsets.h"
#include "Pattern.h"

void InitialiseOffsets::OnInitialise() {
  using namespace Offsets;
  printf("~~ Initialising Offsets ~~\n");

  uint64_t base = (uint64_t)GetModuleHandle(NULL);
  bool failed = false;

  pathfindingSystem = Pattern::FindSignature(
      "AoE2DE_s.exe", "48 8D 0D ? ? ? ? 41 B8 ? ? ? ? E8 ? ? ? ? 33 C0");
  if (pathfindingSystem) {
    pathfindingSystem += *(uint32_t*)(pathfindingSystem + 3) + 7;
    pathfindingSystem -= base;
    printf("pathfindingSystem: %llx\n", pathfindingSystem);
  } else {
    printf("Unable to find signature for pathfindingSystem\n");
    failed = true;
  }

  mainScreen = Pattern::FindSignature("AoE2DE_s.exe",
                                      "48 8B 0D ? ? ? ? E8 ? ? ? ? C6 85");
  if (mainScreen) {
    mainScreen += *(uint32_t*)(mainScreen + 3) + 7;
    mainScreen -= base;
    printf("mainScreen: %llx\n", mainScreen);
  } else {
    printf("Unable to find signature for mainScreen\n");
    failed = true;
  }

  tribePanelInven = Pattern::FindSignature(
      "AoE2DE_s.exe", "48 8B 0D ? ? ? ? 48 85 C9 0F 84 ? ? ? ? 40");
  if (tribePanelInven) {
    tribePanelInven += *(uint32_t*)(tribePanelInven + 3) + 7;
    tribePanelInven -= base;
    printf("tribePanelInven: %llx\n", tribePanelInven);
  } else {
    printf("Unable to find signature for tribePanelInven\n");
    failed = true;
  }

  tribePanelInven_localPlayer = Pattern::FindSignature(
      "AoE2DE_s.exe", "48 8B 83 ? ? ? ? 48 8B 48 70 F3 0F 10");
  if (tribePanelInven_localPlayer) {
    tribePanelInven_localPlayer = *(uint32_t*)(tribePanelInven_localPlayer + 3);
    tribePanelInven_localPlayer -= base;
    printf("tribePanelInven_localPlayer: %llx\n", tribePanelInven_localPlayer);
  } else {
    printf("Unable to find signature for tribePanelInven_localPlayer\n");
    failed = true;
  }

  playerArrayStart = Pattern::FindSignature(
      "AoE2DE_s.exe", "48 8B 88 ? ? ? ? 8B 83 ? ? ? ? 48 8B 0C");
  if (playerArrayStart) {
    playerArrayStart = *(int32_t*)(playerArrayStart + 3);
    printf("playerArrayStart: %llx\n", playerArrayStart);
  } else {
    printf("Unable to find signature for playerArrayStart\n");
    failed = true;
  }

  pAVGame = Pattern::FindSignature("AoE2DE_s.exe",
                                   "49 83 BF ? ? ? ? ? 0F 86 ? ? ? ? 48 8B");
  if (pAVGame) {
    pAVGame += 0xE;
    pAVGame += *(uint32_t*)(pAVGame + 3) + 7;
    pAVGame -= base;
    printf("pAVGame: %llx\n", pAVGame);
  } else {
    printf("Unable to find signature for pAVGame\n");
    failed = true;
  }

  minimapHookOffset =
      Pattern::FindSignature("AoE2DE_s.exe", "88 85 ? ? ? ? 41 8B 46 0C");
  if (minimapHookOffset) {
    minimapHookOffset -= base;
    printf("minimapHookOffset: %llx\n", minimapHookOffset);
  } else {
    printf("Unable to find signature for minimapHookOffset\n");
    failed = true;
  }

  // Functions
  printNotification = Pattern::FindSignature(
      "AoE2DE_s.exe", "48 83 EC 48 48 8B 05 ? ? ? ? 4C 8D");
  if (printNotification) {
    printNotification -= base;
    printf("printNotification: %llx\n", printNotification);
  } else {
    printf("Unable to find signature for printNotification\n");
    failed = true;
  }

  printBottomText = Pattern::FindSignature(
      "AoE2DE_s.exe", "48 8B C4 48 83 EC 78 F3 0F 10 05 ? ? ? ? 41");
  if (printBottomText) {
    printBottomText -= base;
    printf("printBottomText: %llx\n", printBottomText);
  } else {
    printf("Unable to find signature for printBottomText\n");
    failed = true;
  }

  sendChat = Pattern::FindSignature("AoE2DE_s.exe",
                                    "E8 ? ? ? ? 90 48 8B 05 ? ? ? ? F2");
  if (sendChat) {
    sendChat -= 0x94;
    sendChat -= base;
    printf("sendChat: %llx\n", sendChat);
  } else {
    printf("Unable to find signature for sendChat\n");
    failed = true;
  }

  createUnitHook = Pattern::FindSignature("AoE2DE_s.exe",
                                          "48 89 74 24 ? B8 ? ? ? ? 4C 89 74");
  if (createUnitHook) {
    createUnitHook -= 0x23;
    createUnitHook -= base;
    printf("createUnitHook: %llx\n", createUnitHook);
  } else {
    printf("Unable to find signature for createUnitHook\n");
    failed = true;
  }

  return;
}