#pragma once

#include <SGE.h>

/// <summary>
/// 用户数据
/// </summary>
class T005_UserData {
public:
    // 初始化
    inline bool Init(SGE_App* app)
    {
        // 加载图像纹理
        texture = SGE_LoadTextureFile("test.bmp", app->GetRenderer());
        SGE_ERROR_RET_FALSE_IF(texture == nullptr, "Error SGE_LoadTextureFile.");
        return true;
    }

    // 销毁
    inline void Destroy()
    {
        SGE_SAFE_RELEASE(SDL_DestroyTexture, texture);
    }

public:
    SDL_Texture* texture = nullptr; // 纹理
    int mx = -1, my = -1; // 鼠标位置
    double rot = 0; // 旋转角度
    unsigned char r = 0, g = 0; // 颜色
    bool isFlip = false; // 是否翻转
};
