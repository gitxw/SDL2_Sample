#pragma once

#include <SGE.h>

#include <string>
#include <vector>

const int sprite_width = 128;
const int sprite_height = 128;
const float sprite_fps = 24.0f;

struct spritesheet {
    SDL_Texture* texture;
    std::vector<SDL_Rect> sprites;
    Uint32 lastFrame, lastUpdate;
};

/// <summary>
/// 用户数据
/// </summary>
class T009_UserData {
public:
    // 初始化
    inline bool Init(SGE_App* app)
    {
        // 加载图像纹理
        SDL_Texture* texture = SGE_LoadTextureFile("sprites.png", app->GetRenderer());
        SGE_ERROR_RET_FALSE_IF(texture == nullptr, "Error SGE_LoadTextureFile.");

        ss.lastFrame = 0;
        ss.lastUpdate = SDL_GetTicks();
        ss.texture = texture;

        for (int j = 0; j < 16; j++) {
            for (int i = 0; i < 16; i++) {
                SDL_Rect r = { i * sprite_width, j * sprite_height, sprite_width, sprite_height };
                ss.sprites.push_back(r);
            }
        }

        return true;
    }

    // 销毁
    inline void Destroy()
    {
        ss.sprites.clear();

        // 销毁背景图像相关资源
        SGE_SAFE_RELEASE(SDL_DestroyTexture, ss.texture);
    }

public:
    spritesheet ss;
};
