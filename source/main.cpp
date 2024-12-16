#include <Windows.h>
#include <iostream>

#include "UI/UI.h"
#include "Engine/Engine.h"

void Setup(const HMODULE instance)
{
	try
	{
		//Engine::Get()->SetupConsole();

		gui::Setup();
		gui::SetupHook();
	}
	catch (const std::exception& error)
	{
		MessageBoxA(
			0,
			error.what(),
			"Load Error",
			MB_OK | MB_ICONEXCLAMATION
		);

		goto UNLOAD;
	}

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));


UNLOAD:
	gui::DestroyHook();
	gui::Destroy();

	FreeLibraryAndExitThread(instance, 0);
};


BOOL WINAPI DllMain(const HMODULE instance, const uintptr_t reason, const void* reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);

		const auto thread = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(Setup),
			instance,
			0,
			nullptr
		);

		if (thread)
			CloseHandle(thread);
	};

	return TRUE;
};