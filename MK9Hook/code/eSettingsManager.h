#pragma once


// as usual, pluginmh/mugenhook

struct eMouseSettings {
	int sens;
	bool invert_y;
	bool invert_x;
};


class eSettingsManager {
public:
	void Init();

	bool bEnableConsoleWindow;

	bool bEnableGamepadSupport;

	bool bUseGenericVersusImage;

	int iHookMenuOpenKey;
	int iToggleHUDKey;
	
	
	// free camera keys
	int iFreeCameraKeyXPlus;
	int iFreeCameraKeyXMinus;
	int iFreeCameraKeyYPlus;
	int iFreeCameraKeyYMinus;
	int iFreeCameraKeyZPlus;
	int iFreeCameraKeyZMinus;

	int iFreeCameraKeyYawPlus;
	int iFreeCameraKeyYawMinus;
	int iFreeCameraKeyPitchPlus;
	int iFreeCameraKeyPitchMinus;
	int iFreeCameraKeyRollPlus;
	int iFreeCameraKeyRollMinus;

	int iFreeCameraKeyFOVPlus;
	int iFreeCameraKeyFOVMinus;


	eMouseSettings mouse;

	float fMenuScale;

	void SaveSettings();
	void ResetKeys();
};

extern eSettingsManager* SettingsMgr;