#include "mk9.h"
#include <iostream>
#include <Windows.h>
#include "mk9menu.h"
#include "eNotifManager.h"
#include "eSettingsManager.h"

int MK9::GetCharacterInfo(PLAYER_NUM plr)
{
	int gameinfo = *(int*)(GFG_GAME_INFO);
	return ((int(__thiscall*)(int, PLAYER_NUM))0x80E540)(gameinfo, plr);
}

int MK9::GetCharacterObject(PLAYER_NUM plr)
{
	return ((int(__thiscall*)(int, int))0x895B70)(GetCharacterInfo(plr),0);
}

void MK9::SetCharacter(PLAYER_NUM plr, int unk, char * name)
{
	((void(__cdecl*)(PLAYER_NUM, int, char*))0x8141A0)(plr, unk, name);
}

void MK9::SetStage(const char * stage)
{
	((void(__cdecl*)(const char*))0x811DD0)(stage);
}

void MK9::SetCharacters(char * p1, char * p2)
{
	((void(__cdecl*)(char*, char*))0x8142E0)(p1,p2);
}

void MK9::SetCharacterMeter(PLAYER_NUM plr, float meter)
{
	int info = GetCharacterInfo(plr);
	*(float*)(info + 0xC14) = meter;
}

void MK9::SetCharacterLife(PLAYER_NUM plr, float health)
{
	int obj = GetCharacterObject(plr);
	*(float*)(obj + 0x78C0) = health;

}

char * MK9::GetCharacterName(PLAYER_NUM plr)
{
	int info = GetCharacterInfo(plr);
	return (char*)(info + 2404);
}

bool MK9::IsNPC(const char * name)
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

bool MK9::IsBoss(const char * name)
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

void MK9::AddKoins(int amount)
{
	int info = GetCharacterInfo(PLAYER1);
	((void(__cdecl*)(int, int))0x972A70)(info, amount);
}

void __fastcall MK9::CamSetPos(int ptr, int pos)
{
	if (ptr && pos)
	printf("%x %x\n", ptr, pos);
	((void(__thiscall*)(int, int))0x45E1C0)(ptr, pos);
}




void MK9Hook::HookProcessStuff()
{
	Notifications->Update();
	TheMenu->Process();
}

void MK9Hook::HookSetPlayerCharacter(char * p1, char * p2)
{
	p1 = "CHAR_FreddyKrueger";
	MK9::SetCharacters(p1, p2);
}

void MK9Hook::HookLoadPlayerVersusScreen(int len, char * buf, char * format, char * charName, char * texture)
{
	if (SettingsMgr->bUseGenericVersusImage)
	{
		if (MK9::IsBoss(charName) || MK9::IsNPC(charName))
			charName = "dlc";
	}


	((void(__cdecl*)(int, char*, char*, char*, char*))0x616500)(len, buf, format, charName, texture);
}

void MK9Hook::SetupFight()
{
	printf("MK9Hook::Info() | Starting a new fight!\n");
	if (TheMenu->bStageModifier)
		MK9::SetStage(TheMenu->szStageModifierStage);
	if (TheMenu->bPlayer1ModifierEnabled)
		MK9::SetCharacter(PLAYER1, 0, TheMenu->szPlayer1ModifierCharacter);
	if (TheMenu->bPlayer2ModifierEnabled)
		MK9::SetCharacter(PLAYER2, 0, TheMenu->szPlayer2ModifierCharacter);



	printf("MK9Hook::Info() | %s VS %s\n", MK9::GetCharacterName(PLAYER1), MK9::GetCharacterName(PLAYER2));
}

void __fastcall MK9Hook::HookCamSetPos(int ptr, FVector * pos)
{
	if (!TheMenu->bCustomCamera)
	{
		TheMenu->camPos = *pos;
		//MK9::CamSetPos(ptr, pos);
	}
	//else
	//	MK9::CamSetPos(ptr, &TheMenu->camPos);
}
