#include "ESP.h"

#include "Sdk.h"
#include "Renderer.h"
#include "Engine.h"

#include <math.h>

#include "Config.h"

uint32_t ESP::colors_hex[8] = { 0xff0000ff, 0xffff0000,0xff00ff00,0xffffff00,0xff00ffff,0xffff00ff,0xffffffff,0xffffb400 };

void ESP::DrawBox(Unit* unit, int32_t color, bool drawName = false)
{
	Vector3 one3 = unit->GetPosition();
	one3.x -= unit->GetUnitData()->GetCollision().x;
	one3.y -= unit->GetUnitData()->GetCollision().y;
	Vector2 one = Engine::Get()->worldToScreen(one3);

	Vector3 two3 = unit->GetPosition();
	two3.x += unit->GetUnitData()->GetCollision().x;
	two3.y += unit->GetUnitData()->GetCollision().y;
	Vector2 two = Engine::Get()->worldToScreen(two3);

	Vector3 three3 = unit->GetPosition();
	three3.x -= unit->GetUnitData()->GetCollision().x;
	three3.y += unit->GetUnitData()->GetCollision().y;
	Vector2 three = Engine::Get()->worldToScreen(three3);

	Vector3 four3 = unit->GetPosition();
	four3.x += unit->GetUnitData()->GetCollision().x;
	four3.y -= unit->GetUnitData()->GetCollision().y;
	Vector2 four = Engine::Get()->worldToScreen(four3);

	ImVec2 ivOne = ImVec2(one.x, one.y);
	ImVec2 ivTwo = ImVec2(two.x, two.y);
	ImVec2 ivThree = ImVec2(three.x, three.y);
	ImVec2 ivFour = ImVec2(four.x, four.y);


	Renderer::Get()->RenderRect(ivOne, ivFour, ivTwo, ivThree, color);

	if (drawName)
	{
		Vector3 textPos = unit->GetPosition();
		Vector2 screenTextPos = Engine::Get()->worldToScreen(textPos);
		ImVec2 ivTextPos = ImVec2(screenTextPos.x, screenTextPos.y);
		Renderer::Get()->RenderText(std::string(unit->GetUnitData()->GetName()), ivTextPos, 16, color, false);
	}
}

void ESP::DrawBox(Vector3 position, Vector2 edgeSize, int32_t color)
{
	Vector3 one3 = position;
	one3.x -= edgeSize.x;
	one3.y -= edgeSize.y;
	Vector2 one = Engine::Get()->worldToScreen(one3);

	Vector3 two3 = position;
	two3.x += edgeSize.x;
	two3.y += edgeSize.y;
	Vector2 two = Engine::Get()->worldToScreen(two3);

	Vector3 three3 = position;
	three3.x -= edgeSize.x;
	three3.y += edgeSize.y;
	Vector2 three = Engine::Get()->worldToScreen(three3);

	Vector3 four3 = position;
	four3.x += edgeSize.x;
	four3.y -= edgeSize.y;
	Vector2 four = Engine::Get()->worldToScreen(four3);

	ImVec2 ivOne = ImVec2(one.x, one.y);
	ImVec2 ivTwo = ImVec2(two.x, two.y);
	ImVec2 ivThree = ImVec2(three.x, three.y);
	ImVec2 ivFour = ImVec2(four.x, four.y);


	Renderer::Get()->RenderRect(ivOne, ivFour, ivTwo, ivThree, color);
}

void ESP::DrawCircle(Unit* unit, int radius, int32_t color, int smoothness = 16, float thickness = 1.f, bool drawName = false)
{
	const float PI = 3.14159265358979323846f;
	int32_t tileSize = Engine::Get()->GetWorld()->pMap->GetTileSize();
	Vector3 center = unit->GetPosition();

	std::vector<ImVec2> screeenPoints;

	float angle = 0;
	for (int i = 0; i < smoothness; i++)
	{
		angle += (2 * PI) / smoothness;
		float x = (float)(radius * cos(angle) + center.x);
		float y = (float)(radius * sin(angle) + center.y);
		Vector2 screenPos = Engine::Get()->worldToScreen(Vector3(x, y, center.z));
		screeenPoints.push_back(ImVec2(screenPos.x, screenPos.y));
	}
	for (int i = 1; i < screeenPoints.size(); i++)
	{
		Renderer::Get()->RenderLine(screeenPoints[i], screeenPoints[i - 1], color, thickness);
	}
	Renderer::Get()->RenderLine(screeenPoints[0], screeenPoints[screeenPoints.size() - 1], color, thickness);
	if (drawName)
	{
		Vector2 screenTextPos = Engine::Get()->worldToScreen(center);
		ImVec2 ivTextPos = ImVec2(screenTextPos.x, screenTextPos.y);
		Renderer::Get()->RenderText(unit->GetUnitData()->GetName(), ivTextPos, 16, color, false);
	}
}

void ESP::LoadConfig()
{
	Config* config = Config::Get();
	siegeImpactLocation = config->ReadInt("ESP", "siegeImpactLocation");
	trebuchetESP = config->ReadInt("ESP", "trebuchetESP");
	gaiaESP = config->ReadInt("ESP", "gaiaESP");
	goldESP = config->ReadInt("ESP", "goldESP");
	stoneESP = config->ReadInt("ESP", "stoneESP");
}

void ESP::SaveConfig()
{
	Config* config = Config::Get();
	config->Write<int>("ESP", "siegeImpactLocation", siegeImpactLocation);
	config->Write<int>("ESP", "trebuchetESP", trebuchetESP);
	config->Write<int>("ESP", "gaiaESP", gaiaESP);
	config->Write<int>("ESP", "goldESP", goldESP);
	config->Write<int>("ESP", "stoneESP", stoneESP);
}


void ESP::OnUnitIteration(Unit* unit, Player* player, int playerIndex)
{
	if (playerUnitEsp[playerIndex])
	{
		if (!allyEsp && Engine::Get()->GetLocalPlayer()->IsAllied(player))
		{
			return;
		}

		if (!neutralEsp && Engine::Get()->GetLocalPlayer()->IsNeutral(player))
		{
			return;
		}

		if (!enemyEsp && Engine::Get()->GetLocalPlayer()->IsEnemy(player))
		{
			return;
		}
		if (strcmp(unit->GetUnitData()->GetName(), "FLARE") == 0)
		{
			return; //Dont display annoying flares that Bots use
		}

		if (siegeImpactLocation)
		{
			if (std::string(unit->GetUnitData()->GetName()).find("Projectile Scorpion") != std::string::npos)
			{
				Vector3* destination = unit->GetTargetPosition();
				if (destination)
				{
					Vector2 screenDestinationPos = Engine::Get()->worldToScreen(*destination);
					Renderer::Get()->RenderCircleFilled(ImVec2(screenDestinationPos.x, screenDestinationPos.y), 10, colors_hex[*player->pColor] & 0x77ffffff);
				}
			}

			if (std::string(unit->GetUnitData()->GetName()).find("Projectile Mangonel") != std::string::npos)
			{
				Vector3* destination = unit->GetTargetPosition();
				if (destination)
				{
					Vector2 screenDestinationPos = Engine::Get()->worldToScreen(*destination);
					Renderer::Get()->RenderCircleFilled(ImVec2(screenDestinationPos.x, screenDestinationPos.y), 10, colors_hex[*player->pColor] & 0x77ffffff);
				}
			}

			if (std::string(unit->GetUnitData()->GetName()).find("Projectile Trebuchet") != std::string::npos)
			{
				Vector3* destination = unit->GetTargetPosition();
				if (destination)
				{
					Vector2 screenDestinationPos = Engine::Get()->worldToScreen(*destination);
					Renderer::Get()->RenderCircleFilled(ImVec2(screenDestinationPos.x, screenDestinationPos.y), 30, colors_hex[*player->pColor] & 0x77ffffff);
				}
			}
		}

		/*if (unit->pUnitData->Class == (int16_t)EnumUnitDataClass::Miscellaneous)
		{
			return;
		}
		*/
		if (strcmp(unit->GetUnitData()->GetName(), "CSTL") == 0)
		{
			DrawBox(unit, colors_hex[*player->pColor], true);
			return;
		}

		DrawBox(unit, colors_hex[*player->pColor], playerUnitNameEsp[playerIndex]);

		if (trebuchetESP && (std::string(unit->GetUnitData()->GetName()).find("TREBU") != std::string::npos || std::string(unit->GetUnitData()->GetName()).find("PTREB") != std::string::npos))
		{
			DrawCircle(unit, 16, colors_hex[*player->pColor], 100, 2, true);
		}

		if (playerUnitDestinationEsp[playerIndex])
		{
			Vector3* targetPosition = unit->GetTargetPosition();
			if (!targetPosition || targetPosition->x <= 0 || targetPosition->y <= 0) { return; }

			Vector2 screenPos = Engine::Get()->worldToScreen(unit);
			Vector2 screenTargetPos = Engine::Get()->worldToScreen(*targetPosition);
			Renderer::Get()->RenderLine(ImVec2(screenPos.x, screenPos.y), ImVec2(screenTargetPos.x, screenTargetPos.y), colors_hex[*player->pColor]);
		}
	}
}


void ESP::OnMenuPlayerTreenode(Player* player, int playerIndex)
{
	if (ImGui::TreeNode("ESP"))
	{
		ImGui::PushItemWidth(100);
		ImGui::Checkbox("Unit", &playerUnitEsp[playerIndex]);
		ImGui::Checkbox("Unit Destination", &playerUnitDestinationEsp[playerIndex]);
		ImGui::TreePop();
	}
}

void ESP::OnNeutralUnit(Unit* unit)
{
	if (gaiaESP || goldESP || stoneESP)
	{
		std::string unitName = unit->GetUnitData()->GetName();
		Vector2 screenPos = Engine::Get()->worldToScreen(unit);

		if (goldESP && strcmp(unitName.c_str(), "GOLDM") == 0)
		{
			DrawBox(unit, 0xFFFFD700);
			return;
		}
		if (stoneESP && strcmp(unitName.c_str(), "STONM") == 0)
		{
			DrawBox(unit, 0xFF888c8d);
			return;
		}
		if (stoneESP && strcmp(unitName.c_str(), "FORAG") == 0 || stoneESP && strcmp(unitName.c_str(), "FORAGM") == 0)
		{
			DrawBox(unit, 0xff00ff00);
			return;
		}

		if (!gaiaESP)
		{
			return;
		}

		if (std::find(namesFish.begin(), namesFish.end(), unitName) != namesFish.end())
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x400000ff);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
			return;
		}

		if (std::find(namesHeavyFood.begin(), namesHeavyFood.end(), unitName) != namesHeavyFood.end())
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x4000ff00);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
			return;
		}

		if (std::find(namesLighthuntable.begin(), namesLighthuntable.end(), unitName) != namesLighthuntable.end())
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x4000ffff);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
			return;
		}

		if (std::find(namesLightFood.begin(), namesLightFood.end(), unitName) != namesLightFood.end())
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x400000ff);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
			return;
		}

		if (std::find(namesDangerousAnimal.begin(), namesDangerousAnimal.end(), unitName) != namesDangerousAnimal.end())
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x40ff0000);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
			return;
		}

		if (strcmp(unitName.c_str(), "RELIC") == 0)
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 50, 0x40ffffff);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
		}
	}
}

void ESP::OnMenuMainWindow()
{
	ImGui::Separator();
	ImGui::Text("Diplomacy ESP");
	ImGui::Checkbox("Ally", &allyEsp);
	ImGui::SameLine();
	ImGui::Checkbox("Neutral", &neutralEsp);
	ImGui::SameLine();
	ImGui::Checkbox("Enemy", &enemyEsp);

	ImGui::Text("Siege ESP");
	//ImGui::Checkbox("Siege Impact", &siegeImpactLocation);
	ImGui::Checkbox("Trebuchet range", &trebuchetESP);
	ImGui::Separator();
	ImGui::Text("Resource ESP");
	ImGui::Checkbox("Gaia##ESP", &gaiaESP);
	ImGui::SameLine();
	ImGui::Checkbox("Gold##ESP", &goldESP);
	ImGui::SameLine();
	ImGui::Checkbox("Stone##ESP", &stoneESP);
	ImGui::Separator();
}