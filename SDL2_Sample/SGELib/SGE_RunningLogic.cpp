#include "SGE_RunningLogic.h"

// 构造函数
SGE_RunningLogic::SGE_RunningLogic(SGE_App* app)
    : m_app(app)
{
}

// 获取应用程序
SGE_App* SGE_RunningLogic::App() const
{
    return m_app;
}

// 运行前处理
bool SGE_RunningLogic::BeforeRun()
{
    return true;
}

// 当前帧开始
void SGE_RunningLogic::FrameBegin()
{
}

// 当前帧事件处理
// 默认的帧事件处理函数（仅实现了退出事件）
void SGE_RunningLogic::FrameEvent(SDL_Event& e)
{
    if (m_app == nullptr) {
        return;
    }
    switch (e.type) {
    case SDL_QUIT:
        m_app->StopRunning();
        break;
    }
}

// 当前帧更新处理
void SGE_RunningLogic::FrameUpdate(float delta_ms)
{
    SGE_UNREF_PARAM(delta_ms);
}

// 当前帧渲染处理
void SGE_RunningLogic::FrameRender(SDL_Renderer* renderer)
{
    SGE_UNREF_PARAM(renderer);
}

// 当前帧结束
void SGE_RunningLogic::FrameEnd()
{
}

// 当前帧应该等待多长时间(ms)
int SGE_RunningLogic::FrameDelayMs()
{
    return 16; // 大约60FPS
}

// 运行后处理
void SGE_RunningLogic::AfterRun()
{
}
