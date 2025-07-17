#include "SGE_App.h"
#include <SDL.h>
#include <iostream>

using namespace std;

bool loop(SGE_App* app);

int main(int argc, char** args)
{
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Application start.");

    SGE_App app("T004测试", { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768 }, SDL_WINDOW_SHOWN);

    if (!app.Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SGE_App::Init() failed.");
        return -1;
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SGE_App::Init() successfully.");

    /*
    OnCheck_Key_1_Pressing(app, data, is_pressing);
    OnCheck_Key_2_Pressing(app, data, is_pressing);
    OnCheck_Key_3_Pressing(app, data, is_pressing);
    OnKeyDown(app, data, e);
    OnKeyUp(app, data, e);
    On_Key_D_Down(app, data, e);
    On_Key_D_Up(app, data, e);
    OnMouseButtonDown(app, data, e);
    On_LBM_Down(app, data, e);
    On_LBM_Up(app, data, e);
    On_MouseMove(app, data, e);

    SGE_EventHandler ev_handler(&app, &data);
    ev_handler.RegisterCheckKeyPressingEvent(SDL_SCANCODE_1, OnCheck_Key_1_Pressing);
    ev_handler.RegisterCheckKeyPressingEvent(SDL_SCANCODE_1, OnCheck_Key_1_Pressing);
    ev_handler.RegisterCheckKeyPressingEvent(SDL_SCANCODE_1, OnCheck_Key_1_Pressing);
    ev_handler.RegisterKeyboardEvent(SGE_KEY_DOWN, SDL_SCANCODE_D, On_Key_D_Down);
    ev_handler.RegisterKeyboardEvent(SGE_KEY_UP, SDL_SCANCODE_D, On_Key_D_Up);
    ev_handler.RegisterMouseLeftButtonDownEvent(On_LBM_Down);
    ev_handler.RegisterMouseLeftButtonUpEvent(On_LBM_Up);
    ev_handler.RegisterMouseMoveEvent(On_MouseMove);

    update_function(app, data, delta_ms);
    render_function(app, data);

    SGE_Runner runner(&app, &ev_handler, update_function, render_function);
    runner.Run();
    */

    while (loop(&app)) {
        // wait before processing the next frame
        SDL_Delay(10);
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Application stop.");
    return 0;
}

bool loop(SGE_App* app)
{
    SDL_Renderer* renderer = app->GetRenderer();
    static const unsigned char* keys = SDL_GetKeyboardState(NULL);

    SDL_Event e;
    SDL_Rect r;
    //  For mouse rectangle (static to presist between function calls)
    static int mx0 = -1, my0 = -1, mx1 = -1, my1 = -1;

    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Event loop
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            return false;
        case SDL_MOUSEBUTTONDOWN:
            mx0 = e.button.x;
            my0 = e.button.y;
            break;
        case SDL_MOUSEMOTION:
            mx1 = e.button.x;
            my1 = e.button.y;
            break;
        case SDL_MOUSEBUTTONUP:
            mx0 = my0 = mx1 = my1 = -1;
            break;
        }
    }

    // Set drawing color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Test key states - this could also be done with events
    if (keys[SDL_SCANCODE_1]) { // 数字键1
        SDL_RenderDrawPoint(renderer, 10, 10); // 绘制点
    }
    if (keys[SDL_SCANCODE_2]) { // 数字键2
        SDL_RenderDrawLine(renderer, 10, 20, 10, 100); // 绘制线
    }
    if (keys[SDL_SCANCODE_3]) { // 数字键3
        r.x = 20;
        r.y = 20;
        r.w = 100;
        r.h = 100;
        SDL_RenderFillRect(renderer, &r); // 绘制实心矩形
    }

    // Render mouse rectangle
    if (mx0 != -1) {
        r.x = mx0;
        r.y = my0;
        r.w = mx1 - mx0;
        r.h = my1 - my0;
        SDL_RenderDrawRect(renderer, &r); // 绘制空心矩形
    }

    // Update window
    SDL_RenderPresent(renderer);

    return true;
}
