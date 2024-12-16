#include "Keybinds.h"
#include "../Render.h"

#include "imgui.h"


Keybinds::Keybinds(ImGuiKey inputKey, KeyMode mode, bool enableMode)
    : key(inputKey), mode(mode), isEnabled(enableMode), prevKeyState(false)
{
}

void Keybinds::Update()
{
    // Vérifie l'état actuel de la touche
    bool keyPressed = ImGui::IsKeyDown(key);

    switch (mode)
    {
    case HOLD:
        isEnabled = keyPressed;
        break;

    case TOGGLE:
        if (keyPressed && !prevKeyState) // Si la touche vient d'être pressée
        {
            isEnabled = !isEnabled;
        }
        break;

    case ALWAYS:
        isEnabled = true; // Toujours activé, peu importe les entrées
        break;

    case NONE:
        isEnabled = false; // Toujours désactivé
        break;
    }

    // Met à jour l'état précédent de la touche
    prevKeyState = keyPressed;
}

bool Keybinds::IsActive() const
{
    return isEnabled;
}

void Keybinds::SetKey(ImGuiKey newKey)
{
    key = newKey;
}

void Keybinds::SetMode(KeyMode newMode)
{
    mode = newMode;
}
