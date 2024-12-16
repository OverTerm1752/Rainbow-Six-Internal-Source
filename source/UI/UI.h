#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include <d3d11.h>

namespace gui
{
	inline bool open = true;
	inline bool setup = false;

	inline WNDPROC originalWindowProcess = nullptr;
	inline HWND window = nullptr;
	inline WNDCLASSEXW windowClass = { };

	inline IDXGISwapChain* swapChain = nullptr;
	inline ID3D11Device* device = nullptr;
	inline ID3D11DeviceContext* context = nullptr;
	inline ID3D11RenderTargetView* mainRenderTargetView = nullptr;

	bool SetupWindowClass() noexcept;
	void DestroyWindowClass() noexcept;
	bool SetupWindow() noexcept;
	void DestroyWindow() noexcept;

	bool CreateDeviceD3D() noexcept;
	void CleanupDeviceD3D() noexcept;


	void DestroyHook() noexcept;
	void SetupHook();
	void Setup();

	void Destroy() noexcept;

	static long __stdcall Present(IDXGISwapChain*, UINT, UINT);
	
	typedef long(__stdcall* PresentFn)(IDXGISwapChain*, UINT, UINT);
	inline PresentFn presentOrig, presentAddr;
};