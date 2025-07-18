#include "T004_RunningLogic.hpp"

#include <SGE.h>

int main(int argc, char** args)
{
    // 创建应用程序并初始化
    SGE_App app;
    if (!app.Init("T004测试",
            { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 350, 350 },
            SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED)) {
        return -1;
    }

    // 定义逻辑对象
    T004_RunningLogic logic(&app);

    // 运行逻辑
    if (!app.RunLogic(&logic)) {
        return -2;
    }

    return 0;
}
