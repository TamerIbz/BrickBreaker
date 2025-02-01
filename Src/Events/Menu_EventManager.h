#pragma once
#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include "../GAME/MENU_STATES.h"

class Menu_EventManager {
public:
    using Callback = std::function<void(SCREEN_STATES)>;

#pragma region Subscribe 
    void subscribeActivate(const std::string& eventName, Callback callback) { // UI Menu Activated (shows)
        activateListeners[eventName].push_back(callback);
    }

    void subscribeDeactivate(const std::string& eventName, Callback callback) { // UI Menu Deactivates (hides)
        deactivateListeners[eventName].push_back(callback);
    }
#pragma endregion

#pragma region Publishing (calling method to activate & deactive menu)
    void publish(SCREEN_STATES newScreen, SCREEN_STATES oldScreen) // Setting new & old menu, activates new and deactivates old
    {
        CURRENT_SCREEN_STATE = newScreen;
        if (deactivateListeners.find("ScreenDeactivate") != deactivateListeners.end()) {
            for (auto& callback : deactivateListeners["ScreenDeactivate"]) {
                callback(oldScreen);
            }
        }

        if (activateListeners.find("ScreenActivate") != activateListeners.end()) {
            for (auto& callback : activateListeners["ScreenActivate"]) {
                callback(newScreen);
            }
        }
    }
#pragma endregion

    static Menu_EventManager& getInstance() { // singleton
        static Menu_EventManager instance;
        return instance;
    }

private:
    std::unordered_map<std::string, std::vector<Callback>> activateListeners;
    std::unordered_map<std::string, std::vector<Callback>> deactivateListeners;

};

