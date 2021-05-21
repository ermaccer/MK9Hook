#pragma once
#define GFG_GAME_INFO  0xE89B70 


#define MK9HOOK_VERSION "0.1"

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


struct FLinearColor
{
	float A;
	float G;
	float B;
	float R;
};


struct FRotator {
	int Pitch;
	int Yaw;
	int Roll;
};


struct player_info {
	char pad[2404];
	char name[64];
	char _pad[624];
	float meter;

};

namespace MK9 {
	int	  GetCharacterInfo(PLAYER_NUM plr);
	int	  GetCharacterObject(PLAYER_NUM plr);

	void  SetCharacter(PLAYER_NUM plr, int unk, char* name);
	void  SetStage(const char* stage);

	void  SetCharacters(char* p1, char* p2);
	void  SetCharacterMeter(PLAYER_NUM plr, float meter);
	void  SetCharacterLife(PLAYER_NUM plr, float health);

	char* GetCharacterName(PLAYER_NUM plr);

	bool IsNPC(const char* name);
	bool IsBoss(const char* name);

	void AddKoins(int amount);

	void __fastcall CamSetPos(int ptr, int pos);
};


namespace MK9Hook {
	void  HookProcessStuff();
	void  HookSetPlayerCharacter(char* p1, char* p2);
	void  HookLoadPlayerVersusScreen(int len, char* buf, char* format, char* charName, char* texture);

	void  SetupFight();

	void __fastcall HookCamSetPos(int ptr, FVector* pos);

}