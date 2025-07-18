#pragma once

#include "T008_UserData.hpp"

#include <SGE.h>

// 用户数据，为了方便定义为全局变量
// 也可以放在 RunningLogic 类中作成员变量，
// 在 BeforeRun 中申请空间，在 AfterRun 中释放空间
T008_UserData ud;

/// <summary>
/// 本应用的运行逻辑
/// </summary>
class T008_RunningLogic : public SGE_RunningLogic {
public:
    // 构造函数
    T008_RunningLogic(SGE_App* app)
        : SGE_RunningLogic(app)
    {
    }

public:
    // 运行前处理
    inline bool BeforeRun() override
    {
        // 初始化用户数据
        SGE_ERROR_RET_FALSE_IF(!ud.Init(App()), "Error Init T008_UserData.");

        return true;
    }

    // 当前帧事件处理
    inline void FrameEvent(SDL_Event& e) override
    {
        switch (e.type) {
        case SDL_QUIT:
            App()->StopRunning();
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
                ud.squares.push_back(s);
            }

            break;
        }
    }

    // 当前帧更新处理
    inline void FrameUpdate(float delta_ms) override
    {
        // Gravity in pixels per second squared
        const float GRAVITY = 750.0f;

        // Physics loop 物理计算，依据时间差，不受帧率影响
        for (int index = 0; index < ud.squares.size(); index++) {
            square& s = ud.squares[index];

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
                ud.squares.erase(ud.squares.begin() + index);
                index--;
            }
        }
    }

    // 当前帧渲染处理
    inline void FrameRender(SDL_Renderer* renderer) override
    {
        // Render loop
        for (const square& s : ud.squares) {
            SDL_Rect dest = {
                static_cast<int>(round(s.x)),
                static_cast<int>(round(s.y)),
                static_cast<int>(round(s.w)),
                static_cast<int>(round(s.h))
            };
            SDL_RenderCopy(renderer, ud.box, nullptr, &dest);
        }
    }

    // 运行后处理
    inline void AfterRun() override
    {
        // 清理用户数据
        ud.Destroy();
    }
};
