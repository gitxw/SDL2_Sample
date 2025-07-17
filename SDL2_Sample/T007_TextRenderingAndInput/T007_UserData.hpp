#pragma once

#include <SGE.h>

#include <string>

/// <summary>
/// 用户数据
/// </summary>
class T007_UserData {
public:
    // 初始化
    inline bool Init(SGE_App* app)
    {
        // 加载图像纹理
        texture = SGE_LoadTextureFile("test.png", app->GetRenderer());
        SGE_ERROR_RET_FALSE_IF(texture == nullptr, "Error SGE_LoadTextureFile.");

        // 加载字体 - 替换为你的中文字体文件路径
        const char* FONT_PATH = "msyh.ttc"; // 微软雅黑，支持中文
        const int FONT_SIZE = 72;
        font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
        SGE_ERROR_RET_FALSE_IF(font == nullptr, "Failed to load font: %s", TTF_GetError());

        return true;
    }

    // 销毁
    inline void Destroy()
    {
        // 销毁字体相关资源
        if (text != nullptr) {
            SDL_DestroyTexture(text);
            text = nullptr;
        }
        if (font != nullptr) {
            TTF_CloseFont(font);
            font = nullptr;
        }

        // 销毁背景图像相关资源
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }

public:
    SDL_Texture *texture, *text;
    TTF_Font* font;
    std::string input;
};
