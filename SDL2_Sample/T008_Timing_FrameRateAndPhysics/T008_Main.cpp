#include "T008_RunningLogic.hpp"

#include <SGE.h>

int main(int argc, char** args)
{
    // 初始化应用程序
    SGE_App app;
    if (!app.Init("T008测试")) {
        return -1;
    }

    // 定义逻辑对象
    T008_RunningLogic logic(&app);

    // 运行逻辑
    if (!app.RunLogic(&logic)) {
        return -2;
    }

    return 0;
}
