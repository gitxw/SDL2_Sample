#include "T006_FrameFunctions.hpp"
#include "T006_UserData.hpp"

#include <SGE.h>

int main(int argc, char** args)
{
    // 初始化应用程序
    SGE_App app;
    if (!app.Init("T006测试")) {
        return -1;
    }

    // 初始化用户数据
    T006_UserData userData;
    if (!userData.Init(&app)) {
        return -2;
    }

    // Play music forever
    Mix_PlayMusic(userData.music, -1);

    // 执行应用程序
    app.Run(&userData, FrameEventFunc, FrameUpdateFunc, FrameRenderFunc);

    // 清理用户数据
    userData.Destroy();
    // 清理应用程序
    app.Destroy();

    return 0;
}
