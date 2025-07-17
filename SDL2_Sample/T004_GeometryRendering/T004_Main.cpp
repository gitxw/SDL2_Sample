#include "T004_FrameFunctions.hpp"
#include "T004_UserData.hpp"

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

    // 定义用户数据
    T004_UserData userData;

    // 运行
    app.Run(&userData, FrameEventFunc, FrameUpdateFunc, FrameRenderFunc);

    // 清理应用程序
    app.Destroy();

    return 0;
}
