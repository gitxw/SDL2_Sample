#include "SGE_Functions.h"
#include "SGE_App.h"

#include <SDL_image.h>

// 默认的帧事件处理函数（仅实现了退出事件）
void DefaultFrameEventFunc(SGE_App* app, void* userData, SDL_Event& e)
{
    UNREF_PARAM(userData);

    if (app == nullptr) {
        return;
    }
    switch (e.type) {
    case SDL_QUIT:
        app->StopRunning();
        break;
    }
}

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
    SDL_FreeSurface(buffer);
    buffer = nullptr;
    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating texture: %s", SDL_GetError());
        return nullptr;
    }
    return texture;
}
