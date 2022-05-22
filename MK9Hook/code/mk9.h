#pragma once
#include "GameInfo.h"

#define GFG_GAME_INFO  0xE89B70 

#define MK9HOOK_VERSION "0.3.1"

enum  PLAYER_NUM
{
	INVALID_PLAYER_NUM = -1,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
	CPU_PLAYER,
	NOT_CPU_PLAYER,
	BACKGROUND_PLAYER
};

struct FVector
{
	float X;
	float Y;
	float Z;
};


struct FRotator {
	int Pitch;
	int Yaw;
	int Roll;
};


int	  GetInfo(PLAYER_NUM plr);
int	  GetObj(PLAYER_NUM plr);

void  SetCharacter(PLAYER_NUM plr, int unk, char* name);
void  SetStage(const char* stage);

void  SetCharacterMeter(PLAYER_NUM plr, float meter);
void  SetCharacterLife(PLAYER_NUM plr, float health);

void  SetCharacterScale(PLAYER_NUM plr, FVector* scale);
void  SetCharacterSpeed(PLAYER_NUM plr, float speed);

void  SetCharacterDamageScale(PLAYER_NUM plr, float value);

void  RunCharacterScript(PLAYER_NUM plr, MKScript* script, int function);

char* GetCharacterName(PLAYER_NUM plr);
void  GetCharacterPosition(PLAYER_NUM plr, FVector* pos);

void  SetGameSpeed(float speed);

bool IsNPC(const char* name);
bool IsBoss(const char* name);

void AddKoins(int amount);



namespace MK9Hooks {
	void  HookProcessStuff();
	void  HookLoadPlayerVersusScreen(int len, char* buf, char* format, char* charName, char* texture);

	void  SetupFight();

}