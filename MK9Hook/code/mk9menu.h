#include "mk9.h"
enum eCustomCameras {
	CAMERA_3RDPERSON,
	TOTAL_CUSTOM_CAMERAS
};

enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	TOTAL_SUBMENUS
};

// as usual, based on mh2 debug menu

class MK9Menu {
public:
	bool	 m_bIsActive;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool	 m_bSlowMotion;
	bool	 m_bIsFocused;
	bool	 m_bCustomCameraPos;
	bool	 m_bCustomCameraFOV;
	bool	 m_bCustomCameraRot;
	bool	 m_bFreeCam;
	bool	 m_bCustomCameras;
	bool	 m_bYObtained;
	bool	 m_bStageModifier;
	// cheats
	bool m_bInfiniteHealthP1;
	bool m_bInfiniteMeterP1;
	bool m_bInfiniteHealthP2;
	bool m_bInfiniteMeterP2;
	bool m_bNoHealthP1;
	bool m_bNoHealthP2;
	bool m_bZeroMeterP1;
	bool m_bZeroMeterP2;
	bool	m_bChangePlayerSpeed;
	bool	m_bChangePlayerScale;
	bool m_bPlayer1Modifier;
	bool m_bPlayer2Modifier;

	float	 m_fSlowMotionSpeed;
	float	 m_fFreeCameraSpeed;
	float	 m_fP1Speed;
	float	 m_fP2Speed;

	int  m_nFreeCameraRotationSpeed;
	int  m_nCurrentCustomCamera;

	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	char szStageModifierStage[128] = {};
	char szCurrentCameraOption[128] = {};

	FVector	 m_vP1Scale;
	FVector	 m_vP2Scale;

	FVector camPos;
	FRotator camRot;
	float camFov;

	FVector plrPos;
	FVector plrPos2;

	void Initialize();
	void Process();
	void Draw();
	void UpdateControls();

	void DrawSettings();

	bool GetActiveState();
};



extern MK9Menu* TheMenu;

char* GetMK9HookVersion();