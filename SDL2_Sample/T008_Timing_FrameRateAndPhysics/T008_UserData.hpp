#pragma once

#include <SGE.h>

#include <string>
#include <vector>

struct square {
    float x, y, w, h, xvelocity, yvelocity;
    Uint32 born, lastUpdate;
};

/// <summary>
/// 用户数据
/// </summary>
class T008_UserData {
public:
    // 初始化
    inline bool Init(SGE_App* app)
    {
        // 加载图像纹理
        box = SGE_LoadTextureFile("box.jpg", app->GetRenderer());
        SGE_ERROR_RET_FALSE_IF(box == nullptr, "Error SGE_LoadTextureFile.");

        // 加载字体
        const char* FONT_PATH = "font.ttf";
        const int FONT_SIZE = 24;
        font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
        SGE_ERROR_RET_FALSE_IF(font == nullptr, "Failed to load font: %s", TTF_GetError());

        return true;
    }

    // 销毁
    inline void Destroy()
    {
        // 销毁字体相关资源
        SGE_SAFE_RELEASE(TTF_CloseFont, font);

        // 销毁背景图像相关资源
        SGE_SAFE_RELEASE(SDL_DestroyTexture, box);
    }

public:
    SDL_Texture* box;
    TTF_Font* font;

    // Physics squares
    std::vector<square> squares;
};
