#include "mk9.h"

// as usual, based on mh2 debug menu

class MK9Menu {
private:
	int  iCurrentTab;
public:
	bool bIsActive;
	// window data
	bool bFocused;
	// characters
	bool bPlayer1ModifierEnabled;
	bool bPlayer2ModifierEnabled;

	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};

	// cheats
	bool bInfiniteHealthPlayer1;
	bool bInfiniteSuperBarPlayer1;
	bool bInfiniteHealthPlayer2;
	bool bInfiniteSuperBarPlayer2;
	bool bNoHealthPlayer1;
	bool bNoHealthPlayer2;
	bool bCustomCamera;
	bool bCustomFOV;
	bool bCustomCameraRot;
	FVector camPos;
	FRotator camRot;
	float camFov;


	bool bFreeCameraMovement;
	float fFreeCameraSpeed;
	int  iFreeCameraRotSpeed;


	// stage
	bool bStageModifier;
	char szStageModifierStage[128] = {};


	void Initialize();
	void Process();
	void Draw();
	void UpdateControls();
	bool GetActiveState();
};



extern MK9Menu* TheMenu;

char* GetMK9HookVersion();