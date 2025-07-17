#include "T004_Functions.h"
#include "T004_UserData.h"

#include "SGE_App.h"
#include "SGE_Runner.h"

int main(int argc, char** args)
{
    // 创建应用程序并初始化
    SGE_App app("T004测试",
        { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 350, 350 },
        SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED);
    if (!app.Init()) {
        return -1;
    }

    // 运行
    T004_UserData userData;
    SGE_Runner runner(&app, &userData, EventFunction, UpdateFunction, RenderFunction);
    runner.Run();

    return 0;
}
