#pragma once

#include "T005_UserData.hpp"

#include <SGE.h>

// 用户数据，为了方便定义为全局变量
// 也可以放在 RunningLogic 类中作成员变量，
// 在 BeforeRun 中申请空间，在 AfterRun 中释放空间
T005_UserData ud;

/// <summary>
/// 本应用的运行逻辑
/// </summary>
class T005_RunningLogic : public SGE_RunningLogic {
public:
    // 构造函数
    T005_RunningLogic(SGE_App* app)
        : SGE_RunningLogic(app)
    {
    }

public:
    // 运行前处理
    inline bool BeforeRun() override
    {
        // 初始化用户数据
        SGE_ERROR_RET_FALSE_IF(!ud.Init(App()), "Error Init T005_UserData.");

        return true;
    }

    // 当前帧事件处理
    inline void FrameEvent(SDL_Event& e) override
    {
        switch (e.type) {
        case SDL_QUIT:
            App()->StopRunning();
            break;
        case SDL_MOUSEMOTION:
            ud.mx = e.motion.x;
            ud.my = e.motion.y;
            break;
        }
    }

    // 当前帧更新处理
    inline void FrameUpdate(float delta_ms) override
    {
        if (ud.mx != -1) {
            // Distance across window
            float wpercent = ud.mx / 640.0f;
            float hpercent = ud.my / 480.0f;

            // Color
            ud.r = static_cast<unsigned char>(round(wpercent * 255));
            ud.g = static_cast<unsigned char>(round(hpercent * 255));

            ud.mx -= 320;
            ud.my -= 240;
            ud.rot = atan((float)ud.my / (float)ud.mx) * (180.0f / 3.14f);
            if (ud.mx < 0) {
                ud.rot -= 180;
            }
        }
        ud.mx = ud.my = -1;

        // 获取按键状态
        static const unsigned char* keys = SDL_GetKeyboardState(nullptr);
        // 根据按键状态，设置用户数据
        ud.isFlip = keys[SDL_SCANCODE_F]; // F键
    }

    // 当前帧渲染处理
    inline void FrameRender(SDL_Renderer* renderer) override
    {
        // Color mod (b will always be zero)
        SDL_SetTextureColorMod(ud.texture, ud.r, ud.g, 0);

        // Render texture
        SDL_Rect dest = { 240, 180, 160, 120 };
        SDL_RenderCopyEx(
            renderer, ud.texture, nullptr, &dest,
            ud.rot, nullptr,
            ud.isFlip ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    }

    // 运行后处理
    inline void AfterRun() override
    {
        // 清理用户数据
        ud.Destroy();
    }
};
