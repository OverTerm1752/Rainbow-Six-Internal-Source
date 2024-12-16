#pragma once
#include <imgui.h>

enum KeyMode
{
    HOLD,   // Activé tant que la touche est pressée
    TOGGLE, // Alterne entre activé et désactivé à chaque pression
    ALWAYS, // Toujours activé (ignorer les entrées de touches)
    NONE    // Désactivé
};

class Keybinds
{
public:
    Keybinds(ImGuiKey inputKey, KeyMode mode, bool enableMode = false);

    void Update();       // Fonction à appeler chaque frame pour vérifier l'état
    bool IsActive() const; // Retourne l'état actuel (activé/désactivé)

    void SetKey(ImGuiKey newKey);  // Permet de changer la touche
    void SetMode(KeyMode newMode); // Permet de changer le mode

private:
    ImGuiKey key;       // Touche associée
    KeyMode mode;       // Mode actuel
    bool isEnabled;     // Indique si la fonction est activée ou non
    bool prevKeyState;  // État précédent de la touche (utile pour TOGGLE)
};
