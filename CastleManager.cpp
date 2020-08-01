#include "CastleManager.h"

#include "ThreadsafeQueue.h"


#include "Engine.h"
#include "SDK.h"
#include "Renderer.h"
#include "Config.h"

bool warningEnabled = true;
int notification = 0;

ThreadSafeQueue<std::string> localMessages;
ThreadSafeQueue<std::string> teamMessages;
ThreadSafeQueue<std::string> allMessages;

void CastleManager::LoadConfig()
{
	Config* config = Config::Get();
	notification = config->ReadInt("CastleManager", "notification");
	warningEnabled = config->ReadInt("CastleManager", "warningEnabled");
}

void CastleManager::SaveConfig()
{
	Config* config = Config::Get();
	config->Write<int>("CastleManager", "warningEnabled", warningEnabled);
	config->Write<int>("CastleManager", "notification", notification);
}

void CastleManager::OnUnitIteration(Unit* unit, Player* player, int playerIndex)
{
	
}

void CastleManager::OnUnitCreated(Unit* unit)
{
	if (!warningEnabled)
	{
		return;
	}
	Player* owningPlayer = unit->GetOwner();
	if (!owningPlayer /*|| owningPlayer == Engine::Get()->GetLocalPlayer()*/)
	{
		return;
	}
	
	if (strcmp("CSTL", unit->GetUnitData()->GetName()) == 0)
	{
		std::string message = std::string(owningPlayer->name) + " is building a castle!";
		const char* charMessage = message.c_str();

		switch (notification)
		{
		case 0:
			localMessages.push(message);
			break;
		case 1:
			teamMessages.push(message);
			break;
		case 2:
			allMessages.push(message);
			break;
		default:
			break;
		}
	}
}

void CastleManager::OnMenuMainWindow()
{
	if (!localMessages.isEmpty())
	{
		std::string message;
		localMessages.pop(message);
		Engine::Get()->PrintNotification(message.c_str());
	}

	if (!teamMessages.isEmpty())
	{
		std::string message;
		teamMessages.pop(message);
		Engine::Get()->SendChat(message.c_str(), true);
	}

	if (!allMessages.isEmpty())
	{
		std::string message;
		allMessages.pop(message);
		Engine::Get()->SendChat(message.c_str(), false);
	}
	
	ImGui::Separator();
	ImGui::Text("Castle Manager");
	ImGui::Checkbox("Warning", &warningEnabled);
	ImGui::Text("Notification");
	ImGui::SameLine();
	ImGui::RadioButton("Local", &notification, 0);
	ImGui::SameLine();
	ImGui::RadioButton("Team", &notification, 1);
	ImGui::SameLine();
	ImGui::RadioButton("All", &notification, 2);
	ImGui::Separator();
}

void CastleManager::OnDraw()
{
	/*if (strcmp("CSTL", unit->pUnitData->name) == 0)
	{
		Vector2 screenPos = Engine::Get()->worldToScreen(unit->position);
		int screenResX = Engine::Get()->GetMainScreen()->pGameScreen->ScreenResX;
		int screenResY = Engine::Get()->GetMainScreen()->pGameScreen->ScreenResY;
		Renderer::Get()->RenderLine(ImVec2(screenResX / 2, screenResY / 2), ImVec2(screenPos.x, screenPos.y), 0xffffffff, 2);
	}*/
}

void CastleManager::OnPlayerIteration(Player* player, int playerIndex)
{
	
}
