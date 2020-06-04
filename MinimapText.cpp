#include "MinimapText.h"

#include "Engine.h"
#include "Sdk.h"
#include "Renderer.h"
#include "Utility.h"
#include "Offsets.h"

#include "MidfunctionHook.h"
#include "Patcher.h"

#include <map>

#include "Config.h"

#pragma warning( disable : 4244 )

MidfunctionHook minimapHook;
bool* hookEnabled;
bool displayWood = false;
bool displayFood = false;
bool displayGold = true;
bool displayStone = false;
bool displayPopulation = false;


void __fastcall minimapProxy(Registers* registers)
{
	if (!*hookEnabled)
	{
		return;
	}
	if (!displayWood && !displayFood && !displayGold && !displayStone && !displayPopulation)
	{
		return;
	}

	Player* player = Engine::Get()->GetPlayerByName((char*)registers->rdi);
	if (!player)
	{
		return;
	}

	if (!player->pResources)
	{
		return;
	}

	std::string woodString = std::to_string(((int)player->pResources->wood));
	std::string foodString = std::to_string((int)player->pResources->food);
	std::string goldString = std::to_string((int)player->pResources->gold);
	std::string stoneString = std::to_string((int)player->pResources->stone);
	std::string populationString = std::to_string((int)player->pResources->currentPop) + "/" + std::to_string((int)player->pResources->currentPop + (int)player->pResources->popSpaceLeft);

	std::string newName = std::string(player->name) + " -";
	if (displayWood)
	{
		newName += " Wood: " + woodString;
	}
	if (displayFood)
	{
		newName += " Food: " + foodString;
	}
	if (displayGold)
	{
		newName += " Gold: " + goldString;
	}
	if (displayStone)
	{
		newName += " Stone: " + stoneString;
	}
	if (displayPopulation)
	{
		newName += " Pop: " + populationString;
	}
	MidfunctionHook::OverwriteRegister(registers->rsp, Register::RDI, (int64_t)newName.c_str());
}

void MinimapText::LoadConfig()
{
	Config* config = Config::Get();
	*hookEnabled = config->ReadInt("MinimapText", "hookEnabled");
	displayWood = config->ReadInt("MinimapText", "displayWood");
	displayFood = config->ReadInt("MinimapText", "displayFood");
	displayGold = config->ReadInt("MinimapText", "displayGold");
	displayStone = config->ReadInt("MinimapText", "displayStone");
	displayPopulation = config->ReadInt("MinimapText", "displayPopulation");
}

void MinimapText::SaveConfig()
{
	Config* config = Config::Get();
	config->Write<int>("MinimapText", "hookEnabled", *hookEnabled);
	config->Write<int>("MinimapText", "displayWood", displayWood);
	config->Write<int>("MinimapText", "displayFood", displayFood);
	config->Write<int>("MinimapText", "displayGold", displayGold);
	config->Write<int>("MinimapText", "displayStone", displayStone);
	config->Write<int>("MinimapText", "displayPopulation", displayPopulation);
}

void MinimapText::OnInitialise()
{
	hookEnabled = &enabled;

	minimapHook.Hook((BYTE*)(int64_t)GetModuleHandle(NULL) + Offsets::minimapHookOffset, (BYTE*)minimapProxy, 14);
}

void MinimapText::OnShutdown()
{
	minimapHook.Unhook();
}

void MinimapText::OnMenuMainWindow()
{
	ImGui::Separator();
	ImGui::Checkbox("Minimap Ressource Information", &enabled);
	ImGui::Checkbox("Wood##Minimap", &displayWood);
	ImGui::SameLine();
	ImGui::Checkbox("Food##Minimap", &displayFood);
	ImGui::SameLine();
	ImGui::Checkbox("Gold##Minimap", &displayGold);
	ImGui::SameLine();
	ImGui::Checkbox("Stone##Minimap", &displayStone);
	ImGui::SameLine();
	ImGui::Checkbox("Population##Minimap", &displayPopulation);
	ImGui::Separator();
}