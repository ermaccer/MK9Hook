#include <Windows.h>
#include <d3d9.h>
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef long(__stdcall* Reset)(LPDIRECT3DDEVICE9,D3DPRESENT_PARAMETERS*);

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

class eDirectX9Hook {
public:
	static EndScene m_pEndScene;
	static Reset    m_pReset;
	static HWND ms_hWindow;
	static WNDPROC ms_pWndProc;
	static ImGuiStyle	ms_localStyleCopy;

	static bool ms_bInit;
	static bool ms_bShouldReloadFonts;

	static void	   Init();
	static void    SetImGuiStyle();
	static void    InitImGui(LPDIRECT3DDEVICE9 pDevice);
	static void	   ReloadImGuiFont();
	static long __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice);
	static long __stdcall Reset(LPDIRECT3DDEVICE9 pDevice,D3DPRESENT_PARAMETERS *pPresentationParameters);
	static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};


DWORD WINAPI DirectXHookThread(LPVOID lpReserved);
