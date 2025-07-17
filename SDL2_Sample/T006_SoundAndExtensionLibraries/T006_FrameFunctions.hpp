#pragma once

#include "T006_UserData.hpp"

#include <SGE.h>

// 帧事件处理函数
void FrameEventFunc(SGE_App* app, void* userData, SDL_Event& e)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T006_UserData* ud = static_cast<T006_UserData*>(userData);

    switch (e.type) {
    case SDL_QUIT:
        app->StopRunning();
        break;
    case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_SPACE) {
            if (Mix_PausedMusic() == 1) {
                Mix_ResumeMusic();
            } else {
                Mix_PauseMusic();
            }
        } else if (e.key.keysym.sym == SDLK_ESCAPE) {
            Mix_HaltMusic();
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        // Play sound once on the first available channel
        Mix_PlayChannel(-1, ud->sound, 0);
        break;
    }
}

// 帧更新函数
void FrameUpdateFunc(SGE_App* app, void* userData, float delta_ms)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
}

// 帧渲染函数
void FrameRenderFunc(SGE_App* app, void* userData)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T006_UserData* ud = static_cast<T006_UserData*>(userData);
    // 取得渲染器
    SDL_Renderer* renderer = app->GetRenderer();

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Render bg_img_texture
    SDL_RenderCopy(renderer, ud->bg_img_texture, nullptr, nullptr);

    // 绘制ttf纹理
    SDL_RenderCopy(renderer, ud->ttf_texture, nullptr, &ud->ttf_rect);

    // Update window
    SDL_RenderPresent(renderer);
}
