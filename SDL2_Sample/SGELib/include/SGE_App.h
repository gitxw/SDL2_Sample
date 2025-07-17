#pragma once

#include <SDL.h>

#include <string>

/// <summary>
/// 应用程序类
/// </summary>
class SGE_App {
public:
    // 构造函数
    SGE_App();
    // 析构函数
    ~SGE_App();

    /// <summary>
    /// 初始化
    /// </summary>
    /// <param name="windowTitle">[IN] 窗口标题</param>
    /// <param name="windowRect">[IN] 窗口位置尺寸</param>
    /// <param name="windowFlags">[IN] 窗口样式，为 SDL_WindowFlags 的组合</param>
    /// <param name="rendererFlags">[IN] 渲染器样式，为 SDL_RendererFlags 的组合</param>
    /// <returns>是否成功</returns>
    bool Init(const std::string windowTitle = "SGE_App",
        const SDL_Rect& windowRect = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480 },
        Uint32 windowFlags = SDL_WINDOW_SHOWN,
        Uint32 rendererFlags = SDL_RENDERER_ACCELERATED);
    // 销毁（析构函数中自动调用）
    void Destroy();

    // 获取SDL窗口
    inline SDL_Window* GetWindow() const { return m_window; }
    // 获取SDL渲染器
    inline SDL_Renderer* GetRenderer() const { return m_renderer; }

private:
    SDL_Window* m_window; // SDL窗口
    SDL_Renderer* m_renderer; // SDL渲染器
};
