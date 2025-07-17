#include "T004_Functions.h"
#include "T004_UserData.h"

// 事件处理函数
void EventFunction(SGE_Runner* runner, SDL_Event& e)
{
    SDL_assert(runner != nullptr);
    SDL_assert(runner->GetApp() != nullptr);
    SDL_assert(runner->GetUserData() != nullptr);

    // 取得用户数据
    T004_UserData* userData = static_cast<T004_UserData*>(runner->GetUserData());

    switch (e.type) {
    case SDL_QUIT:
        runner->StopRunning();
        break;
    case SDL_MOUSEBUTTONDOWN:
        userData->mx0 = e.button.x;
        userData->my0 = e.button.y;
        break;
    case SDL_MOUSEMOTION:
        userData->mx1 = e.button.x;
        userData->my1 = e.button.y;
        break;
    case SDL_MOUSEBUTTONUP:
        userData->mx0 = userData->my0 = userData->mx1 = userData->my1 = -1;
        break;
    }
}

// 更新处理函数
void UpdateFunction(SGE_Runner* runner, float delta_ms)
{
    SDL_assert(runner != nullptr);
    SDL_assert(runner->GetApp() != nullptr);
    SDL_assert(runner->GetUserData() != nullptr);

    // 取得用户数据
    T004_UserData* userData = static_cast<T004_UserData*>(runner->GetUserData());

    // 获取按键状态
    static const unsigned char* keys = SDL_GetKeyboardState(nullptr);
    // 根据按键状态，设置用户数据
    userData->isDrawPoint = keys[SDL_SCANCODE_1]; // 数字键1
    userData->isDrawLine = keys[SDL_SCANCODE_2]; // 数字键2
    userData->isDrawRect = keys[SDL_SCANCODE_3]; // 数字键3
}

// 渲染处理函数
void RenderFunction(SGE_Runner* runner)
{
    SDL_assert(runner != nullptr);
    SDL_assert(runner->GetApp() != nullptr);
    SDL_assert(runner->GetUserData() != nullptr);

    // 取得用户数据
    T004_UserData* userData = static_cast<T004_UserData*>(runner->GetUserData());
    // 取得渲染器
    SDL_Renderer* renderer = runner->GetApp()->GetRenderer();

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Set drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // 绘制点
    if (userData->isDrawPoint) {
        SDL_RenderDrawPoint(renderer, 10, 10);
    }
    // 绘制线
    if (userData->isDrawLine) {
        SDL_RenderDrawLine(renderer, 10, 20, 10, 100);
    }
    // 绘制实心矩形
    SDL_Rect r;
    if (userData->isDrawRect) {
        r.x = 20;
        r.y = 20;
        r.w = 100;
        r.h = 100;
        SDL_RenderFillRect(renderer, &r);
    }

    // 绘制鼠标空心矩形
    if (userData->mx0 != -1) {
        r.x = userData->mx0;
        r.y = userData->my0;
        r.w = userData->mx1 - userData->mx0;
        r.h = userData->my1 - userData->my0;
        SDL_RenderDrawRect(renderer, &r);
    }

    // Update window
    SDL_RenderPresent(renderer);
}
