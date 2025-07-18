#include "T009_RunningLogic.hpp"

#include <SGE.h>

int main(int argc, char** args)
{
    // 初始化应用程序
    SGE_App app;
    if (!app.Init("T009测试")) {
        return -1;
    }

    // 定义逻辑对象
    T009_RunningLogic logic(&app);

    // 运行逻辑
    if (!app.RunLogic(&logic)) {
        return -2;
    }

    return 0;
}
