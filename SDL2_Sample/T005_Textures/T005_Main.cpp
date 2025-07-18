#include "T005_RunningLogic.hpp"

#include <SGE.h>

int main(int argc, char** args)
{
    // 初始化应用程序
    SGE_App app;
    if (!app.Init("T005测试")) {
        return -1;
    }

    // 定义逻辑对象
    T005_RunningLogic logic(&app);

    // 运行逻辑
    if (!app.RunLogic(&logic)) {
        return -2;
    }

    return 0;
}
