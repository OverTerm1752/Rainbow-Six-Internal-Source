#include "Engine.h"

void Engine::SetupConsole() noexcept
{
    AllocConsole();
    SetConsoleTitleA("Console");
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);
    freopen_s(&file, "CONOUT$", "w", stderr);
    freopen_s(&file, "CONIN$", "r", stdin);
}

Engine::~Engine() noexcept
{
    fclose(stdout);
    fclose(stderr);
    fclose(stdin);

    FreeConsole();
}