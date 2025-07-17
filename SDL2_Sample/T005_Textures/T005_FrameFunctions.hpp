#pragma once

#include "T005_UserData.hpp"

#include <SGE.h>

// 帧事件处理函数
void FrameEventFunc(SGE_Runner* runner, SDL_Event& e)
{
    SDL_assert(runner != nullptr);
    SDL_assert(runner->GetApp() != nullptr);
    SDL_assert(runner->GetUserData() != nullptr);

    // 取得用户数据
    T005_UserData* userData = static_cast<T005_UserData*>(runner->GetUserData());

    switch (e.type) {
    case SDL_QUIT:
        runner->StopRunning();
        break;
    case SDL_MOUSEMOTION:
        userData->mx = e.motion.x;
        userData->my = e.motion.y;
        break;
    }
}

// 帧更新函数
void FrameUpdateFunc(SGE_Runner* runner, float delta_ms)
{
    SDL_assert(runner != nullptr);
    SDL_assert(runner->GetApp() != nullptr);
    SDL_assert(runner->GetUserData() != nullptr);

    // 取得用户数据
    T005_UserData* userData = static_cast<T005_UserData*>(runner->GetUserData());

    if (userData->mx != -1) {
        // Distance across window
        float wpercent = userData->mx / 640.0f;
        float hpercent = userData->my / 480.0f;

        // Color
        userData->r = static_cast<unsigned char>(round(wpercent * 255));
        userData->g = static_cast<unsigned char>(round(hpercent * 255));

        userData->mx -= 320;
        userData->my -= 240;
        userData->rot = atan((float)userData->my / (float)userData->mx) * (180.0f / 3.14f);
        if (userData->mx < 0) {
            userData->rot -= 180;
        }
    }
    userData->mx = userData->my = -1;

    // 获取按键状态
    static const unsigned char* keys = SDL_GetKeyboardState(nullptr);
    // 根据按键状态，设置用户数据
    userData->isFlip = keys[SDL_SCANCODE_F]; // F键
}

// 帧渲染函数
void FrameRenderFunc(SGE_Runner* runner)
{
    SDL_assert(runner != nullptr);
    SDL_assert(runner->GetApp() != nullptr);
    SDL_assert(runner->GetUserData() != nullptr);

    // 取得用户数据
    T005_UserData* userData = static_cast<T005_UserData*>(runner->GetUserData());
    // 取得渲染器
    SDL_Renderer* renderer = runner->GetApp()->GetRenderer();

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Color mod (b will always be zero)
    SDL_SetTextureColorMod(userData->texture, userData->r, userData->g, 0);

    // Render texture
    SDL_Rect dest = { 240, 180, 160, 120 };
    SDL_RenderCopyEx(
        renderer, userData->texture, nullptr, &dest,
        userData->rot, nullptr,
        userData->isFlip ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

    // Update window
    SDL_RenderPresent(renderer);
}
