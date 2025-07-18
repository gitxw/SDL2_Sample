#pragma once

#include "SGE_App.h"

/*
运行逻辑基类，各个应用程序应继承此类，实现自己的逻辑
BeforeRun 运行一次
    帧循环
        +--FrameBegin
        +--FrameEvent
        +--FrameUpdate
        +--FrameRender
        +--FrameEnd
        +--FrameDelayMs
AfterRun 运行一次
*/
class SGE_RunningLogic {
public:
    // 构造函数
    SGE_RunningLogic(SGE_App* app);

    // 获取应用程序
    SGE_App* App() const;

public:
    // 运行前处理
    virtual bool BeforeRun();

    // 当前帧开始
    virtual void FrameBegin();

    // 当前帧事件处理
    virtual void FrameEvent(SDL_Event& e);
    // 当前帧更新处理
    virtual void FrameUpdate(float delta_ms);
    // 当前帧渲染处理
    virtual void FrameRender(SDL_Renderer* renderer);

    // 当前帧结束
    virtual void FrameEnd();

    // 执行下一帧前应该等待多长时间(ms)，重载此函数可改变帧率
    virtual int FrameDelayMs();

    // 运行后处理
    virtual void AfterRun();

private:
    SGE_App* m_app;
};
