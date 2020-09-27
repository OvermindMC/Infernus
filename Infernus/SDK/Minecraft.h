#pragma once
#include "../Other/Utils.h"
#include "Classes/ClientInstance.h"

static ClientInstance* CachedClientInstance = nullptr;
static GameMode* CachedGameMode = nullptr;
static std::vector<Actor*>* CachedPlayers = new std::vector<Actor*>();

class Minecraft {
public:
    static UINT64 GetBaseModule() {
        return (UINT64)GetModuleHandle(NULL);
    };

    static ClientInstance* GetClientInstance() {
        return (ClientInstance*)CachedClientInstance;
    };

    static LocalPlayer* GetLocalPlayer() {
        return GetClientInstance()->LocalPlayer();
    };

    static GameMode* GetGameMode() {
        return CachedGameMode;
    };

    static std::vector<Actor*>* FetchPlayers() {
        return CachedPlayers;
    };
};