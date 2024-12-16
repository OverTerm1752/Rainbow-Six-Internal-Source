#pragma warning(disable : 6387)

#include "UI.h"

#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_win32.h"
#include "../../external/imgui/imgui_impl_dx11.h"

#include "../../external/minhook/minhook.h"

#include "Render.h"

#include "../Core/Features/Visuals.h"
#include "../Core/Features/Aimbot.h"
#include "../Core/Features/Misc.h"

#include "../Config.h"


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM wideParam, LPARAM longParam);
LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wideParam, LPARAM longParam)
{
	if (gui::open && ImGui_ImplWin32_WndProcHandler(window, message, wideParam, longParam))
		return 1L;

	return CallWindowProc(gui::originalWindowProcess, window, message, wideParam, longParam);
};

bool gui::SetupWindowClass() noexcept
{
	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(nullptr);
	windowClass.hIcon = nullptr;
	windowClass.hCursor = nullptr;
	windowClass.hbrBackground = nullptr;
	windowClass.lpszMenuName = nullptr;
	windowClass.lpszClassName = L"Window Class";
	windowClass.hIconSm = nullptr;

	if (!RegisterClassExW(&windowClass))
		return false;

	return true;
};

void gui::DestroyWindowClass() noexcept
{
	UnregisterClassW(
		windowClass.lpszClassName,
		windowClass.hInstance
	);
};

bool gui::SetupWindow() noexcept
{
	window = CreateWindowW(
		windowClass.lpszClassName,
		L"Window",
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		100,
		100,
		0,
		0,
		windowClass.hInstance,
		0
	);
	if (!window)
		return false;


	return true;
}

void gui::DestroyWindow() noexcept
{
	if (window)
		DestroyWindow(window);
}

bool gui::CreateDeviceD3D() noexcept
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = window;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		feature_levels,
		2,
		D3D11_SDK_VERSION,
		&sd,
		&swapChain,
		&device,
		nullptr,
		nullptr) == S_OK)
	{
		void** swapChainTable = *reinterpret_cast<void***>(swapChain);
		swapChain->Release();
		device->Release();
		presentAddr = (PresentFn)swapChainTable[8];
		return true;
	}
	return false;
};

void gui::CleanupDeviceD3D() noexcept
{
	if (mainRenderTargetView)
	{
		mainRenderTargetView->Release();
		mainRenderTargetView = nullptr;
	}

	if (context)
	{
		context->Release();
		context = nullptr;
	}

	if (device)
	{
		device->Release();
		device = nullptr;
	}
}

static long __stdcall gui::Present(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
	if (!setup) 
	{
		if (SUCCEEDED(swapChain->GetDevice(__uuidof(ID3D11Device), (void**)&device)))
		{
			device->GetImmediateContext(&context);
			DXGI_SWAP_CHAIN_DESC sd;
			swapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			device->CreateRenderTargetView(pBackBuffer, nullptr, &mainRenderTargetView);
			pBackBuffer->Release();
			originalWindowProcess = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProcess)));
			ImGui::CreateContext();
			Render::Fonts();
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(device, context);
			setup = true;
		}
		else
			return presentOrig(swapChain, syncInterval, flags);
	}


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	


	UIkey.Update();
	config->aimbot.key.Update();
	config->misc.noClipSettings.second.Update();
	config->misc.JumpingSettings.second.Update();

	if (UIkey.IsActive()) {
		open = true;
		Render::Style();
		Render::Menu();
	};

	Aimbot::Run();

	Visuals::Renderables();
	Visuals::Effects();

	Misc::Movement();
	Misc::Physics();
	Misc::ChatInteraction();


	ImGui::EndFrame();
	ImGui::Render();

	context->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return presentOrig(swapChain, syncInterval, flags);
}

void gui::SetupHook() 
{
	if (MH_Initialize())
		throw std::runtime_error("Unable to initialize minhook");

	if (MH_CreateHook(
		reinterpret_cast<void**>(presentAddr),
		&Present,
		reinterpret_cast<void**>(&presentOrig)
	)) 	throw std::runtime_error("Unable to hook Present");


	if (MH_EnableHook(MH_ALL_HOOKS))
		throw std::runtime_error("Unable to enable hooks");

	CleanupDeviceD3D();
};

void gui::Setup()
{
	if (!SetupWindowClass())
		throw std::runtime_error("Failed to create window class.");

	if (!SetupWindow())
		throw std::runtime_error("Failed to create window.");

	if (!CreateDeviceD3D())
		throw std::runtime_error("Failed to create device.");

	DestroyWindow();
	DestroyWindowClass();
};

void gui::DestroyHook() noexcept
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
};

void gui::Destroy() noexcept
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtrW(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(originalWindowProcess));

	CleanupDeviceD3D();
}