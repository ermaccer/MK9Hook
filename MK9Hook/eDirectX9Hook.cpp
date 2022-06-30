#include "eDirectX9Hook.h"
#include "code/eNotifManager.h"
#include "code/mk9menu.h"
#include "code/eSettingsManager.h"
#include "code/eGamepadManager.h"
#include "font.h"
EndScene eDirectX9Hook::m_pEndScene;
HWND eDirectX9Hook::ms_hWindow;
WNDPROC eDirectX9Hook::ms_pWndProc;
ImGuiStyle	eDirectX9Hook::ms_localStyleCopy;
Reset eDirectX9Hook::m_pReset;

bool eDirectX9Hook::ms_bInit;
bool eDirectX9Hook::ms_bShouldReloadFonts;

void eDirectX9Hook::Init()
{
	m_pEndScene = 0;
	ms_hWindow = 0;
	ms_pWndProc = 0;
	ms_bInit = false;
	ms_bShouldReloadFonts = false;
}

void eDirectX9Hook::SetImGuiStyle()
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

	style->WindowRounding = 6.0f;
	style->ItemSpacing = ImVec2(7, 5.5);
	style->FrameRounding = 2.0f;
	style->FramePadding = ImVec2(6, 4.25);

	ms_localStyleCopy = ImGui::GetStyle();


	ReloadImGuiFont();
}

void eDirectX9Hook::InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui_ImplWin32_Init(ms_hWindow);
	ImGui_ImplDX9_Init(pDevice);
	if (SettingsMgr->bEnableGamepadSupport)
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GamepadThread), nullptr, 0, nullptr);
	SetImGuiStyle();
}

void eDirectX9Hook::ReloadImGuiFont()
{
	if (!(SettingsMgr->fMenuScale < 1.0f))
	{
		float fontSize = 13.0f;
		ImGuiStyle * style = &ImGui::GetStyle();
		ImGuiIO io = ImGui::GetIO();
		io.Fonts->Clear();
		io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, fontSize * SettingsMgr->fMenuScale);
		io.Fonts->Build();

		style->WindowPadding = ms_localStyleCopy.WindowPadding;
		style->WindowRounding = ms_localStyleCopy.WindowRounding;
		style->WindowMinSize = ms_localStyleCopy.WindowMinSize;
		style->ChildRounding = ms_localStyleCopy.ChildRounding;
		style->PopupRounding = ms_localStyleCopy.PopupRounding;
		style->FramePadding = ms_localStyleCopy.FramePadding;
		style->FrameRounding = ms_localStyleCopy.FrameRounding;
		style->ItemSpacing = ms_localStyleCopy.ItemSpacing;
		style->ItemInnerSpacing = ms_localStyleCopy.ItemInnerSpacing;
		style->CellPadding = ms_localStyleCopy.CellPadding;
		style->TouchExtraPadding = ms_localStyleCopy.TouchExtraPadding;
		style->IndentSpacing = ms_localStyleCopy.IndentSpacing;
		style->ColumnsMinSpacing = ms_localStyleCopy.ColumnsMinSpacing;
		style->ScrollbarSize = ms_localStyleCopy.ScrollbarSize;
		style->ScrollbarRounding = ms_localStyleCopy.ScrollbarRounding;
		style->GrabMinSize = ms_localStyleCopy.GrabMinSize;
		style->GrabRounding = ms_localStyleCopy.GrabRounding;
		style->LogSliderDeadzone = ms_localStyleCopy.LogSliderDeadzone;
		style->TabRounding = ms_localStyleCopy.TabRounding;
		style->TabMinWidthForCloseButton = ms_localStyleCopy.TabMinWidthForCloseButton;
		style->DisplayWindowPadding = ms_localStyleCopy.DisplayWindowPadding;
		style->DisplaySafeAreaPadding = ms_localStyleCopy.DisplaySafeAreaPadding;
		style->MouseCursorScale = ms_localStyleCopy.MouseCursorScale;

		style->ScaleAllSizes(SettingsMgr->fMenuScale);
		ImGui_ImplDX9_InvalidateDeviceObjects();

		if (ms_bShouldReloadFonts)
			ms_bShouldReloadFonts = false;


	}
}

long __stdcall eDirectX9Hook::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!ms_bInit)
	{
		D3DDEVICE_CREATION_PARAMETERS params;
		pDevice->GetCreationParameters(&params);
		ms_hWindow = params.hFocusWindow;
		ms_pWndProc = (WNDPROC)SetWindowLongPtr(ms_hWindow, GWL_WNDPROC, (LONG_PTR)WndProc);
		InitImGui(pDevice);
		ms_bInit = true;
	}
	if (ms_bShouldReloadFonts)
		ReloadImGuiFont();

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = false;

	static bool draw = true;
	if (draw)
	{
		Notifications->SetNotificationTime(3500);
		Notifications->PushNotification("MK9Hook %s is running! Press F1 to open the menu.", MK9HOOK_VERSION);
		draw = false;
	}

	Notifications->Draw();

	if (TheMenu->GetActiveState())
		TheMenu->Draw();

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return m_pEndScene(pDevice);
}

long __stdcall eDirectX9Hook::Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS * pPresentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	ImGui_ImplDX9_CreateDeviceObjects();
	return m_pReset(pDevice, pPresentationParameters);
}

LRESULT __stdcall eDirectX9Hook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KILLFOCUS:
		TheMenu->m_bIsFocused = false;
		break;
	case WM_SETFOCUS:
		TheMenu->m_bIsFocused = true;
		break;
	case WM_KEYDOWN:
		if (wParam == SettingsMgr->iHookMenuOpenKey)
			TheMenu->m_bIsActive ^= 1;
		switch (wParam)
		{
		case VK_F5:
			TheMenu->m_bSlowMotion ^= 1;
			if (TheMenu->m_bSlowMotion)
				SetGameSpeed(TheMenu->m_fSlowMotionSpeed);
			else
				SetGameSpeed(1.0);
			break;
		case VK_F2:
			ToggleHUD();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (TheMenu->GetActiveState())
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(ms_pWndProc, hWnd, uMsg, wParam, lParam);
}

DWORD WINAPI DirectXHookThread(LPVOID lpReserved)
{
	Sleep(2000);
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)&eDirectX9Hook::m_pEndScene, eDirectX9Hook::EndScene);
			kiero::bind(16, (void**)&eDirectX9Hook::m_pReset, eDirectX9Hook::Reset);
			attached = true;
		}
	} while (!attached);
	return TRUE;
}