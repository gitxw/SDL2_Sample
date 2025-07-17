#pragma once

#include <SDL.h>

#include <string>

class SGE_App;

// 未使用的函数形参，用于消除编译报警
#define UNREF_PARAM(x) (x);

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
/// 默认的帧事件处理函数（仅实现了退出事件）
/// </summary>
/// <param name="app">[IN] 应用程序</param>
/// <param name="userData">[IN] 用户数据</param>
/// <param name="e">[IN] SDL事件对象</param>
void DefaultFrameEventFunc(SGE_App* app, void* userData, SDL_Event& e);

/// <summary>
/// 加载图像并创建纹理
/// </summary>
/// <param name="imgFilePath">[IN] 图像文件路径</param>
/// <param name="renderer">[IN] 渲染器</param>
/// <returns>纹理对象</returns>
SDL_Texture* SGE_LoadTextureFile(const std::string& imgFilePath, SDL_Renderer* renderer);
