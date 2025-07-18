#pragma once

#include "T007_UserData.hpp"

#include <SGE.h>

// 用户数据，为了方便定义为全局变量
// 也可以放在 RunningLogic 类中作成员变量，
// 在 BeforeRun 中申请空间，在 AfterRun 中释放空间
T007_UserData ud;

/// <summary>
/// 本应用的运行逻辑
/// </summary>
class T007_RunningLogic : public SGE_RunningLogic {
public:
    // 构造函数
    T007_RunningLogic(SGE_App* app)
        : SGE_RunningLogic(app)
    {
    }

public:
    // 运行前处理
    inline bool BeforeRun() override
    {
        // 初始化用户数据
        SGE_ERROR_RET_FALSE_IF(!ud.Init(App()), "Error Init T007_UserData.");

        // Start sending SDL_TextInput events
        SDL_StartTextInput();

        return true;
    }

    // 当前帧事件处理
    inline void FrameEvent(SDL_Event& e) override
    {
        switch (e.type) {
        case SDL_QUIT:
            App()->StopRunning();
            break;
        case SDL_TEXTINPUT:
            ud.input += e.text.text;
            break;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_BACKSPACE && ud.input.size()) {
                // 删除中文字符时，可以整个字删除
                std::wstring input_u16 = SGE_Encoder::UTF8_To_UTF16(ud.input);
                input_u16.pop_back();
                ud.input = SGE_Encoder::UTF16_To_UTF8(input_u16);
            }
            break;
        }
    }

    // 当前帧渲染处理
    inline void FrameRender(SDL_Renderer* renderer) override
    {
        // Render texture
        SDL_RenderCopy(renderer, ud.texture, nullptr, nullptr);

        if (ud.input.size()) {
            SDL_Color foreground = { 0, 0, 0 }; // 文字颜色
            int w, h; // 文字尺寸
            // 创建字体纹理
            ud.text = SGE_CreateFontTexture(ud.font, ud.input, foreground, renderer, w, h);
            // 绘制纹理
            SDL_Rect dest = { static_cast<int>(320 - (w / 2.0f)), 240, w, h };
            SDL_RenderCopy(renderer, ud.text, nullptr, &dest);
            // 释放纹理
            SGE_SAFE_RELEASE(SDL_DestroyTexture, ud.text);
        }
    }

    // 运行后处理
    inline void AfterRun() override
    {
        // Stop sending SDL_TextInput events
        SDL_StopTextInput();

        // 清理用户数据
        ud.Destroy();
    }
};
