#pragma once

#include "SGE_App.h"

#include <functional>

/// <summary>
/// 运行器类
/// </summary>
class SGE_Runner {
public:
    // 构造函数
    inline SGE_Runner(
        SGE_App* app,
        void* userData = nullptr,
        std::function<void(SGE_Runner* runner, SDL_Event& e)> frameEventFunc = nullptr,
        std::function<void(SGE_Runner* runner, float delta_ms)> frameUpdateFunc = nullptr,
        std::function<void(SGE_Runner* runner)> frameRenderFunc = nullptr)
    {
        m_app = app;
        m_userData = userData;
        m_frameEventFunc = frameEventFunc;
        m_frameUpdateFunc = frameUpdateFunc;
        m_frameRenderFunc = frameRenderFunc;
        m_isRunning = false;
    }
    // 析构函数
    inline ~SGE_Runner() { }

    // 运行
    void Run();

    // 获取应用程序
    inline SGE_App* GetApp() { return m_app; }

    // 获取用户数据
    inline void* GetUserData() { return m_userData; }

    // 获取运行状态
    inline bool IsRunning() const { return m_isRunning; }
    // 停止运行
    inline void StopRunning() { m_isRunning = false; }

private:
    SGE_App* m_app; // 应用程序
    void* m_userData; // 用户数据
    std::function<void(SGE_Runner* runner, SDL_Event& e)> m_frameEventFunc; // 帧事件处理函数
    std::function<void(SGE_Runner* runner, float delta_ms)> m_frameUpdateFunc; // 帧更新函数
    std::function<void(SGE_Runner* runner)> m_frameRenderFunc; // 帧渲染函数
    bool m_isRunning; // 是否正在运行
};
