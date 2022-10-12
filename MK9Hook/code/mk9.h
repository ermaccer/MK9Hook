#pragma once
#include "GameInfo.h"
#include "unreal/FVector.h"
#include "unreal/SkeletalMeshComponent.h"
#include "unreal/FRotator.h"

#define GFG_GAME_INFO  0xE89B70 

#define MK9HOOK_VERSION "0.3.3"

enum  PLAYER_NUM
{
	INVALID_PLAYER_NUM = -1,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS
};



int	  GetInfo(PLAYER_NUM plr);
int	  GetBackupInfo(PLAYER_NUM plr);
int	  GetObj(PLAYER_NUM plr);
int	  GetBackupObj(PLAYER_NUM plr);

void  SetCharacter(PLAYER_NUM plr, int unk, char* name);
void  SetStage(const char* stage);

void  SetCharacterMeter(PLAYER_NUM plr, float meter);
void  SetCharacterLife(PLAYER_NUM plr, float health);

void  SetBackupCharacterMeter(PLAYER_NUM plr, float meter);
void  SetBackupCharacterLife(PLAYER_NUM plr, float health);

void  SetCharacterScale(PLAYER_NUM plr, FVector* scale);
void  SetCharacterSpeed(PLAYER_NUM plr, float speed);
void  SetCharacterAI(PLAYER_NUM plr, const char* script);
void  DismemberCharacter(PLAYER_NUM plr, int partID);

void  SetCharacterDamageScale(PLAYER_NUM plr, float value);

void  RunCharacterScript(PLAYER_NUM plr, MKScript* script, int function);

char* GetCharacterName(PLAYER_NUM plr);
void  GetCharacterPosition(PLAYER_NUM plr, FVector* pos);


USkeletalMeshComponent* GetSkeleton(PLAYER_NUM plr);

void  SetGameSpeed(float speed);

bool IsNPC(const char* name);
bool IsBoss(const char* name);

void AddKoins(int amount);



namespace MK9Hooks {
	void  HookProcessStuff();
	void  HookLoadPlayerVersusScreen(int len, char* buf, char* format, char* charName, char* texture);

	void  SetupFight();

}