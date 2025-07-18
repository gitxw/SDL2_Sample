#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

class SGE_App;

// 未使用的函数形参，用于消除编译报警
#define SGE_UNREF_PARAM(x) (x);

// 安全的使用func释放资源obj
#define SGE_SAFE_RELEASE(func, obj) \
    do {                            \
        if (obj != nullptr) {       \
            func(obj);              \
            obj = nullptr;          \
        }                           \
    } while (0); // 使用do { ... } while(0)解决外部悬挂else问题

// 安全的释放指针
#define SGE_SAFE_DEL_POINT(p) \
    do {                      \
        if (p != nullptr) {   \
            delete p;         \
            p = nullptr;      \
        }                     \
    } while (0); // 使用do { ... } while(0)解决外部悬挂else问题

/**
 * @def SGE_ERROR_RET_FALSE_IF(expr, format, ...)
 * @brief 如果表达式为真，则记录错误并返回 false
 *
 * @param expr 要检查的表达式
 * @param format 格式化字符串（支持 printf 风格）
 * @param ... 格式化字符串对应的参数
 *
 * @return 如果表达式不为真则继续执行，否则返回 false
 */
#define SGE_ERROR_RET_FALSE_IF(expr, format, ...)                              \
    do {                                                                       \
        if (expr) {                                                            \
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, format, ##__VA_ARGS__); \
            return false;                                                      \
        }                                                                      \
    } while (0); // 使用do { ... } while(0)解决外部悬挂else问题

/// <summary>
/// 加载图像并创建纹理
/// </summary>
/// <param name="imgFilePath">[IN] 图像文件路径</param>
/// <param name="renderer">[IN] 渲染器</param>
/// <returns>纹理对象</returns>
SDL_Texture* SGE_LoadTextureFile(const std::string& imgFilePath, SDL_Renderer* renderer);

/// <summary>
/// 创建文本纹理
/// </summary>
/// <param name="font">[IN] 字体</param>
/// <param name="text">[IN] 文本</param>
/// <param name="font_color">[IN] 字体颜色</param>
/// <param name="renderer">[IN] 渲染器</param>
/// <param name="w">[OUT] 宽度(px)</param>
/// <param name="h">[OUT] 高度(px)</param>
/// <returns>纹理对象</returns>
SDL_Texture* SGE_CreateFontTexture(TTF_Font* font, const std::string& text, const SDL_Color& font_color, SDL_Renderer* renderer, int& w, int& h);
