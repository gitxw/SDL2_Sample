#include "SGE_Functions.h"
#include "SGE_App.h"

#include <SDL_image.h>

// 加载图像并创建纹理
SDL_Texture* SGE_LoadTextureFile(const std::string& imgFilePath, SDL_Renderer* renderer)
{
    // 渲染器不能为空
    if (renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "renderer == nullptr");
        return nullptr;
    }

    // 加载图像
    SDL_Surface* buffer = IMG_Load(imgFilePath.c_str());
    if (buffer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error loading image %s: %s", imgFilePath.c_str(), SDL_GetError());
        return nullptr;
    }

    // 创建纹理
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, buffer);
    // 释放图像
    SGE_SAFE_RELEASE(SDL_FreeSurface, buffer);

    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating texture: %s", SDL_GetError());
        return nullptr;
    }
    return texture;
}

// 创建文本纹理
SDL_Texture* SGE_CreateFontTexture(TTF_Font* font, const std::string& text, const SDL_Color& font_color, SDL_Renderer* renderer, int& w, int& h)
{
    if (font == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Param Error: font == nullptr");
        return nullptr;
    }
    if (renderer == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Param Error: renderer == nullptr");
        return nullptr;
    }
    SDL_Surface* blendedSurface = TTF_RenderUTF8_Blended(font, text.c_str(), font_color);
    if (blendedSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create blended text surface: %s", TTF_GetError());
        return nullptr;
    }
    // 创建字体纹理
    SDL_Texture* ttf_texture = SDL_CreateTextureFromSurface(renderer, blendedSurface);
    if (ttf_texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create blended texture: %s", TTF_GetError());
        return nullptr;
    }
    // 设置文本尺寸
    w = blendedSurface->w;
    h = blendedSurface->h;
    // 释放表面（不再需要）
    SDL_FreeSurface(blendedSurface);

    return ttf_texture;
}
