#include "mk9.h"
#include <iostream>
#include <Windows.h>
#include "mk9menu.h"
#include "eNotifManager.h"
#include "eSettingsManager.h"
#include "unreal/FName.h"
#include "mkcamera.h"

int GetInfo(PLAYER_NUM plr)
{
	int gameinfo = *(int*)(GFG_GAME_INFO);
	return ((int(__thiscall*)(int, PLAYER_NUM))0x80E540)(gameinfo, plr);
}

int GetObj(PLAYER_NUM plr)
{
	return ((int(__thiscall*)(int, int))0x895B70)(GetInfo(plr), 0);
}

void SetCharacter(PLAYER_NUM plr, int unk, char * name)
{
	((void(__cdecl*)(PLAYER_NUM, int, char*))0x8141A0)(plr, unk, name);
}

void SetStage(const char * stage)
{
	((void(__cdecl*)(const char*))0x811DD0)(stage);
}

void SetCharacterMeter(PLAYER_NUM plr, float meter)
{
	int info = GetInfo(plr);
	*(float*)(info + 0xC14) = meter;
}

void SetCharacterLife(PLAYER_NUM plr, float health)
{
	int obj = GetObj(plr);
	*(float*)(obj + 0x78C0) = health;

}

void SetCharacterScale(PLAYER_NUM plr, FVector * scale)
{
	int obj = GetObj(plr);
	int actor = *(int*)(obj + 8);
	*(FVector*)(actor + 0x118 + 4) = *scale;
}

void SetCharacterSpeed(PLAYER_NUM plr, float speed)
{
	int obj = GetObj(plr);
	*(float*)(obj + 0xF4) = speed;
}

void SetCharacterAI(PLAYER_NUM plr, const char* script)
{
	int info = GetInfo(plr);
	int drone = ((int(__thiscall*)(int))0x44D480)(info);
	if (drone)
		((void(__cdecl*)(int, const char*))0x891A80)(drone, script);
}

void DismemberCharacter(PLAYER_NUM plr, int partID)
{
	int obj = GetObj(plr);
	USkeletalMeshComponent* skeleton = GetSkeleton(plr);
	if (skeleton)
		skeleton->Dismember(partID);
	
}

void SetCharacterDamageScale(PLAYER_NUM plr, float value)
{
	int info = GetInfo(plr);
	*(float*)(info + 0x17EC) = value;
}

void RunCharacterScript(PLAYER_NUM plr, MKScript* script, int function)
{
	((void(__thiscall*)(int, MKScript*, int))0x45C610)(*(int*)((int)GetObj(plr) + 0x2FA4), script, function);
}

char * GetCharacterName(PLAYER_NUM plr)
{
	int info = GetInfo(plr);
	return (char*)(info + 2404);
}

void GetCharacterPosition(PLAYER_NUM plr, FVector * pos)
{
	int obj = GetObj(plr);
	int actor = *(int*)(obj + 8);
	FVector location = *(FVector*)(actor + 0xDC);
	*pos = location;
}

USkeletalMeshComponent* GetSkeleton(PLAYER_NUM plr)
{
	int obj = GetObj(plr);
	return *(USkeletalMeshComponent**)(obj + 268);
}

void SetGameSpeed(float speed)
{
	*(float*)0xE91E24 = speed;
}

bool IsNPC(const char * name)
{
	// game removes CHAR_, so this kinda breaks NPC_
	static const char* szNPCs[] = {
	"asemale",
	"lassicjade",
	"lassicnoob",
	"lassicreptile",
	"lassicsmoke",
	"yberNinja_lk4d4",
	"enericfightera",
	"enericfighterb",
	"l_oni",
	"c_director",
	"arkatansoldiera",
	"ombie_ale",
	};

	char tmp[64] = {};
	strcpy(tmp, name);

	for (int i = 0; i < strlen(tmp); i++)
		tmp[i] = tolower(tmp[i]);


	for (int i = 0; i < sizeof(szNPCs) / sizeof(szNPCs[0]); i++)
	{
		if (strcmp(tmp, szNPCs[i]) == 0)
			return true;
	}



	return false;
}

bool IsBoss(const char * name)
{
	static const char* szBoss[] = {
	"shaokahn",
	"kintaro",
	"goro",
	};

	char tmp[64] = {};
	strcpy(tmp, name);

	for (int i = 0; i < strlen(tmp); i++)
		tmp[i] = tolower(tmp[i]);

	for (int i = 0; i < sizeof(szBoss) / sizeof(szBoss[0]); i++)
	{
		if (strcmp(tmp, szBoss[i]) == 0)
			return true;
	}
	return false;
}

void AddKoins(int amount)
{
	int info = GetInfo(PLAYER1);
	((void(__cdecl*)(int, int))0x972A70)(info, amount);
}


void MK9Hooks::HookProcessStuff()
{
	Notifications->Update();
	TheMenu->Process();


	if (TheMenu->m_bInfiniteMeterP1)
		SetCharacterMeter(PLAYER1, 1.0f);

	if (TheMenu->m_bInfiniteMeterP2)
		SetCharacterMeter(PLAYER2, 1.0f);


	if (TheMenu->m_bZeroMeterP1)
		SetCharacterMeter(PLAYER1, 0.0f);

	if (TheMenu->m_bZeroMeterP2)
		SetCharacterMeter(PLAYER2, 0.0f);

	if (TheMenu->m_bInfiniteHealthP1)
	{
		if (GetObj(PLAYER1))
			SetCharacterLife(PLAYER1, 1.0f);
	}
	if (TheMenu->m_bInfiniteHealthP2)
	{
		if (GetObj(PLAYER2))
			SetCharacterLife(PLAYER2, 1.0f);
	}
	if (TheMenu->m_bNoHealthP1)
	{
		if (GetObj(PLAYER1))
			SetCharacterLife(PLAYER1, 0.0f);
	}
	if (TheMenu->m_bNoHealthP2)
	{
		if (GetObj(PLAYER2))
			SetCharacterLife(PLAYER2, 0.0f);
	}


	if (TheMenu->m_bChangePlayerScale)
	{
		if (GetObj(PLAYER1))
			SetCharacterScale(PLAYER1,&TheMenu->m_vP1Scale);
		if (GetObj(PLAYER2))
			SetCharacterScale(PLAYER2, &TheMenu->m_vP2Scale);
	}

	if (TheMenu->m_bDisableComboScaling)
	{
		SetCharacterDamageScale(PLAYER1, 1.0f);
		SetCharacterDamageScale(PLAYER2, 1.0f);
	}

	if (TheMenu->m_bChangePlayerSpeed)
	{
		if (GetObj(PLAYER1))
			SetCharacterSpeed(PLAYER1, TheMenu->m_fP1Speed);
		if (GetObj(PLAYER2))
			SetCharacterSpeed(PLAYER2, TheMenu->m_fP2Speed);
	}

	if (TheMenu->m_bSlowMotion)
		SetGameSpeed(TheMenu->m_fSlowMotionSpeed);

	if (TheMenu->m_bForceCameraUpdate)
	{
		if (TheCamera)
		{
			TheCamera->HookedSetPosition(&TheMenu->camPos);
			TheCamera->HookedSetRotation(&TheMenu->camRot);
			//TheCamera->SetFOV(TheMenu->camFov);
		}

	}

}

void MK9Hooks::HookLoadPlayerVersusScreen(int len, char * buf, char * format, char * charName, char * texture)
{
	if (SettingsMgr->bUseGenericVersusImage)
	{
		if (IsBoss(charName) || IsNPC(charName))
			charName = "dlc";
	}


	((void(__cdecl*)(int, char*, char*, char*, char*))0x616500)(len, buf, format, charName, texture);
}

void MK9Hooks::SetupFight()
{
	printf("MK9Hook::Info() | Starting a new fight!\n");

	TheMenu->m_bYObtained = false;

	if (TheMenu->m_bStageModifier)
		SetStage(TheMenu->szStageModifierStage);
	if (TheMenu->m_bPlayer1Modifier)
		SetCharacter(PLAYER1, 0, TheMenu->szPlayer1ModifierCharacter);
	if (TheMenu->m_bPlayer2Modifier)
		SetCharacter(PLAYER2, 0, TheMenu->szPlayer2ModifierCharacter);

	if (TheMenu->m_bPlayer1BackupModifier)
		SetCharacter(PLAYER1, 1, TheMenu->szPlayer1ModifierBackupCharacter);
	if (TheMenu->m_bPlayer2BackupModifier)
		SetCharacter(PLAYER2, 1, TheMenu->szPlayer2ModifierBackupCharacter);


	printf("MK9Hook::Info() | %s VS %s\n", GetCharacterName(PLAYER1), GetCharacterName(PLAYER2));
}
