#pragma once

#include "T006_UserData.hpp"

#include <SGE.h>

// 用户数据，为了方便定义为全局变量
// 也可以放在 RunningLogic 类中作成员变量，
// 在 BeforeRun 中申请空间，在 AfterRun 中释放空间
T006_UserData ud;

/// <summary>
/// 本应用的运行逻辑
/// </summary>
class T006_RunningLogic : public SGE_RunningLogic {
public:
    // 构造函数
    T006_RunningLogic(SGE_App* app)
        : SGE_RunningLogic(app)
    {
    }

public:
    // 运行前处理
    inline bool BeforeRun() override
    {
        // 初始化用户数据
        SGE_ERROR_RET_FALSE_IF(!ud.Init(App()), "Error Init T006_UserData.");

        // Play music forever
        Mix_PlayMusic(ud.music, -1);

        return true;
    }

    // 当前帧事件处理
    inline void FrameEvent(SDL_Event& e) override
    {
        switch (e.type) {
        case SDL_QUIT:
            App()->StopRunning();
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
            Mix_PlayChannel(-1, ud.sound, 0);
            break;
        }
    }

    // 当前帧渲染处理
    inline void FrameRender(SDL_Renderer* renderer) override
    {
        // Render bg_img_texture
        SDL_RenderCopy(renderer, ud.bg_img_texture, nullptr, nullptr);

        // 绘制ttf纹理
        SDL_RenderCopy(renderer, ud.ttf_texture, nullptr, &ud.ttf_rect);
    }

    // 运行后处理
    inline void AfterRun() override
    {
        // 清理用户数据
        ud.Destroy();
    }
};
