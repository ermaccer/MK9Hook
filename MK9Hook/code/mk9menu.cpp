#include "mk9menu.h"
#include <iostream>
#include "..\imgui\imgui.h"
#include "eNotifManager.h"
#include "eSettingsManager.h"
#include <Windows.h>
#include "..\eDirectX9Hook.h"

const char* szCharacters[] = {
	"NPC_BaseMale",
	"NPC_ClassicJade",
	"NPC_ClassicNoob",
	"NPC_ClassicReptile",
	"NPC_ClassicSmoke",
	"NPC_CyberNinja_LK4D4",
	"NPC_GenericFighterA",
	"NPC_GenericFighterB",
	"NPC_GL_Oni",
	"NPC_JC_Director",
	"NPC_TarkatanSoldierA",
	"NPC_Zombie_Male",
	"NPC_FightingDummy_Male",
	"CHAR_Baraka",
	"CHAR_Baraka_B",
	"CHAR_CyberZero",
	"CHAR_CyberZero_C",
	"CHAR_Cyrax",
	"CHAR_Cyrax_B",
	"CHAR_Cyrax_C",
	"CHAR_Ermac",
	"CHAR_Ermac_B",
	"CHAR_Ermac_C",
	"CHAR_FreddyKrueger",
	"CHAR_Goro",
	"CHAR_Jade",
	"CHAR_Jade_B",
	"CHAR_Jade_C",
	"CHAR_Jade_D",
	"CHAR_Jax",
	"CHAR_Jax_B",
	"CHAR_JohnnyCage",
	"CHAR_JohnnyCage_B",
	"CHAR_Kabal",
	"CHAR_Kabal_B",
	"CHAR_Kano",
	"CHAR_Kano_B",
	"CHAR_Kenshi",
	"CHAR_Kintaro",
	"CHAR_Kitana",
	"CHAR_Kitana_B",
	"CHAR_Kitana_C",
	"CHAR_Kitana_D",
	"CHAR_KungLao",
	"CHAR_KungLao_B",
	"CHAR_LiuKang",
	"CHAR_LiuKang_B",
	"CHAR_Mileena",
	"CHAR_Mileena_B",
	"CHAR_Mileena_D",
	"CHAR_Mileena_E",
	"CHAR_Nightwolf",
	"CHAR_Nightwolf_B",
	"CHAR_Noob",
	"CHAR_Noob_B",
	"CHAR_Noob_D",
	"CHAR_QuanChi",
	"CHAR_QuanChi_B",
	"CHAR_Raiden",
	"CHAR_Raiden_B",
	"CHAR_Rain",
	"CHAR_Reptile",
	"CHAR_Reptile_B",
	"CHAR_Reptile_C",
	"CHAR_Scorpion",
	"CHAR_Scorpion_B",
	"CHAR_Scorpion_C",
	"CHAR_Sektor",
	"CHAR_Sektor_B",
	"CHAR_Sektor_C",
	"CHAR_ShangTsung",
	"CHAR_ShangTsung_B",
	"CHAR_ShaoKahn",
	"CHAR_Sheeva",
	"CHAR_Sheeva_B",
	"CHAR_Sindel",
	"CHAR_Sindel_B",
	"CHAR_Skarlet",
	"CHAR_Smoke",
	"CHAR_Smoke_B",
	"CHAR_Smoke_D",
	"CHAR_Sonya",
	"CHAR_Sonya_B",
	"CHAR_Stryker",
	"CHAR_Stryker_B",
	"CHAR_SubZero",
	"CHAR_SubZero_B",
	"CHAR_SubZero_C"
};

const char* szStageNames[]{
	"BGND_Armory",
	"BGND_BellTower",
	"BGND_BioViewer",
	"BGND_Courtyard",
	"BGND_CourtyardN",
	"BGND_DeadPool",
	"BGND_Desert",
	"BGND_FleshPits",
	"BGND_GorosLair",
	"BGND_Graveyard",
	"BGND_Hell",
	"BGND_KahnsColiseum",
	"BGND_Krypt",
	"BGND_LivingForest",
	"BGND_Nekropolis",
	"BGND_Pit",
	"BGND_PitBottom",
	"BGND_PitDay",
	"BGND_RooftopDawn",
	"BGND_RooftopDay",
	"BGND_RooftopDusk",
	"BGND_SKThrone",
	"BGND_SoulChamber",
	"BGND_STGardens",
	"BGND_STGardensN",
	"BGND_Street",
	"BGND_STThrone",
	"BGND_Subway",
	"BGND_Temple",
	"BGND_Tower",
	"BGND_Wastelands",
};
const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Third Person",
};

int GetCamMode(const char* mode)
{
	for (int i = 0; i < TOTAL_CUSTOM_CAMERAS; i++)
	{
		if (strcmp(mode, szCameraModes[i]) == 0)
		{
			return i;
			break;
		}
	}
	return -1;
}


MK9Menu* TheMenu = new MK9Menu();

FVector& colorFilter = *(FVector*)0xDEBF8C;

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

}

void MK9Menu::Initialize()
{
	m_bPlayer1Modifier = false;
	m_bPlayer2Modifier = false;
	m_bStageModifier = false;
	m_bCustomCameraPos = false;
	m_bCustomCameraRot = false;
	m_bCustomCameraFOV = false;
	m_fFreeCameraSpeed = 5.25f;
	m_nFreeCameraRotationSpeed = 120;
	m_bChangePlayerSpeed = false;
	m_bChangePlayerScale = false;
	camFov = 1.0f;
	m_bNoHealthP1 = false;
	m_bNoHealthP2 = false;
	m_fP1Speed = 1.0f;
	m_fP2Speed = 1.0f;
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	plrPos = {};
	plrPos2 = {};
	m_vP1Scale = { 1.0f,1.0f,1.0f };
	m_vP2Scale = { 1.0f,1.0f,1.0f };
	m_bSlowMotion = false;
	m_fSlowMotionSpeed = 0.5f;
	m_bCustomCameras = false;
	m_bYObtained = false;
	m_bZeroMeterP1 = false;
	m_bZeroMeterP2 = false;
}

void MK9Menu::Process()
{
	UpdateControls();
}

void MK9Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetMK9HookVersion(), &m_bIsActive, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			m_bSubmenuActive[SUBMENU_SETTINGS] = true;
			ImGui::EndMenu();
		}
	}
	ImGui::EndMenuBar();

	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character Modifier"))
		{
			ImGui::Checkbox("Enable Player 1 Modifier", &m_bPlayer1Modifier);

			if (ImGui::BeginCombo("Player 1 Character", szPlayer1ModifierCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
				{
					bool is_selected = (szPlayer1ModifierCharacter == szCharacters[n]);
					if (ImGui::Selectable(szCharacters[n], is_selected))
						sprintf(szPlayer1ModifierCharacter, szCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::Separator();
			ImGui::Checkbox("Enable Player 2 Modifier", &m_bPlayer2Modifier);

			if (ImGui::BeginCombo("Player 2 Character", szPlayer2ModifierCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
				{
					bool is_selected = (szPlayer2ModifierCharacter == szCharacters[n]);
					if (ImGui::Selectable(szCharacters[n], is_selected))
						sprintf(szPlayer2ModifierCharacter, szCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Stage Modifier"))
		{
			ImGui::Checkbox("Enable Stage Modifier", &m_bStageModifier);

			if (ImGui::BeginCombo("Stage", szStageModifierStage))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szStageNames); n++)
				{
					bool is_selected = (szStageModifierStage == szStageNames[n]);
					if (ImGui::Selectable(szStageNames[n], is_selected))
						sprintf(szStageModifierStage, szStageNames[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player Control"))
		{
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
			{
				ImGui::Checkbox("Change Player Speed", &m_bChangePlayerSpeed);
				ImGui::SliderFloat("Player 1", &m_fP1Speed, 0.0, 10.0f);
				ImGui::SliderFloat("Player 2", &m_fP2Speed, 0.0, 10.0f);
				if (ImGui::Button("Reset Speed"))
				{
					m_fP1Speed = 1.0f;
					m_fP2Speed = 1.0f;
					if (GetObj(PLAYER1))
						SetCharacterSpeed(PLAYER1, m_fP1Speed);
					if (GetObj(PLAYER2))
						SetCharacterSpeed(PLAYER2, m_fP2Speed);
				}

				ImGui::Checkbox("Change Player Scale", &m_bChangePlayerScale);
				ImGui::InputFloat3("Player 1 ", &m_vP1Scale.X);
				ImGui::InputFloat3("Player 2 ", &m_vP2Scale.X);

				if (ImGui::Button("Reset Scale"))
				{
					m_vP1Scale = { 1.0f,1.0f,1.0f };
					m_vP2Scale = { 1.0f,1.0f,1.0f };
					if (GetObj(PLAYER1))
						SetCharacterScale(PLAYER1,&m_vP1Scale);
					if (GetObj(PLAYER2))
						SetCharacterScale(PLAYER2, &m_vP2Scale);
				}
				ImGui::Separator();
				ImGui::Text("Position");
				ImGui::SameLine(); ShowHelpMarker("Read only!");
				if (GetObj(PLAYER1))
				{
					GetCharacterPosition(PLAYER1,&plrPos);
					ImGui::InputFloat3("X | Y | Z", &plrPos.X);
				}
				if (GetObj(PLAYER2))
				{
					GetCharacterPosition(PLAYER2,&plrPos2);
					ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
				}
			}
			else
				ImGui::Text("Player options are only available in-game!");
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Speed Modifier"))
		{
			ImGui::Text("Gamespeed Control");
			ImGui::InputFloat("", &m_fSlowMotionSpeed, 0.1f);

			if (m_fSlowMotionSpeed > 2.0f) m_fSlowMotionSpeed = 2.0f;
			if (m_fSlowMotionSpeed < 0.0f) m_fSlowMotionSpeed = 0.0f;
			if (ImGui::Checkbox("Enable", &m_bSlowMotion))
			{
				if (TheMenu->m_bSlowMotion)
					SetGameSpeed(m_fSlowMotionSpeed);
				else
					SetGameSpeed(1.0);
			}
			ImGui::SameLine(); ShowHelpMarker("Hotkey - F5.");

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Control"))
		{
			ImGui::Checkbox("Set Camera Position", &m_bCustomCameraPos);
			ImGui::InputFloat3("X | Y | Z", &camPos.X);
			ImGui::Checkbox("Set Camera Rotation", &m_bCustomCameraRot);
			ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);
			ImGui::Checkbox("Set FOV", &m_bCustomCameraFOV);
			ImGui::InputFloat("FOV", &camFov);
			ImGui::Separator();
			ImGui::Checkbox("Enable Freecam", &m_bFreeCam);
			ImGui::SameLine(); ShowHelpMarker("Allows to move camera with certain keys.\nRequires all toggles enabled!\nYou can configure keys in .ini file.");

			if (m_bFreeCam)
			{
				if (!m_bCustomCameraPos || !m_bCustomCameraRot || !m_bCustomCameraFOV)
					ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Check rest of the Set Camera options!");

				ImGui::InputFloat("Freecam Speed", &m_fFreeCameraSpeed);
				ImGui::InputInt("Freecam Rotation Speed", &m_nFreeCameraRotationSpeed);
			}

			if (GetObj(PLAYER1) && GetObj(PLAYER2))
			{
				ImGui::Checkbox("Custom Cameras", &m_bCustomCameras);

				if (ImGui::BeginCombo("Mode", szCurrentCameraOption))
				{
					for (int n = 0; n < IM_ARRAYSIZE(szCameraModes); n++)
					{
						bool is_selected = (szCurrentCameraOption == szCameraModes[n]);
						if (ImGui::Selectable(szCameraModes[n], is_selected))
							sprintf(szCurrentCameraOption, szCameraModes[n]);
						if (is_selected)
							ImGui::SetItemDefaultFocus();

					}
					ImGui::EndCombo();
				}
				m_nCurrentCustomCamera = GetCamMode(szCurrentCameraOption);
			}
			else
				ImGui::Text("Custom cameras will appear once in-game!");

			ImGui::EndTabItem();

		}
		if (ImGui::BeginTabItem("Cheats"))
		{
			ImGui::Separator();
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 11.5f * ImGui::GetFontSize());

			ImGui::Text("Infinite Health");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##infhealth", &m_bInfiniteHealthP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##infhealth", &m_bInfiniteHealthP2);
			ImGui::NextColumn();


			ImGui::Text("Zero Health\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##0health", &m_bNoHealthP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##0health", &m_bNoHealthP2);
			ImGui::NextColumn();

			ImGui::Text("Infinite Meter\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##super", &m_bInfiniteMeterP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##super", &m_bInfiniteMeterP2);
			ImGui::NextColumn();

			ImGui::Text("Zero Meter\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##0super", &m_bZeroMeterP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##0super", &m_bZeroMeterP2);
			ImGui::NextColumn();


			ImGui::Columns(1);
			ImGui::Separator();
			static int moneyAmount = 0;
			ImGui::Text("Krypt Koins");
			ImGui::InputInt("Amount", &moneyAmount);

			if (ImGui::Button("Add Koins"))
			{
				AddKoins(moneyAmount);
				Notifications->SetNotificationTime(1000);
				Notifications->PushNotification("Added %d koins", moneyAmount);
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc."))
		{
			ImGui::Text("Color Filter");
			ImGui::InputFloat3("R | G | B", &colorFilter.X);
#ifdef _DEBUG
			if (ImGui::Button("Print Pointers"))
			{
				printf("P1 OBJ: 0x%X INFO: 0x%X\n", GetObj(PLAYER1), GetInfo(PLAYER1));
			}
#endif
			ImGui::EndTabItem();
		}
	}
	ImGui::End();


	if (m_bSubmenuActive[SUBMENU_SETTINGS])
		DrawSettings();
}

void MK9Menu::UpdateControls()
{
	if (TheMenu->m_bFreeCam)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camPos.X += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camPos.X -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camPos.Y += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camPos.Y -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camPos.Z += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camPos.Z -= TheMenu->m_fFreeCameraSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			TheMenu->camRot.Yaw -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			TheMenu->camRot.Yaw += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			TheMenu->camRot.Roll -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			TheMenu->camRot.Roll += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			TheMenu->camRot.Pitch -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			TheMenu->camRot.Pitch += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
			TheMenu->camFov -= 1.0f;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
			TheMenu->camFov += 1.0f;
	}
}

void MK9Menu::DrawSettings()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 700,700 }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SUBMENU_SETTINGS]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"INI"
	};

	enum eSettings {
		MENU,
		INI,
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(settingNames); n++)
	{
		bool is_selected = (settingID == n);
		if (ImGui::Selectable(settingNames[n], is_selected))
			settingID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (settingID)
	{
	case MENU:
		ImGui::TextWrapped("All user settings are saved to mk9hook_user.ini.");
		ImGui::Text("Menu Scale");
		ImGui::InputFloat("", &SettingsMgr->fMenuScale);
		break;
	case INI:
		ImGui::TextWrapped("These settings control MK9Hook.ini options. Any changes require game restart to take effect.");
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		ImGui::Checkbox("Debug Console", &SettingsMgr->bEnableConsoleWindow);

		ImGui::LabelText("", "Features");
		ImGui::Separator();
		ImGui::Checkbox("Use Generic VS Images", &SettingsMgr->bUseGenericVersusImage);
		ImGui::SameLine(); ShowHelpMarker("Replaces all NPC vs images with 'dlc'. Disable only if you have VS images made for them.");
		ImGui::Separator();

		break;
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Settings saved to MK9Hook.ini and mk9hook_user.ini!");
		eDirectX9Hook::ms_bShouldReloadFonts = true;
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();

	ImGui::End();
}

bool MK9Menu::GetActiveState()
{
	return m_bIsActive;
}

char * GetMK9HookVersion()
{
	static char buffer[512] = {};
	sprintf(buffer, "MK9Hook by ermaccer (%s)", MK9HOOK_VERSION);
	return buffer;
}
