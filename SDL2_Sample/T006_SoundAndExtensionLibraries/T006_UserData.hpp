#pragma once

#include <SGE.h>

/// <summary>
/// 用户数据
/// </summary>
class T006_UserData {
public:
    // 初始化
    inline bool Init(SGE_App* app)
    {
        // 加载图像纹理
        bg_img_texture = SGE_LoadTextureFile("test.png", app->GetRenderer());
        SGE_ERROR_RET_FALSE_IF(bg_img_texture == nullptr, "Error SGE_LoadTextureFile.");

        // Load music
        music = Mix_LoadMUS("music.wav");
        SGE_ERROR_RET_FALSE_IF(music == nullptr, "Error loading music:.%s", Mix_GetError());

        // Load sound
        sound = Mix_LoadWAV("scratch.wav");
        SGE_ERROR_RET_FALSE_IF(sound == nullptr, "Error loading sound: %s", Mix_GetError());

        // 加载字体 - 替换为你的中文字体文件路径
        const char* FONT_PATH = "STCAIYUN.TTF"; // 华文彩云，支持中文
        const int FONT_SIZE = 72;
        font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
        SGE_ERROR_RET_FALSE_IF(font == nullptr, "Failed to load font: %s", TTF_GetError());
        // 设置字体样式
        TTF_SetFontStyle(font, TTF_STYLE_BOLD);
        TTF_SetFontOutline(font, 1); // 设置1像素轮廓
        // 创建文字表面
        SDL_Color font_color = { 255, 0, 255, 255 }; // RGBA紫色
        SDL_Surface* blendedSurface = TTF_RenderUNICODE_Blended(font, (Uint16*)L"~ ABC主菜单 ~", font_color);
        SGE_ERROR_RET_FALSE_IF(blendedSurface == nullptr, "Failed to create blended text surface: %s", TTF_GetError());
        // 创建字体纹理
        ttf_texture = SDL_CreateTextureFromSurface(app->GetRenderer(), blendedSurface);
        SGE_ERROR_RET_FALSE_IF(ttf_texture == nullptr, "Failed to create blended texture: %s", TTF_GetError());
        // 设置文本位置
        ttf_rect = { 50, 50, blendedSurface->w, blendedSurface->h };
        // 释放表面（不再需要）
        SDL_FreeSurface(blendedSurface);

        return true;
    }

    // 销毁
    inline void Destroy()
    {
        // 销毁字体相关资源
        SGE_SAFE_RELEASE(SDL_DestroyTexture, ttf_texture);
        SGE_SAFE_RELEASE(TTF_CloseFont, font);

        // 销毁背景图像相关资源
        SGE_SAFE_RELEASE(SDL_DestroyTexture, bg_img_texture);

        // 销毁声音相关资源
        SGE_SAFE_RELEASE(Mix_FreeMusic, music);
        SGE_SAFE_RELEASE(Mix_FreeChunk, sound);
    }

public:
    SDL_Texture* bg_img_texture;
    Mix_Music* music;
    Mix_Chunk* sound;

    TTF_Font* font; // 字体
    SDL_Texture* ttf_texture; // 字体纹理
    SDL_Rect ttf_rect; // 字体位置
};
