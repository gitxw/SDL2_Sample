#include "T006_RunningLogic.hpp"

#include <SGE.h>

int main(int argc, char** args)
{
    // 初始化应用程序
    SGE_App app;
    if (!app.Init("T006测试")) {
        return -1;
    }

    // 定义逻辑对象
    T006_RunningLogic logic(&app);

    // 运行逻辑
    if (!app.RunLogic(&logic)) {
        return -2;
    }

    return 0;
}
