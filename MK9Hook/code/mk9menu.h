#include "mk9.h"
#include "GameInfo.h"
#include "helper/eKeyboardMan.h"
#include "unreal/FVector.h"
#include <vector>

enum eCustomCameras {
	CAMERA_3RDPERSON,
	CAMERA_HEAD_TRACKING,
	TOTAL_CUSTOM_CAMERAS
};

enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	SUBMENU_SCRIPT,
	SUBMENU_CAMERA_DEBUG,
	TOTAL_SUBMENUS
};

enum eScriptExecuteType {
	SCRIPT_P1,
	SCRIPT_P2,
	SCRIPT_GLOBAL
};

struct eScriptKeyBind {
	eScriptExecuteType type;
	eVKKeyCode key;
	char scriptSource[128] = {};
	char scriptName[128] = {};
	char functionHash[128] = {};
};

class MK9Menu {
public:
	bool	 m_bIsActive = false;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool     m_bPressingKey = false;
	bool	 m_bSlowMotion = false;
	bool	 m_bIsFocused = true;
	bool	 m_bCustomCameraPos = false;
	bool	 m_bCustomCameraFOV = false;
	bool	 m_bCustomCameraRot = false;
	bool	 m_bFreeCam = false;
	bool	 m_bCustomCameras = false;
	bool	 m_bYObtained = false;
	bool	 m_bStageModifier = false;
	bool	 m_bDontFlipCamera = false;
	bool	 m_bUsePlayerTwoAsTracker = false;
	bool	 m_bStaticHead = false;
	bool	 m_bDontAdjust = false;
	bool	 m_bMouseControl = false;
	bool	 m_bHideHUD = false;
	bool     m_bForceCameraUpdate = false;
	// cheats
	bool	m_bInfiniteHealthP1 = false;
	bool	m_bInfiniteMeterP1 = false;
	bool	m_bInfiniteHealthP2 = false;
	bool	m_bInfiniteMeterP2 = false;
	bool	m_bNoHealthP1 = false;
	bool	m_bNoHealthP2 = false;
	bool	m_bZeroMeterP1 = false;
	bool	m_bZeroMeterP2 = false;

	bool	m_bInfiniteHealthBP1 = false;
	bool	m_bInfiniteMeterBP1 = false;
	bool	m_bInfiniteHealthBP2 = false;
	bool	m_bInfiniteMeterBP2 = false;
	bool	m_bNoHealthBP1 = false;
	bool	m_bNoHealthBP2 = false;
	bool	m_bZeroMeterBP1 = false;
	bool	m_bZeroMeterBP2 = false;

	bool	m_bChangePlayerSpeed = false;
	bool	m_bChangePlayerScale = false;
	bool	m_bPlayer1Modifier = false;
	bool	m_bPlayer2Modifier = false;
	bool	m_bPlayer1BackupModifier = false;
	bool	m_bPlayer2BackupModifier = false;
	bool	m_bAIDroneModifierP1 = false;
	bool	m_bAIDroneModifierP2 = false;

	bool    m_bDisableComboScaling = false;

	float	 m_fSlowMotionSpeed = 0.5f;
	float	 m_fFreeCameraSpeed = 5.25f;
	float	 m_fP1Speed = 1.0f;
	float	 m_fP2Speed = 1.0f;
	float	 m_fAdjustCustomHeadCameraX = 0.0f;
	float	 m_fAdjustCustomHeadCameraY = -2800.0f;
	float	 m_fAdjustCustomHeadCameraZ = 0.0f;
	float	 m_fAdjustCustomHeadCameraY2 = 0.0f;


	int  m_nFreeCameraRotationSpeed = 120;
	int  m_nCurrentCustomCamera = CAMERA_3RDPERSON;


	int* m_pCurrentVarToChange = nullptr;

	int  m_nScriptExecuteType = 0;
	char* m_nHash = 0;
	MKScript* m_pScript;

	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	char szPlayer1ModifierBackupCharacter[128] = {};
	char szPlayer2ModifierBackupCharacter[128] = {};
	char szStageModifierStage[128] = {};
	char szCurrentCameraOption[128] = {};
	char szPlayer1AI[128] = {};
	char szPlayer2AI[128] = {};

	FVector	 m_vP1Scale = { 1.0f, 1.0f, 1.0f };
	FVector	 m_vP2Scale = { 1.0f, 1.0f, 1.0f };

	FVector camPos;
	FRotator camRot;
	float camFov;

	std::vector<eScriptKeyBind> m_vKeyBinds;

	FVector plrPos;
	FVector plrPos2;

	void Initialize();
	void Process();
	void Draw();
	void UpdateControls();

	void DrawCharacterTab();
	void DrawStageTab();
	void DrawPlayerTab();
	void DrawSpeedTab();
	void DrawCameraTab();
	void DrawCheatsTab();
	void DrawScriptTab();
	void DrawMiscTab();
	void DrawAITab();

	void DrawSettings();
	void DrawScriptReference();
	void DrawCamDebug();

	void DrawKeyBind(char* name, int* var);
	void KeyBind(int* var, char* bindName, char* name);

	void ProcessScriptHotkeys();

	bool GetActiveState();
};



extern MK9Menu* TheMenu;

void ToggleHUD();

char* GetMK9HookVersion();