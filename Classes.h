#pragma once
// Generated using ReClass 2016
#include <cstdint>

#include "Engine.h"

struct Vector4 {
  float x;
  float y;
  float z;
  float w;

  Vector4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }
};

struct Vector3 {
  float x;
  float y;
  float z;

  Vector3() {
    x = 0;
    y = 0;
    z = 0;
  }

  Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
};

struct Vector2 {
  float x;
  float y;

  Vector2() {
    x = 0;
    y = 0;
  }

  Vector2(float x, float y) {
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

enum class EnumUnitDataClass : int16_t  // From Age of Empires 2013
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

class PathfindingSystem {
 public:
  World* GetWorld() {
    return *reinterpret_cast<World**>((uint64_t)this + 0x18);
  }
};

class Resources {
 public:
  float food;             // 0x0000
  float wood;             // 0x0004
  float stone;            // 0x0008
  float gold;             // 0x000C
  float popSpaceLeft;     // 0x0010
  char pad_0x0014[0x4];   // 0x0014
  float age;              // 0x0018
  char pad_0x001C[0x10];  // 0x001C
  float currentPop;       // 0x002C
  char pad_0x0030[0x64];  // 0x0030
  float villagerCount;    // 0x0094

};  // Size=0x0098

class Player {
 public:
  char pad_0x0000[0x28];          // 0x0000
  ObjectManager* pObjectManager;  // 0x0028
  char pad_0x0030[0x40];          // 0x0030
  Resources* pResources;          // 0x0070
  char pad_0x0078[0xE0];          // 0x0078
  int* pColor;                    // 0x0158
  char pad_0x0160[0x18];          // 0x0160
  float xScreenPos;               // 0x0178
  float yScreenPos;               // 0x017C
  char pad_0x0180[0x9210];        // 0x0170
  char* name;                     // 0x9390

  void SetCameraPosition(Vector2 pos) {
    xScreenPos = pos.x;
    yScreenPos = pos.y;
  }

  void SetCameraPosition(Vector3 pos) {
    xScreenPos = pos.x;
    yScreenPos = pos.y;
  }

  bool IsAllied(Player* other) {
    int32_t playerNumber = Engine::Get()->GetPlayerNumber(other);
    int32_t* diplomacy = (int32_t*)((int64_t)this + 0xd0);
    return *(diplomacy + playerNumber) == 2;
  }

  bool IsEnemy(Player* other) {
    int32_t playerNumber = Engine::Get()->GetPlayerNumber(other);
    int32_t* diplomacy = (int32_t*)((int64_t)this + 0xd0);
    return *(diplomacy + playerNumber) == 4;
  }

  bool IsNeutral(Player* other) {
    int32_t playerNumber = Engine::Get()->GetPlayerNumber(other);
    int32_t* diplomacy = (int32_t*)((int64_t)this + 0xd0);

    // TODO is 0 correct?
    return *(diplomacy + playerNumber) == 1;
  }

};  // Size=0x93A0

class World {
 public:
  char pad_0x0000[0x80];      // 0x0000
  __int32 gameTime;           // 0x0080
  char pad_0x0084[0x1C];      // 0x0084
  Map* pMap;                  // 0x00A0
  char pad_0x00A8[0xB0];      // 0x00A8
  float camX;                 // 0x0158
  float camY;                 // 0x015C
  char pad_0x0160[0x148];     // 0x0168
  PlayerArray* pPlayerArray;  // 0x02A8

};  // Size=0x02A8

class pWorld {
 public:
  World* pWorld;  // 0x0000

};  // Size=0x0008

class Map {
 public:
  int32_t GetTileSize() {
    return *reinterpret_cast<int32_t*>((int64_t)this + 0x5B38);
  }

};  // Size=0x5CC8

class CommHandler {
 public:
  char pad_0x0000[0xC08];      // 0x0000
  unsigned char isGamePaused;  // 0x0C08
};

class Game {
 public:
  char pad_0x0000[0x298];     // 0x0000
  CommHandler* pCommHandler;  // 0x0298
  char pad_0x02A0[0x1A8];     // 0x02A0
};                            // Size=0x0448

class MainScreen {
 public:
  GameScreen* pGameScreen;  // 0x0000
  char pad_0x0008[0x38];    // 0x0008

};  // Size=0x0040

class GameScreen {
 public:
  char pad_0x0000[0x48];  // 0x0000
  __int32 mouseX;         // 0x0048
  __int32 mosueY;         // 0x004C
  char pad_0x0050[0x5C];  // 0x0050
  __int32 ScreenResX;     // 0x00AC
  __int32 ScreenResX2;    // 0x00B0
  __int32 ScreenResY;     // 0x00B4
  __int32 ScreenResY2;    // 0x00B8
  char pad_0x00BC[0xD4];  // 0x00BC
  MainView* pMainView;    // 0x0190
  char pad_0x0198[0x30];  // 0x0198
};                        // Size=0x01C8

class MainView {
 public:
  char pad_0x0000[0x2C0];  // 0x0000
  float ScreenPosX;        // 0x02C0
  float ScreenPosY;        // 0x02C4
  float ScreenPosZ;        // 0x02C8

};  // Size=0x02CC

class UnitData {
 public:
  char* GetName() {
    return *reinterpret_cast<char**>(*(uint64_t*)this + 0x848);
  }

  Vector3 GetCollision() { return *(Vector3*)(*(uint64_t*)this + 0x718); }
};

class Unit {
 private:
  float GetPosX() {
    int32_t position = *reinterpret_cast<int64_t*>((uint64_t)this + 0x1a0) ^
                       0x187F64ADC21CDE88 ^ 0x4F019E376DDAD1E5;
    return *(float*)(&position);
  }

  float GetPosY() {
    int32_t position = *reinterpret_cast<int64_t*>((uint64_t)this + 0x308) ^
                       0x51E534524D81CFA6;
    return *(float*)(&position);
  }

  float GetPosZ() {
    int32_t position = (*reinterpret_cast<int64_t*>((uint64_t)this + 0x3f8) -
                        0x17258AE0D9C58D92) ^
                       0x78E0AFEAF822FC61;
    return *(float*)(&position);
  }

 public:
  UnitData* GetUnitData() {
    return reinterpret_cast<UnitData*>((uint64_t)this + 0x10);
  }

  Player* GetOwner() {
    return *reinterpret_cast<Player**>((uint64_t)this + 0x18);
  }

  Vector3 GetPosition() { return Vector3(GetPosX(), GetPosY(), GetPosZ()); }

  float GetHealth() {
    int32_t position = (*reinterpret_cast<int64_t*>((uint64_t)this + 0x100) +
                        0x16F41E044E9AB282 - 0x3E3A7DDCA209C1DB);
    return *(float*)(&position);
  }

  Vector3* GetTargetPosition() {
    uint64_t actionList = *reinterpret_cast<uint64_t*>((uint64_t)this + 0x648);
    if (!actionList) {
      return NULL;
    }
    uint64_t targetDataWrapper =
        *reinterpret_cast<uint64_t*>(actionList + 0x10);
    if (!targetDataWrapper) {
      return NULL;
    }
    uint64_t actionMoveTo = *reinterpret_cast<uint64_t*>(targetDataWrapper);
    if (!actionMoveTo) {
      return NULL;
    }
    return reinterpret_cast<Vector3*>(actionMoveTo + 0x38);
  }
};

class ObjectManager {
 public:
  char pad_0x0000[0x8];  // 0x0000
  Unit** units;          // 0x0008
  __int32 Count;         // 0x0010

};  // Size=0x0018

class PlayerData {
 public:
  Player* player;  // 0x0000
  void* unk;       // 0x0008
};

class PlayerArray {
 public:
  PlayerData playerData[8];  // 0x0008
};                           // Size: 0x0074

class PlayerName {
 public:
  char pad_0000[68];  // 0x0000
};                    // Size: 0x0044