#pragma once
// Generated using ReClass 2016
#include <cstdint>

struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
};

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
};


// Generated using ReClass 2016

class World;
class pWorld;
class Map;
class PlayerArray;
class MainScreen;
class GameScreen;
class MainView;
class ObjectManager;
class Player;


enum class EnumUnitDataClass : int16_t //From Age of Empires 2013
{
	InvalidClass = -1,
	Archer = 0,
	Artifact = 1,
	TradeBoat = 2,
	Building = 3,
	Civilian = 4,
	OceanFish = 5,
	Infantry = 6,
	BerryBush = 7,
	StoneMine = 8,
	PreyAnimal = 9,
	PredatorAnimal = 10,
	Miscellaneous = 11,
	Cavalry = 12,
	SiegeWeapon = 13,
	Terrain = 14,
	Tree = 15,
	TreeStump = 16,
	Healer = 17,
	Monk = 18,
	TradeCart = 19,
	TransportBoat = 20,
	FishingBoat = 21,
	Warship = 22,
	Conquistador = 23,
	WarElephant = 24,
	Hero = 25,
	ElephantArcher = 26,
	Wall = 27,
	Phalanx = 28,
	DomesticAnimal = 29,
	Flag = 30,
	DeepSeaFish = 31,
	GoldMine = 32,
	ShoreFish = 33,
	Cliff = 34,
	Petard = 35,
	CavalryArcher = 36,
	Doppelganger = 37,
	Bird = 38,
	Gate = 39,
	SalvagePile = 40,
	ResourcePile = 41,
	Relic = 42,
	MonkWithRelic = 43,
	HandCannoneer = 44,
	TwoHandedSwordsman = 45,
	Pikeman = 46,
	Scout = 47,
	OreMine = 48,
	Farm = 49,
	Spearman = 50,
	PackedUnit = 51,
	Tower = 52,
	BoardingBoat = 53,
	UnpackedSiegeUnit = 54,
	Ballista = 55,
	Raider = 56,
	CavalryRaider = 57,
	Livestock = 58,
	King = 59,
	MiscBuilding = 60,
	ControlledAnimal = 61
};

class PathfindingSystem
{
public:
	World* GetWorld()
	{
		return *reinterpret_cast<World**>((uint64_t)this + 0x18);
	}
};

class Resources
{
public:
	float food; //0x0000 
	float wood; //0x0004 
	float stone; //0x0008 
	float gold; //0x000C 
	float popSpaceLeft; //0x0010 

}; //Size=0x00C8

class Player
{
public:
	char pad_0x0000[0x28]; //0x0000
	ObjectManager* pObjectManager; //0x0028 
	char pad_0x0030[0x40]; //0x0030
	Resources* pResources; //0x0070 
	char pad_0x0078[0xE0]; //0x0078
	int* pColor; //0x0158 
	char pad_0x0160[0x18]; //0x0160
	float xScreenPos; //0x0178 
	float yScreenPos; //0x017C 
	char pad_0x0180[0x9218]; //0x0180
	char* name; //0x9398 

	void SetCameraPosition(Vector2 pos)
	{
		xScreenPos = pos.x;
		yScreenPos = pos.y;
	}

	void SetCameraPosition(Vector3 pos)
	{
		xScreenPos = pos.x;
		yScreenPos = pos.y;
	}

}; //Size=0x93A0

class World
{
public:
	char pad_0x0000[0x80]; //0x0000
	__int32 gameTime; //0x0080 
	char pad_0x0084[0x1C]; //0x0084
	Map* pMap; //0x00A0 
	char pad_0x00A8[0xB0]; //0x00A8
	float camX; //0x0158 
	float camY; //0x015C 
	char pad_0x0160[0x140]; //0x0160
	PlayerArray* pPlayerArray; //0x02A0 

}; //Size=0x02A8

class pWorld
{
public:
	World* pWorld; //0x0000 

}; //Size=0x0008

class Map
{
public:
	int32_t GetTileSize()
	{
		static int32_t tileOffset = 0x5B38;
		return *reinterpret_cast<int32_t*>((int64_t)this + tileOffset);
	}

}; //Size=0x5CC8

class MainScreen
{
public:
	GameScreen* pGameScreen; //0x0000 
	char pad_0x0008[0x38]; //0x0008

}; //Size=0x0040

class GameScreen
{
public:
	char pad_0x0000[0x48]; //0x0000
	__int32 mouseX; //0x0048 
	__int32 mosueY; //0x004C 
	char pad_0x0050[0x5C]; //0x0050
	__int32 ScreenResX; //0x00AC 
	__int32 ScreenResX2; //0x00B0 
	__int32 ScreenResY; //0x00B4 
	__int32 ScreenResY2; //0x00B8 
	char pad_0x00BC[0xD4]; //0x00BC
	MainView* pMainView; //0x0190 
	char pad_0x0198[0x30]; //0x0198

}; //Size=0x01C8

class MainView
{
public:
	char pad_0x0000[0x2C0]; //0x0000
	float ScreenPosX; //0x02C0 
	float ScreenPosY; //0x02C4 
	float ScreenPosZ; //0x02C8 

}; //Size=0x02CC



class UnitData
{
public:
	char pad_0x0000[0x20]; //0x0000
	__int16 Class; //0x0020 
	char pad_0x0022[0x26]; //0x0022
	__int16 unk; //0x0048 
	__int16 maxHp; //0x004A 
	char pad_0x004C[0x8]; //0x004C
	float collisionX; //0x0054 
	float collisionY; //0x0058 
	float collisionZ; //0x005C 
	char pad_0x0060[0x120]; //0x0060
	char* name; //0x0180 
}; //Size=0x0408


class Unit
{
public:
	char pad_0x0000[0x10]; //0x0000
	UnitData* pUnitData; //0x0010 
	Player* pOwner; //0x0018 
	char pad_0x0020[0x70]; //0x0020
	float fHealth; //0x0090 
	char pad_0x0094[0x4]; //0x0094
	Vector3 position;

	//When moving sadly height isnt set. When attack it works.
	Vector3* GetTargetPosition()
	{
		uint64_t actionList = *reinterpret_cast<uint64_t*>((uint64_t)this + 0x278);
		if (!actionList){return NULL;}
		uint64_t targetDataWrapper = *reinterpret_cast<uint64_t*>(actionList + 0x10);
		if (!targetDataWrapper) { return NULL; }
		uint64_t actionMoveTo = *reinterpret_cast<uint64_t*>(targetDataWrapper);
		if (!actionMoveTo) { return NULL; }
		return reinterpret_cast<Vector3*>(actionMoveTo + 0x38);
	}

	

}; //Size=0x0250

class ObjectManager
{
public:
	char pad_0x0000[0x8]; //0x0000
	Unit** units; //0x0008 
	__int32 Count; //0x0010 

}; //Size=0x0018


class PlayerData
{
public:
	Player* player; //0x0000
	void* unk; //0x0008
};

class PlayerArray
{
public:
	PlayerData playerData[8]; //0x0008
}; //Size: 0x0074

class PlayerName
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044