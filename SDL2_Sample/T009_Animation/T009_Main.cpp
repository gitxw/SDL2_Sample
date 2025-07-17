#include "T009_FrameFunctions.hpp"
#include "T009_UserData.hpp"

#include <SGE.h>

int main(int argc, char** args)
{
    // 初始化应用程序
    SGE_App app;
    if (!app.Init("T009测试")) {
        return -1;
    }

    // 初始化用户数据
    T009_UserData userData;
    if (!userData.Init(&app)) {
        return -2;
    }

    // 执行应用程序
    app.Run(&userData, FrameEventFunc, FrameUpdateFunc, FrameRenderFunc);

    // 清理用户数据
    userData.Destroy();
    // 清理应用程序
    app.Destroy();

    return 0;
}
