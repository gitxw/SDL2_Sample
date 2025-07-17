#pragma once

#include "SGE_Runner.h"

#include <SDL.h>

// 事件处理函数
void EventFunction(SGE_Runner* runner, SDL_Event& e);

// 更新处理函数
void UpdateFunction(SGE_Runner* runner, float delta_ms);

// 渲染处理函数
void RenderFunction(SGE_Runner* runner);
