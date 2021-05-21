// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include "code/mk9.h"
#include "MemoryMgr.h"
#include "includes.h"
#include "code/mk9menu.h"
#include "code/eNotifManager.h"
#include "code/mkcamera.h"
#include "code/eSettingsManager.h"

using namespace Memory::VP;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

void SetStyle()
{

	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.51f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.51f, 0.16f, 0.15f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.15f, 0.11f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.25f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.78f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.22f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.48f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.86f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.60f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.55f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.55f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.55f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.75f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.51f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.91f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.93f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.65f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.55f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.91f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.51f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.91f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}



void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
	SetStyle();

}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg)
	{
	case WM_KILLFOCUS:
		TheMenu->bFocused = false;
		break;
	case WM_SETFOCUS:
		TheMenu->bFocused = true;
		break;
	case WM_KEYDOWN:
		if (wParam == SettingsMgr->iHookMenuOpenKey)
			TheMenu->bIsActive ^= 1;
		break;
	default:
		break;
	}

	if (TheMenu->GetActiveState())
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}



bool init = false;
bool first_msg = true;
long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		D3DDEVICE_CREATION_PARAMETERS params;
		pDevice->GetCreationParameters(&params);
		window = params.hFocusWindow;
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
		InitImGui(pDevice);
		init = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = false;
	if (first_msg)
	{
		Notifications->SetNotificationTime(7500);
		Notifications->PushNotification("MK9Hook %s is running! Press F1 to open the menu.", MK9HOOK_VERSION);
		first_msg = false;
	}
	Notifications->Draw();

	if (TheMenu->GetActiveState())
	{
		TheMenu->Draw();
	}

	ImGui::EndFrame();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(pDevice);
}



DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)& oEndScene, hkEndScene);
			attached = true;
		}
	} while (!attached);
	return TRUE;
}
void CustomPrintf(int flag, char* format, ...)
{
	char msg[512];

	va_list args;
	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	if (strcmp(msg, "WebServicesJob::StepWaitProfileGUID") == 0)
		return;
	if (strcmp(msg, "HttpRequestJob::StepWaitForCompletion") == 0)
		return;

	if (strcmp(msg, "WebServicesJob::StepWaitProfileCreation") == 0)
		return;

	printf(msg);
	printf("\n");
}


void WINAPI HookUpdate()
{
	while (true)
	{
		MK9Hook::HookProcessStuff();
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

	//InjectHook(0x8FE4D0, CustomPrintf, PATCH_JUMP);
	InjectHook(0x8146A3, MK9Hook::HookLoadPlayerVersusScreen, PATCH_CALL);
	InjectHook(0x80DF82, MK9Hook::SetupFight, PATCH_CALL);

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
		MessageBoxA(0, "Invalid game version!\nMK9Hook only supports latest (or it needs to be updated) Steam executable.", 0, MB_ICONINFORMATION);
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
			DisableThreadLibraryCalls(hMod);
			CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
			CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HookUpdate, hMod, 0, nullptr);
			OnInitializeHook();
		}
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}




