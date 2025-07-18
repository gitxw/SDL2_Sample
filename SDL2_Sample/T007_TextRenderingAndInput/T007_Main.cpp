#include "T007_RunningLogic.hpp"
#include "T007_UserData.hpp"

#include <SGE.h>

int main(int argc, char** args)
{
    // 初始化应用程序
    SGE_App app;
    if (!app.Init("T007测试")) {
        return -1;
    }

    // 定义逻辑对象
    T007_RunningLogic logic(&app);

    // 运行逻辑
    if (!app.RunLogic(&logic)) {
        return -2;
    }

    return 0;
}
