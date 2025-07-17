#pragma once

#include <SDL.h>
#include <SGE.h>

// 帧事件处理函数
void FrameEventFunc(SGE_Runner* runner, SDL_Event& e);

// 帧更新函数
void FrameUpdateFunc(SGE_Runner* runner, float delta_ms);

// 帧渲染函数
void FrameRenderFunc(SGE_Runner* runner);
