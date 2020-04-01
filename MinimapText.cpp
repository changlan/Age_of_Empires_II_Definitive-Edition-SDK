


#include "MinimapText.h"

#include "Engine.h"
#include "Sdk.h"
#include "Renderer.h"
#include "Utility.h"
#include "Offsets.h"

#include "MidfunctionHook.h"
#include "Patcher.h"

#include <map>

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

	std::string woodString = std::to_string((player->pResources->wood));
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

void MinimapText::OnInitialise()
{
	hookEnabled = &enabled;

	int64_t base = (int64_t)GetModuleHandle(NULL);

	Patcher patcher;

	//74 7F 48 8D 4B 01 48 85 C9 74 59   + 14
	//Patch usage of short string optimizaation (playernames <= 15)
	//patcher.NOPBytes((BYTE*)(base + 0xA426EE), 6);

	//74 7F 48 8D 4B 01 48 85 C9 74 59   + 18
	//Increase space allocated for playernames to 0x120 bytes so we can write as much as we want to on screen
	//Patcher().Patch((BYTE*)(base + 0xA426F5), (int32_t)0x120);

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