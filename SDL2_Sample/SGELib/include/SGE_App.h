#pragma once

#include <SDL.h>

#include <string>

/// <summary>
/// 应用程序类
/// </summary>
class SGE_App {
public:
    /// <summary>
    /// 构造函数
    /// </summary>
    /// <param name="windowTitle">[IN] 窗口标题</param>
    /// <param name="windowRect">[IN] 窗口位置尺寸</param>
    /// <param name="windowFlags">[IN] 窗口样式，为 SDL_WindowFlags 的组合</param>
    /// <param name="rendererFlags">[IN] 渲染器样式，为 SDL_RendererFlags 的组合</param>
    inline SGE_App(
        const std::string windowTitle = "SGE_App",
        const SDL_Rect& windowRect = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480 },
        Uint32 windowFlags = SDL_WINDOW_SHOWN,
        Uint32 rendererFlags = SDL_RENDERER_ACCELERATED)
        : m_windowTitle(windowTitle)
        , m_windowRect(windowRect)
        , m_windowFlags(windowFlags)
        , m_rendererFlags(rendererFlags)
        , m_window(nullptr)
        , m_renderer(nullptr)
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SGE_App constructor.");
    }
    /// <summary>
    /// 析构函数
    /// </summary>
    inline ~SGE_App()
    {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SGE_App destructor.");
        Destroy();
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SGE_App destoryed.");
    }

    // 获取窗口标题
    inline std::string GetWindowTitle() const { return m_windowTitle; }
    // 设置窗口标题
    inline void SetWindowTitle(const std::string& windowTitle) { m_windowTitle = windowTitle; }

    // 获取窗口位置尺寸
    inline SDL_Rect GetWindowRect() const { return m_windowRect; }
    // 设置窗口位置尺寸
    inline void SetWindowRect(const SDL_Rect& windowRect) { m_windowRect = windowRect; }

    // 获取窗口样式（SDL_WindowFlags）
    inline Uint32 GetWindowFlags() const { return m_windowFlags; }
    // 设置窗口样式（SDL_WindowFlags）
    inline void SetWindowFlags(Uint32 windowFlags) { m_windowFlags = windowFlags; }

    // 获取渲染器样式（SDL_RendererFlags）
    inline Uint32 GetRendererFlags() const { return m_rendererFlags; }
    // 设置渲染器样式（SDL_RendererFlags）
    inline void SetRendererFlags(Uint32 rendererFlags) { m_rendererFlags = rendererFlags; }

    // 初始化
    bool Init();
    // 销毁
    void Destroy();

    // 获取SDL窗口
    inline SDL_Window* GetWindow() const { return m_window; }
    // 获取SDL渲染器
    inline SDL_Renderer* GetRenderer() const { return m_renderer; }

private:
    std::string m_windowTitle; // 窗口标题
    SDL_Rect m_windowRect; // 窗口位置尺寸
    Uint32 m_windowFlags; // 窗口样式
    Uint32 m_rendererFlags; // 渲染器样式

    SDL_Window* m_window; // SDL窗口
    SDL_Renderer* m_renderer; // SDL渲染器
};
