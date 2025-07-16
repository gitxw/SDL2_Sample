#include "SGE_App.h"

#include <iostream>

// 初始化
bool SGE_App::Init()
{
    // 初始化SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    // 创建窗口
    m_window = SDL_CreateWindow(
        m_windowTitle.c_str(),
        m_windowRect.x, m_windowRect.y, m_windowRect.w, m_windowRect.h,
        m_windowFlags);
    if (nullptr == m_window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating window: %s", SDL_GetError());
        return false;
    }

    // 创建渲染器
    // 第2个参数设置-1，由SDL决定渲染后端
    // ----------------------------------------------------------
    // 平台       默认尝试顺序 (高→低优先级)
    // Windows    Direct3D 11 → Direct3D 9 → OpenGL → Software
    // macOS      Metal → OpenGL → Software
    // Linux      Vulkan → OpenGL → OpenGL ES → Software
    // Android    Vulkan → OpenGL ES 3 → OpenGL ES 2
    // ----------------------------------------------------------
    m_renderer = SDL_CreateRenderer(m_window, -1, m_rendererFlags);
    if (nullptr == m_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error creating renderer: %s", SDL_GetError());
        return false;
    }

    // 使用黑色清空窗口内容
    if (SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error SDL_SetRenderDrawColor: %s", SDL_GetError());
        return false;
    }
    if (SDL_RenderClear(m_renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error SDL_RenderClear: %s", SDL_GetError());
        return false;
    }

    return true;
}

// 销毁
void SGE_App::Destroy()
{
    // 销毁渲染器
    if (nullptr != m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    // 销毁窗口
    if (nullptr != m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    // 退出SDL
    SDL_Quit();
}
