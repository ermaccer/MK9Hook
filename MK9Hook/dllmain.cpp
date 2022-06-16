// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include "code/mk9.h"
#include "MemoryMgr.h"
#include "code/mk9menu.h"
#include "code/eNotifManager.h"
#include "code/mkcamera.h"
#include "code/eSettingsManager.h"
#include "code/eGamepadManager.h"
#include "eDirectX9Hook.h"
#include "code/helper/eMouse.h"

using namespace Memory::VP;


void WINAPI HookUpdate()
{
	while (true)
	{
		MK9Hooks::HookProcessStuff();
		eMouse::UpdateMouse();
		Sleep(1);
	}
}

void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}

	printf("MK9Hook::OnInitializeHook() | Begin!\n");
	TheMenu->Initialize();
	Notifications->Init();

	InjectHook(0x8146A3, MK9Hooks::HookLoadPlayerVersusScreen, PATCH_CALL);
	InjectHook(0x80DF82, MK9Hooks::SetupFight, PATCH_CALL);

	InjectHook(0x82A24D,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x86AAB7,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x86CC89,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x86D13C,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x86D1E7,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x86D2B6,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x86D6E8,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x86D8E0,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x86DDB4,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x873462,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x8743C3,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x875F2E,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x878A46,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x878FB4,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x879229,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87B3F6,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87B73D,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87B872,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87B8D7,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87C756,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87CA63,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87D382,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87D4E2,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87D5C7,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87D8C1,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87DC44,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x87E42C,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x8DB93A,  &MKCamera::HookedSetPosition, PATCH_CALL);
	InjectHook(0x9782E2,  &MKCamera::HookedSetPosition, PATCH_CALL);

	InjectHook(0x82A25B, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86AAC7, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86CC94, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86D144, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86D2C1, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86D6F3, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86D8EB, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86DDBF, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86EF00, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86EF15, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x86EF2A, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x873470, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x876044, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x8760A1, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x8760FE, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x877B70, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x878A88, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x878FC2, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87921E, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87B401, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87B732, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87B87D, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87B8E2, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87CA6E, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87D4ED, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87D5D2, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87D8C9, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87DC4C, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x87E437, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x8DB96A, &MKCamera::HookedSetRotation, PATCH_CALL);
	InjectHook(0x9782F0, &MKCamera::HookedSetRotation, PATCH_CALL);


	InjectHook(0x82A26E, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x82A2E9, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x86B5A3, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x86B5C6, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x86D34A, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x86DE3F, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x8761F9, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x876214, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x876264, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x87629C, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x8795D9, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x87B88D, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x87B8F2, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x87C6BF, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x87E44C, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x8DB8D1, &MKCamera::HookedSetFOV, PATCH_CALL);
	InjectHook(0x978303, &MKCamera::HookedSetFOV, PATCH_CALL);


	//gamepad
	if (SettingsMgr->bEnableGamepadSupport)
		InjectHook(0x99CA36, XInputGetState_Hook, PATCH_JUMP);
}

bool CheckGame()
{
	char* gameName = (char*)(0xD15624);

	if (strcmp(gameName, "Unreal") == 0)
	{
		return true;
	}
	else
	{
		MessageBoxA(0, "Invalid game version!\nMK9Hook only supports latest Steam executable.\n\n"
			"If you still cannot run the plugin and made sure that the game is updated, MK9Hook needs to be updated.", 0, MB_ICONINFORMATION);
		return false;
	}
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (CheckGame())
		{
			SettingsMgr->Init();
			OnInitializeHook();
			DisableThreadLibraryCalls(hMod);
			CreateThread(nullptr, 0, DirectXHookThread, hMod, 0, nullptr);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HookUpdate, hMod, 0, nullptr);
		}
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}




