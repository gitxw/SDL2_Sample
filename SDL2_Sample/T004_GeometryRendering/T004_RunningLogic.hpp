#pragma once

#include "T004_UserData.hpp"

#include <SGE.h>

// 用户数据，为了方便定义为全局变量
// 也可以放在 RunningLogic 类中作成员变量，
// 在 BeforeRun 中申请空间，在 AfterRun 中释放空间
T004_UserData ud;

/// <summary>
/// 本应用的运行逻辑
/// </summary>
class T004_RunningLogic : public SGE_RunningLogic {
public:
    // 构造函数
    T004_RunningLogic(SGE_App* app)
        : SGE_RunningLogic(app)
    {
    }

public:
    // 当前帧事件处理
    inline void FrameEvent(SDL_Event& e) override
    {
        switch (e.type) {
        case SDL_QUIT:
            App()->StopRunning();
            break;
        case SDL_MOUSEBUTTONDOWN:
            ud.mx0 = e.button.x;
            ud.my0 = e.button.y;
            break;
        case SDL_MOUSEMOTION:
            ud.mx1 = e.button.x;
            ud.my1 = e.button.y;
            break;
        case SDL_MOUSEBUTTONUP:
            ud.mx0 = ud.my0 = ud.mx1 = ud.my1 = -1;
            break;
        }
    }

    // 当前帧更新处理
    inline void FrameUpdate(float delta_ms) override
    {
        // 获取按键状态
        static const unsigned char* keys = SDL_GetKeyboardState(nullptr);
        // 根据按键状态，设置用户数据
        ud.isDrawPoint = keys[SDL_SCANCODE_1]; // 数字键1
        ud.isDrawLine = keys[SDL_SCANCODE_2]; // 数字键2
        ud.isDrawRect = keys[SDL_SCANCODE_3]; // 数字键3
    }

    // 当前帧渲染处理
    inline void FrameRender(SDL_Renderer* renderer) override
    {
        // Set drawing color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // 绘制点
        if (ud.isDrawPoint) {
            SDL_RenderDrawPoint(renderer, 10, 10);
        }
        // 绘制线
        if (ud.isDrawLine) {
            SDL_RenderDrawLine(renderer, 10, 20, 10, 100);
        }
        // 绘制实心矩形
        SDL_Rect r;
        if (ud.isDrawRect) {
            r = { 20, 20, 100, 100 };
            SDL_RenderFillRect(renderer, &r);
        }

        // 绘制鼠标空心矩形
        if (ud.mx0 != -1) {
            r = { ud.mx0, ud.my0, ud.mx1 - ud.mx0, ud.my1 - ud.my0 };
            SDL_RenderDrawRect(renderer, &r);
        }
    }
};
