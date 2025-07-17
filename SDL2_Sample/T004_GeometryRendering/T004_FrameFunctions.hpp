#pragma once

#include <SGE.h>

#include "T004_UserData.hpp"

// 帧事件处理函数
void FrameEventFunc(SGE_App* app, void* userData, SDL_Event& e)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }

    // 取得用户数据
    T004_UserData* ud = static_cast<T004_UserData*>(userData);

    switch (e.type) {
    case SDL_QUIT:
        app->StopRunning();
        break;
    case SDL_MOUSEBUTTONDOWN:
        ud->mx0 = e.button.x;
        ud->my0 = e.button.y;
        break;
    case SDL_MOUSEMOTION:
        ud->mx1 = e.button.x;
        ud->my1 = e.button.y;
        break;
    case SDL_MOUSEBUTTONUP:
        ud->mx0 = ud->my0 = ud->mx1 = ud->my1 = -1;
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
    T004_UserData* ud = static_cast<T004_UserData*>(userData);

    // 获取按键状态
    static const unsigned char* keys = SDL_GetKeyboardState(nullptr);
    // 根据按键状态，设置用户数据
    ud->isDrawPoint = keys[SDL_SCANCODE_1]; // 数字键1
    ud->isDrawLine = keys[SDL_SCANCODE_2]; // 数字键2
    ud->isDrawRect = keys[SDL_SCANCODE_3]; // 数字键3
}

// 帧渲染函数
void FrameRenderFunc(SGE_App* app, void* userData)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T004_UserData* ud = static_cast<T004_UserData*>(userData);
    // 取得渲染器
    SDL_Renderer* renderer = app->GetRenderer();

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Set drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // 绘制点
    if (ud->isDrawPoint) {
        SDL_RenderDrawPoint(renderer, 10, 10);
    }
    // 绘制线
    if (ud->isDrawLine) {
        SDL_RenderDrawLine(renderer, 10, 20, 10, 100);
    }
    // 绘制实心矩形
    SDL_Rect r;
    if (ud->isDrawRect) {
        r.x = 20;
        r.y = 20;
        r.w = 100;
        r.h = 100;
        SDL_RenderFillRect(renderer, &r);
    }

    // 绘制鼠标空心矩形
    if (ud->mx0 != -1) {
        r.x = ud->mx0;
        r.y = ud->my0;
        r.w = ud->mx1 - ud->mx0;
        r.h = ud->my1 - ud->my0;
        SDL_RenderDrawRect(renderer, &r);
    }

    // Update window
    SDL_RenderPresent(renderer);
}
