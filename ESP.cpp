#include "ESP.h"

#include "Sdk.h"
#include "Renderer.h"
#include "Engine.h"

#include <math.h>

uint32_t ESP::colors_hex[8] = { 0xff0000ff, 0xffff0000,0xff00ff00,0xffffff00,0xff00ffff,0xffff00ff,0xffffffff,0xffffb400 };

void ESP::DrawBox(Unit* unit, int32_t color, bool drawName = false)
{
	Vector3 one3 = unit->position;
	one3.x -= unit->pUnitData->collisionX;
	one3.y -= unit->pUnitData->collisionY;
	Vector2 one = Engine::Get()->worldToScreen(one3);

	Vector3 two3 = unit->position;
	two3.x += unit->pUnitData->collisionX;
	two3.y += unit->pUnitData->collisionY;
	Vector2 two = Engine::Get()->worldToScreen(two3);

	Vector3 three3 = unit->position;
	three3.x -= unit->pUnitData->collisionX;
	three3.y += unit->pUnitData->collisionY;
	Vector2 three = Engine::Get()->worldToScreen(three3);

	Vector3 four3 = unit->position;
	four3.x += unit->pUnitData->collisionX;
	four3.y -= unit->pUnitData->collisionY;
	Vector2 four = Engine::Get()->worldToScreen(four3);

	ImVec2 ivOne = ImVec2(one.x, one.y);
	ImVec2 ivTwo = ImVec2(two.x, two.y);
	ImVec2 ivThree = ImVec2(three.x, three.y);
	ImVec2 ivFour = ImVec2(four.x, four.y);


	Renderer::Get()->RenderRect(ivOne, ivFour, ivTwo, ivThree, color);

	if (drawName)
	{
		Vector3 textPos = unit->position;
		Vector2 screenTextPos = Engine::Get()->worldToScreen(textPos);
		ImVec2 ivTextPos = ImVec2(screenTextPos.x, screenTextPos.y);
		Renderer::Get()->RenderText(unit->pUnitData->name, ivTextPos, 16, color, false);
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

void ESP::DrawCircle(Unit* unit, int radius, int32_t color, int smoothness = 16, int thickness = 1, bool drawName = false)
{
	static const float PI = 3.14159265358979323846;
	int32_t tileSize = Engine::Get()->GetWorld()->pMap->GetTileSize();
	Vector3 center = unit->position;

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
	Renderer::Get()->RenderLine(screeenPoints[0], screeenPoints[screeenPoints.size()-1], color, thickness);
	if (drawName)
	{
		Vector2 screenTextPos = Engine::Get()->worldToScreen(center);
		ImVec2 ivTextPos = ImVec2(screenTextPos.x, screenTextPos.y);
		Renderer::Get()->RenderText(unit->pUnitData->name, ivTextPos, 16, color, false);
	}
}

void ESP::OnUnitIteration(Unit* unit, Player* player, int playerIndex)
{

	if (playerUnitEsp[playerIndex])
	{
		if (strcmp(unit->pUnitData->name, "FLARE") == 0)
		{
			return; //Dont display annoying flares that Bots use
		}

		if (siegeImpactLocation)
		{
			if (std::string(unit->pUnitData->name).find("Projectile Scorpion") != std::string::npos)
			{
				Vector3* destination = unit->GetTargetPosition();
				if (destination)
				{
					Vector2 screenDestinationPos = Engine::Get()->worldToScreen(*destination);
					Renderer::Get()->RenderCircleFilled(ImVec2(screenDestinationPos.x, screenDestinationPos.y), 10, colors_hex[*player->pColor] & 0x77ffffff);
				}
			}

			if (std::string(unit->pUnitData->name).find("Projectile Mangonel") != std::string::npos)
			{
				Vector3* destination = unit->GetTargetPosition();
				if (destination)
				{
					Vector2 screenDestinationPos = Engine::Get()->worldToScreen(*destination);
					Renderer::Get()->RenderCircleFilled(ImVec2(screenDestinationPos.x, screenDestinationPos.y), 10, colors_hex[*player->pColor] & 0x77ffffff);
				}
			}

			if (std::string(unit->pUnitData->name).find("Projectile Trebuchet") != std::string::npos)
			{
				Vector3* destination = unit->GetTargetPosition();
				if (destination)
				{
					Vector2 screenDestinationPos = Engine::Get()->worldToScreen(*destination);
					Renderer::Get()->RenderCircleFilled(ImVec2(screenDestinationPos.x, screenDestinationPos.y), 30, colors_hex[*player->pColor] & 0x77ffffff);
				}
			}
		}

		if (unit->pUnitData->Class == (int16_t)EnumUnitDataClass::Miscellaneous)
		{
			return;
		}

		if (strcmp(unit->pUnitData->name, "CSTL") == 0)
		{
			DrawBox(unit, colors_hex[*player->pColor], true);
			return;
		}

		DrawBox(unit, colors_hex[*player->pColor], playerUnitNameEsp[playerIndex]);

		if (trebuchetESP && (std::string(unit->pUnitData->name).find("TREBU") != std::string::npos || std::string(unit->pUnitData->name).find("PTREB") != std::string::npos))
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
	if (gaiaEsp || goldESP || stoneESP)
	{
		std::string unitName = unit->pUnitData->name;
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

		if (!gaiaEsp)
		{
			return;
		}

		if (strcmp(unitName.c_str(), "FISHS") == 0 || strcmp(unitName.c_str(), "FISHX") == 0 ||
			strcmp(unitName.c_str(), "FISH1") == 0 || strcmp(unitName.c_str(), "FISH2") == 0 || 
			strcmp(unitName.c_str(), "FISH3") == 0 || strcmp(unitName.c_str(), "FISH4") == 0 ||
			strcmp(unitName.c_str(), "turtles") == 0)
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x400000ff);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
		}

		if (strcmp(unitName.c_str(), "BOARX") == 0 || strcmp(unitName.c_str(), "RHINO") == 0 ||
			strcmp(unitName.c_str(), "BOAR") == 0 || strcmp(unitName.c_str(), "BOARJ") == 0 || 
			strcmp(unitName.c_str(), "ZEBRA") == 0)
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x4000ff00);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
		}

		if (strcmp(unitName.c_str(), "DEERX") == 0 || strcmp(unitName.c_str(), "IBEX") == 0)
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x4000ffff);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
		}

		if (strcmp(unitName.c_str(), "SHEEPG") == 0 || strcmp(unitName.c_str(), "GOOSE") == 0 ||
			strcmp(unitName.c_str(), "PIG") == 0 || strcmp(unitName.c_str(), "LLAMAG") == 0 ||
			strcmp(unitName.c_str(), "Cow Black") == 0 || strcmp(unitName.c_str(), "Cow Brown") == 0 ||
			strcmp(unitName.c_str(), "Cow Black and White") == 0 || strcmp(unitName.c_str(), "BUFFALO") == 0 ||
			strcmp(unitName.c_str(), "TURKYG") == 0 || strcmp(unitName.c_str(), "Cow Black") == 0 ||
			strcmp(unitName.c_str(), "GOAT") == 0)
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x400000ff);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
		}


		if (strcmp(unitName.c_str(), "WOLFX") == 0 || strcmp(unitName.c_str(), "KOMODO") == 0 || 
			strcmp(unitName.c_str(), "GJAGR") == 0 || strcmp(unitName.c_str(), "SLEOPA") == 0 ||
			strcmp(unitName.c_str(), "BEAR") == 0 || strcmp(unitName.c_str(), "CROCO") == 0 ||
			strcmp(unitName.c_str(), "LION") == 0 || strcmp(unitName.c_str(), "TIGER") == 0)
		{
			Renderer::Get()->RenderCircleFilled(ImVec2(screenPos.x, screenPos.y), 20, 0x40ff0000);
			Renderer::Get()->RenderText(unitName, ImVec2(screenPos.x, screenPos.y), 16, 0xffffffff);
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
	ImGui::Text("Siege ESP");
	ImGui::Checkbox("Siege Impact", &siegeImpactLocation);
	ImGui::Checkbox("Trebuchet range", &trebuchetESP);
	ImGui::Separator();
	ImGui::Text("Resource ESP");
	ImGui::Checkbox("Gaia##ESP", &gaiaEsp);
	ImGui::SameLine();
	ImGui::Checkbox("Gold##ESP", &goldESP);
	ImGui::SameLine();
	ImGui::Checkbox("Stone##ESP", &stoneESP);
	ImGui::Separator();
}