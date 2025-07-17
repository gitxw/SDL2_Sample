#pragma once

#include "T005_UserData.hpp"

#include <SGE.h>

// 帧事件处理函数
void FrameEventFunc(SGE_App* app, void* userData, SDL_Event& e)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T005_UserData* ud = static_cast<T005_UserData*>(userData);

    switch (e.type) {
    case SDL_QUIT:
        app->StopRunning();
        break;
    case SDL_MOUSEMOTION:
        ud->mx = e.motion.x;
        ud->my = e.motion.y;
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
    T005_UserData* ud = static_cast<T005_UserData*>(userData);

    if (ud->mx != -1) {
        // Distance across window
        float wpercent = ud->mx / 640.0f;
        float hpercent = ud->my / 480.0f;

        // Color
        ud->r = static_cast<unsigned char>(round(wpercent * 255));
        ud->g = static_cast<unsigned char>(round(hpercent * 255));

        ud->mx -= 320;
        ud->my -= 240;
        ud->rot = atan((float)ud->my / (float)ud->mx) * (180.0f / 3.14f);
        if (ud->mx < 0) {
            ud->rot -= 180;
        }
    }
    ud->mx = ud->my = -1;

    // 获取按键状态
    static const unsigned char* keys = SDL_GetKeyboardState(nullptr);
    // 根据按键状态，设置用户数据
    ud->isFlip = keys[SDL_SCANCODE_F]; // F键
}

// 帧渲染函数
void FrameRenderFunc(SGE_App* app, void* userData)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T005_UserData* ud = static_cast<T005_UserData*>(userData);
    // 取得渲染器
    SDL_Renderer* renderer = app->GetRenderer();

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Color mod (b will always be zero)
    SDL_SetTextureColorMod(ud->texture, ud->r, ud->g, 0);

    // Render texture
    SDL_Rect dest = { 240, 180, 160, 120 };
    SDL_RenderCopyEx(
        renderer, ud->texture, nullptr, &dest,
        ud->rot, nullptr,
        ud->isFlip ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

    // Update window
    SDL_RenderPresent(renderer);
}
