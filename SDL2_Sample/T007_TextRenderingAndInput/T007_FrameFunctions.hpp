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

    SDL_Color foreground = { 0, 0, 0 };

    if (ud->input.size()) {
        SDL_Surface* text_surf = TTF_RenderUTF8_Blended(ud->font, ud->input.c_str(), foreground); // 此函数支持中文
        ud->text = SDL_CreateTextureFromSurface(renderer, text_surf);

        SDL_Rect dest;
        dest.x = static_cast<int>(320 - (text_surf->w / 2.0f));
        dest.y = 240;
        dest.w = text_surf->w;
        dest.h = text_surf->h;
        SDL_RenderCopy(renderer, ud->text, nullptr, &dest);

        SDL_DestroyTexture(ud->text);
        SDL_FreeSurface(text_surf);
    }

    // Update window
    SDL_RenderPresent(renderer);
}
