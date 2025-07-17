#pragma once

#include "T009_UserData.hpp"

#include <SGE.h>

// 帧事件处理函数
void FrameEventFunc(SGE_App* app, void* userData, SDL_Event& e)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T009_UserData* ud = static_cast<T009_UserData*>(userData);

    switch (e.type) {
    case SDL_QUIT:
        app->StopRunning();
        break;
    }
}

// 帧更新函数
void FrameUpdateFunc(SGE_App* app, void* userData, float delta_ms)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T009_UserData* ud = static_cast<T009_UserData*>(userData);
}

// 帧渲染函数
void FrameRenderFunc(SGE_App* app, void* userData)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T009_UserData* ud = static_cast<T009_UserData*>(userData);
    // 取得渲染器
    SDL_Renderer* renderer = app->GetRenderer();

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    Uint32 current = SDL_GetTicks();
    float dT = (current - ud->ss.lastUpdate) / 1000.0f;

    int framesToUpdate = static_cast<int>(floor(dT / (1.0f / sprite_fps)));
    if (framesToUpdate > 0) {
        ud->ss.lastFrame += framesToUpdate;
        ud->ss.lastFrame %= ud->ss.sprites.size();
        ud->ss.lastUpdate = current;
    }

    SDL_RenderCopy(renderer, ud->ss.texture, &ud->ss.sprites[ud->ss.lastFrame], nullptr);

    // Update window
    SDL_RenderPresent(renderer);
}
