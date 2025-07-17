#include <SGE.h>

int main(int argc, char** args)
{
    // 初始化应用程序
    SGE_App app;
    if (!app.Init("T001测试")) {
        return -1;
    }

    // 执行应用程序
    app.Run();

    // 清理应用程序
    app.Destroy();

    return 0;
}
