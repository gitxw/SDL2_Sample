#pragma once

#include "T007_UserData.hpp"

#include <SGE.h>

#include <string>

// 帧事件处理函数
void FrameEventFunc(SGE_App* app, void* userData, SDL_Event& e)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T007_UserData* ud = static_cast<T007_UserData*>(userData);

    switch (e.type) {
    case SDL_QUIT:
        app->StopRunning();
        break;
    case SDL_TEXTINPUT:
        ud->input += e.text.text;
        break;
    case SDL_KEYDOWN:
        if (e.key.keysym.sym == SDLK_BACKSPACE && ud->input.size()) {
            // 删除中文字符时，可以整个字删除
            std::wstring input_u16 = SGE_Encoder::UTF8_To_UTF16(ud->input);
            input_u16.pop_back();
            ud->input = SGE_Encoder::UTF16_To_UTF8(input_u16);
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
}

// 帧渲染函数
void FrameRenderFunc(SGE_App* app, void* userData)
{
    if (app == nullptr || userData == nullptr) {
        return;
    }
    // 取得用户数据
    T007_UserData* ud = static_cast<T007_UserData*>(userData);
    // 取得渲染器
    SDL_Renderer* renderer = app->GetRenderer();

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Render texture
    SDL_RenderCopy(renderer, ud->texture, nullptr, nullptr);

    if (ud->input.size()) {
        SDL_Color foreground = { 0, 0, 0 }; // 文字颜色
        int w, h; // 文字尺寸
        // 创建字体纹理
        ud->text = SGE_CreateFontTexture(ud->font, ud->input, foreground, renderer, w, h);
        // 绘制纹理
        SDL_Rect dest = { static_cast<int>(320 - (w / 2.0f)), 240, w, h };
        SDL_RenderCopy(renderer, ud->text, nullptr, &dest);
        // 释放纹理
        SGE_SAFE_RELEASE(SDL_DestroyTexture, ud->text);
    }

    // Update window
    SDL_RenderPresent(renderer);
}
