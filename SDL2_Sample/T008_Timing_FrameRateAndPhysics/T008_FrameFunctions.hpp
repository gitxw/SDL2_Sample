#pragma once

#include "T008_UserData.hpp"

#include <SGE.h>

#include <string>

// 帧事件处理函数
void FrameEventFunc(SGE_App* app, void* userData, SDL_Event& e)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T008_UserData* ud = static_cast<T008_UserData*>(userData);

    switch (e.type) {
    case SDL_QUIT:
        app->StopRunning();
        break;
    case SDL_MOUSEBUTTONDOWN:
        for (int i = 0; i < 3; i++) {
            square s;
            s.x = static_cast<float>(e.button.x);
            s.y = static_cast<float>(e.button.y);
            s.w = static_cast<float>(rand() % 50 + 25);
            s.h = static_cast<float>(rand() % 50 + 25);
            s.yvelocity = -500.0f;
            s.xvelocity = static_cast<float>(rand() % 500 - 250);
            s.lastUpdate = SDL_GetTicks();
            s.born = SDL_GetTicks();
            ud->squares.push_back(s);
        }

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
    T008_UserData* ud = static_cast<T008_UserData*>(userData);

    // Gravity in pixels per second squared
    const float GRAVITY = 750.0f;

    // Physics loop 物理计算，依据时间差，不受帧率影响
    for (int index = 0; index < ud->squares.size(); index++) {
        square& s = ud->squares[index];

        Uint32 time = SDL_GetTicks();
        float dT = (time - s.lastUpdate) / 1000.0f;

        s.yvelocity += dT * GRAVITY;
        s.y += s.yvelocity * dT;
        s.x += s.xvelocity * dT;

        if (s.y > 480 - s.h) {
            s.y = 480 - s.h;
            s.xvelocity = 0;
            s.yvelocity = 0;
        }

        s.lastUpdate = time;
        if (s.lastUpdate > s.born + 5000) { // 生成5秒后消失
            ud->squares.erase(ud->squares.begin() + index);
            index--;
        }
    }
}

// 帧渲染函数
void FrameRenderFunc(SGE_App* app, void* userData)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T008_UserData* ud = static_cast<T008_UserData*>(userData);
    // 取得渲染器
    SDL_Renderer* renderer = app->GetRenderer();

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Render loop
    for (const square& s : ud->squares) {
        SDL_Rect dest = {
            static_cast<int>(round(s.x)),
            static_cast<int>(round(s.y)),
            static_cast<int>(round(s.w)),
            static_cast<int>(round(s.h))
        };
        SDL_RenderCopy(renderer, ud->box, nullptr, &dest);
    }

    // Update window
    SDL_RenderPresent(renderer);
}
