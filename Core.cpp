#pragma once
#include <Windows.h>
#include <iostream>

#include "imgui\imgui.h"
#include "imgui\imgui_internal.h"


#include "Sdk.h"
#include "Renderer.h"
#include "Core.h"
#include "Engine.h"
#include "FeatureManager.h"
#include "Utility.h"
#include "MidfunctionHook.h"

//Features
#include "CastleManager.h"
#include "ResourceInformation.h"
#include "ESP.h"
#include "MinimapText.h"
#include "RelicManager.h"
#include "CustomLoadingScreen.h"
#include "Debug.h"
//#include "PauseManager.h"

MidfunctionHook onGameStartHook = MidfunctionHook();
MidfunctionHook onTurnHook = MidfunctionHook();
MidfunctionHook onCreateUnitHook = MidfunctionHook();

void __fastcall  OnGameStartHook(Registers* registers)
{
	FeatureManager::Get()->OnGameStart();
	printf("OnGameStart()\n");
}


void __fastcall  OnTurnHook(Registers* registers)
{
	FeatureManager::Get()->OnTurn();
	printf("OnTurn()\n");
}

void __fastcall  OnCreateUnitHook(Registers* registers)
{
	__try
	{
		const auto objectManager = reinterpret_cast<ObjectManager*>(registers->rcx);
		const int totalPlayers = Engine::Get()->GetTotalPlayers();

		bool foundArray = false;
		PlayerArray* playerArray = Engine::Get()->GetPlayerArray();
		for (int i = 1; i <= totalPlayers; i++)
		{
			Player* player = playerArray->playerData[i].player;
			if (!player)
			{
				continue;
			}

			if (player->pObjectManager == objectManager)
			{
				foundArray = true;
				break;
			}
		}

		if (foundArray)
		{
			const auto unit = reinterpret_cast<Unit*>(registers->rdx);
			FeatureManager::Get()->OnCreateUnit(unit);
		}
	}
	__except (1)
	{
		
	}
}

Core::Core()
{
	//onGameStartHook.Hook((BYTE*)GetModuleHandle(NULL) + 0xba276a, (BYTE*)OnGameStartHook, 15);
	//onGameStartHook.Hook((BYTE*)GetModuleHandle(NULL) + 0x7463b, (BYTE*)OnTurnHook, 14);
	onCreateUnitHook.Hook((BYTE*)GetModuleHandle(NULL) + 0xdce840, (BYTE*)OnCreateUnitHook, 15);
	
	FeatureManager* featureManager = FeatureManager::Get();

	//Register Features here
	featureManager->RegisterFeature(new ResourceInformation());
	featureManager->RegisterFeature(new ESP());
	featureManager->RegisterFeature(new MinimapText());
	featureManager->RegisterFeature(new RelicManager());
	featureManager->RegisterFeature(new CustomLoadingScreen("C:\\wallpaper.jpg"));
	//featureManager->RegisterFeature(new PauseManager());
	featureManager->RegisterFeature(new CastleManager());

#ifdef _DEBUG
	featureManager->RegisterFeature(new Debug());
#endif

	FeatureManager::Get()->OnInitialise();
}

void createPlayerTreeNode(Player* player, int playerIndex)
{
	ImGui::PushStyleColor(ImGuiCol_Text, Engine::Get()->GetPlayerColorImGUI(*player->pColor));

	std::string playerText = "Player " + std::to_string(playerIndex);
	if (ImGui::TreeNode(player->name))
	{
		ImGui::PushStyleColor(ImGuiCol_Text, 0xffffffff);
		ImGui::Text("Player %p (%f, %f)", player, player->xScreenPos, player->yScreenPos);
		FeatureManager::Get()->OnMenuPlayerTreenode(player, playerIndex);
		if (ImGui::TreeNode(player->pObjectManager->units, "Units %p", (int64_t)player->pObjectManager->units))
		{
			int buildingCount = 0;
			int infantryCount = 0;
			int calavaryCount = 0;
			for (int i = 0; i < player->pObjectManager->Count; i++)
			{
				Unit* unit = player->pObjectManager->units[i];
				if (!unit) { continue; }

				if (unit->pOwner == player)
				{
					ImGui::Text("%p", unit);
					ImGui::SameLine();
					ImGui::Text("%s", unit->pUnitData->name);
					ImGui::SameLine();
					std::string text = std::string("Copy##") + std::string(unit->pUnitData->name) + std::to_string(i);

					if (ImGui::Button(text.c_str()))
					{
						Utility::CopyToClipboard((uint64_t)unit);
					}
					std::string vmtTree = std::string("VMT##") + std::string(unit->pUnitData->name) + "VMT";
					if (ImGui::TreeNode(vmtTree.c_str()))
					{
						for (int vmtIndex = 0; vmtIndex < 175; vmtIndex++)
						{
							std::string vmtText = std::string("Copy##") + std::string(unit->pUnitData->name) + std::to_string(vmtIndex) + "VMT";
							ImGui::Text("%d - %p", vmtIndex, *(int64_t**)(*(int64_t**)unit + vmtIndex));
							ImGui::SameLine();
							if (ImGui::Button(vmtText.c_str()))
							{
								Utility::CopyToClipboard((uint64_t) * (int64_t**)(*(int64_t**)unit + vmtIndex));
							}
						}
						ImGui::TreePop();
					}

					if (unit->pUnitData->Class == (int16_t)EnumUnitDataClass::Building)
					{
						buildingCount++;
					}
					if (unit->pUnitData->Class == (int16_t)EnumUnitDataClass::Infantry)
					{
						infantryCount++;
					}
					if (unit->pUnitData->Class == (int16_t)EnumUnitDataClass::Cavalry)
					{
						calavaryCount++;
					}
				}
			}
			ImGui::Text("Buildings %.d", buildingCount);
			ImGui::Text("Infantry %.d", infantryCount);
			ImGui::Text("Cavalry %.d", calavaryCount);
			ImGui::TreePop();
		}
		ImGui::PopStyleColor();
		ImGui::TreePop();
	}
	ImGui::PopStyleColor();
}


void Core::OnPresent()
{
	__try
	{
		//printf("Valid: ");
		MainScreen* mainScreen = Engine::Get()->GetMainScreen();
		if (!mainScreen)
		{
			return;
		}
		//printf("mainScreen %p", mainScreen);
		World* world = Engine::Get()->GetWorld();
		if (!world)
		{
			return;
		}
		//printf(" world %p", world);

		PlayerArray* playerArray = world->pPlayerArray;
		if (!playerArray)
		{
			return;
		}
		//printf(" playerArray %p", playerArray);
		int totalPlayers = Engine::Get()->GetTotalPlayers();

		static bool openOverlay = true;
		if (GetAsyncKeyState(VK_INSERT) & 1) { openOverlay = !openOverlay; }

		Renderer::Get()->BeginScene();
		FeatureManager::Get()->OnDraw();
		Player* gaiaPlayer = *(Player**)(playerArray);

		if (gaiaPlayer)
		{
			for (int i = 0; i < gaiaPlayer->pObjectManager->Count; i++)
			{
				Unit* unit = gaiaPlayer->pObjectManager->units[i];
				if (!unit || unit->pUnitData->Class == -1)
				{
					continue;
				}
				FeatureManager::Get()->OnNeutralUnit(unit);
			}
		}

		for (int i = 1; i <= totalPlayers; i++)
		{
			Player* player = playerArray->playerData[i].player;
			if (!player)
			{
				continue;
			}
			if (skipLocalplayer && player == Engine::Get()->GetLocalPlayer())
			{
				continue;
			}
			FeatureManager::Get()->OnPlayerIteration(player, i);
			for (int j = 0; j < player->pObjectManager->Count; j++)
			{
				Unit* unit = player->pObjectManager->units[j];
				if (!unit || unit->pUnitData->Class == -1)
				{
					continue;
				}
				FeatureManager::Get()->OnUnitIteration(unit, player, i);
			}
		}

		Renderer::Get()->EndScene();

		ImGui::SetNextWindowBgAlpha(0.8f);
		if (openOverlay)
		{
			__try
			{
				if (ImGui::Begin("Age of Empires 2 DE", &openOverlay, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
				{
					if (ImGui::TreeNode("Debug"))
					{
						ImGui::Text("World %p", world);
						ImGui::Text("Map %p tilesize %d", world->pMap, world->pMap->GetTileSize());
						ImGui::Text("Localplayer %p", Engine::Get()->GetLocalPlayer());
						ImGui::Text("PlayerArray %p", playerArray);
						ImGui::Text("totalPlayers %d", totalPlayers);
						ImGui::Text("ScreenPos %p %f %f %f", mainScreen->pGameScreen->pMainView, mainScreen->pGameScreen->pMainView->ScreenPosX, mainScreen->pGameScreen->pMainView->ScreenPosY, mainScreen->pGameScreen->pMainView->ScreenPosZ);
						ImGui::TreePop();
					}
					ImGui::Separator();
					ImGui::Text("Player Information");
					for (int i = 0; i <= totalPlayers; i++)
					{
						Player* currentPlayer = playerArray->playerData[i].player;
						if (skipLocalplayer && currentPlayer == Engine::Get()->GetLocalPlayer())
						{
							continue;
						}
						createPlayerTreeNode(currentPlayer, i);
					}
					FeatureManager::Get()->OnMenuMainWindow();
					ImGui::Separator();
					ImGui::Checkbox("Skip localplayer", &skipLocalplayer);
					ImGui::Separator();
					ImGui::Separator();
					if(ImGui::Button("Save Config"))
					{
						FeatureManager::Get()->SaveConfig();
					}
					ImGui::SameLine();
					if (ImGui::Button("Load Config"))
					{
						FeatureManager::Get()->LoadConfig();
					}
				}
			}
			__finally
			{
				ImGui::End();
			}
		}
	}
	__except (1)
	{
		if (Renderer::Get()->inFrame)
		{
			Renderer::Get()->EndScene();
		}
	}
}

void Core::OnShutdown()
{
	onCreateUnitHook.Unhook();
}
