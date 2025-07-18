#pragma once

#include "T009_UserData.hpp"

#include <SGE.h>

// 用户数据，为了方便定义为全局变量
// 也可以放在 RunningLogic 类中作成员变量，
// 在 BeforeRun 中申请空间，在 AfterRun 中释放空间
T009_UserData ud;

/// <summary>
/// 本应用的运行逻辑
/// </summary>
class T009_RunningLogic : public SGE_RunningLogic {
public:
    // 构造函数
    T009_RunningLogic(SGE_App* app)
        : SGE_RunningLogic(app)
    {
    }

public:
    // 运行前处理
    inline bool BeforeRun() override
    {
        // 初始化用户数据
        SGE_ERROR_RET_FALSE_IF(!ud.Init(App()), "Error Init T009_UserData.");

        return true;
    }

    // 当前帧渲染处理
    inline void FrameRender(SDL_Renderer* renderer) override
    {
        Uint32 current = SDL_GetTicks();
        float dT = (current - ud.ss.lastUpdate) / 1000.0f;

        int framesToUpdate = static_cast<int>(floor(dT / (1.0f / sprite_fps)));
        if (framesToUpdate > 0) {
            ud.ss.lastFrame += framesToUpdate;
            ud.ss.lastFrame %= ud.ss.sprites.size();
            ud.ss.lastUpdate = current;
        }

        SDL_RenderCopy(renderer, ud.ss.texture, &ud.ss.sprites[ud.ss.lastFrame], nullptr);
    }

    // 运行后处理
    inline void AfterRun() override
    {
        // 清理用户数据
        ud.Destroy();
    }
};
