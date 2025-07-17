#pragma once

#include <SDL.h>

#include <string>

/// <summary>
/// 加载图像并创建纹理
/// </summary>
/// <param name="imgFilePath">[IN] 图像文件路径</param>
/// <param name="renderer">[IN] 渲染器</param>
/// <returns>纹理对象</returns>
SDL_Texture* SGE_LoadTextureFile(const std::string& imgFilePath, SDL_Renderer* renderer);
