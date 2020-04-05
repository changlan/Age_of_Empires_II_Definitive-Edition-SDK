#include "CastleManager.h"

#include "ThreadsafeQueue.h"


#include "Engine.h"
#include "SDK.h"
#include "Renderer.h"

bool warningEnabled = true;
bool warnTeam = false;
bool warnAll = false;
int notification = 0;

ThreadSafeQueue<std::string> teamMessages;
ThreadSafeQueue<std::string> allMessages;

void CastleManager::OnUnitCreated(Unit* unit)
{
	if (!warningEnabled)
	{
		return;
	}
	Player* owningPlayer = unit->pOwner;
	if (!owningPlayer || owningPlayer == Engine::Get()->GetLocalPlayer())
	{
		return;
	}
	
	if (strcmp("CSTL", unit->pUnitData->name) == 0)
	{
		std::string message = std::string(owningPlayer->name) + " is building a castle!";
		const char* charMessage = message.c_str();

		switch (notification)
		{
		case 0:
			Engine::Get()->PrintNotification(charMessage);
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