#include "mk9menu.h"
#include <iostream>
#include "..\imgui\imgui.h"
#include "eNotifManager.h"
#include "eSettingsManager.h"
#include <Windows.h>

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


MK9Menu* TheMenu = new MK9Menu();

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
	bPlayer1ModifierEnabled = false;
	bPlayer2ModifierEnabled = false;
	bStageModifier = false;
	iCurrentTab = 0;
	bCustomCamera = false;
	bCustomCameraRot = false;
	bCustomFOV = false;
	fFreeCameraSpeed = 5.25f;
	iFreeCameraRotSpeed = 120;

	camFov = 1.0f;
	bNoHealthPlayer1 = false;
	bNoHealthPlayer2 = false;

	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szStageModifierStage, szStageNames[0]);

}

void MK9Menu::Process()
{
	UpdateControls();



	if (TheMenu->bInfiniteSuperBarPlayer1)
		MK9::SetCharacterMeter(PLAYER1, 1.0f);

	if (TheMenu->bInfiniteSuperBarPlayer2)
		MK9::SetCharacterMeter(PLAYER2, 1.0f);

	if (TheMenu->bInfiniteHealthPlayer1)
	{
		if (MK9::GetCharacterObject(PLAYER1))
			MK9::SetCharacterLife(PLAYER1, 1.0f);
	}
	if (TheMenu->bInfiniteHealthPlayer2)
	{
		if (MK9::GetCharacterObject(PLAYER2))
			MK9::SetCharacterLife(PLAYER2, 1.0f);
	}
	if (TheMenu->bNoHealthPlayer1)
	{
		if (MK9::GetCharacterObject(PLAYER1))
			MK9::SetCharacterLife(PLAYER1, 0.0f);
	}
	if (TheMenu->bNoHealthPlayer2)
	{
		if (MK9::GetCharacterObject(PLAYER2))
			MK9::SetCharacterLife(PLAYER2, 0.0f);
	}
}

void MK9Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetMK9HookVersion());
	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character Modifier"))
		{
			ImGui::Checkbox("Enable Player 1 Modifier", &bPlayer1ModifierEnabled);

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
			ImGui::Checkbox("Enable Player 2 Modifier", &bPlayer2ModifierEnabled);

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


			ImGui::Checkbox("Enable Stage Modifier", &bStageModifier);

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
		if (ImGui::BeginTabItem("Camera Control"))
		{
			ImGui::Checkbox("Custom Camera Position", &bCustomCamera);
			ImGui::InputFloat3("X | Y | Z", &camPos.X);
			ImGui::Checkbox("Custom Camera Rotation", &bCustomCameraRot);
			ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);
			ImGui::Checkbox("Custom FOV", &bCustomFOV);
			ImGui::InputFloat("FOV", &camFov);
			ImGui::Separator();
			ImGui::Checkbox("Enable Freecam", &bFreeCameraMovement);
			ImGui::SameLine(); ShowHelpMarker("Requires both toggles enabled!\n You can configure keys in .ini file.");
			ImGui::InputFloat("Freecam Speed", &fFreeCameraSpeed);
			ImGui::InputInt("Freecam Rotation Speed", &iFreeCameraRotSpeed);


			ImGui::EndTabItem();

		}
		if (ImGui::BeginTabItem("Cheats"))
		{
			ImGui::Text("Player 1");
			ImGui::Separator();
			ImGui::Checkbox("Infinite Health", &bInfiniteHealthPlayer1);
			ImGui::Checkbox("Zero Health", &bNoHealthPlayer1);
			ImGui::Checkbox("Infinite Super Meter", &bInfiniteSuperBarPlayer1);
			ImGui::Separator();

			ImGui::Text("Player 2");
			ImGui::Separator();
			ImGui::Checkbox("Infinite Health ", &bInfiniteHealthPlayer2);
			ImGui::Checkbox("Zero Health ", &bNoHealthPlayer2);
			ImGui::Checkbox("Infinite Super Meter ", &bInfiniteSuperBarPlayer2);
			ImGui::Separator();

			static int moneyAmount = 0;
			ImGui::Text("Krypt Koins");
			ImGui::InputInt("Amount", &moneyAmount);

			if (ImGui::Button("Add Koins"))
			{
				MK9::AddKoins(moneyAmount);
				Notifications->SetNotificationTime(6000);
				Notifications->PushNotification("Added %d koins", moneyAmount);
			}

			ImGui::EndTabItem();
		}
	}
}

void MK9Menu::UpdateControls()
{
	if (TheMenu->bFreeCameraMovement)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camPos.X += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camPos.X -= TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camPos.Y += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camPos.Y -= TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camPos.Z += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camPos.Z -= TheMenu->fFreeCameraSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			TheMenu->camRot.Yaw -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			TheMenu->camRot.Yaw += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			TheMenu->camRot.Roll -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			TheMenu->camRot.Roll += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			TheMenu->camRot.Pitch -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			TheMenu->camRot.Pitch += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
			TheMenu->camFov -= 1.0f;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
			TheMenu->camFov += 1.0f;
	}
}

bool MK9Menu::GetActiveState()
{
	return bIsActive;
}

char * GetMK9HookVersion()
{
	char buffer[512];
	sprintf(buffer, "MK9Hook by ermaccer (%s)", MK9HOOK_VERSION);
	return buffer;
}
