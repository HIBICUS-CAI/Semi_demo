#include <iostream>
#include "GameSys.h"

int main()
{
    std::cout << "开始执行游戏" << std::endl;

    GameSys gameSys;

    bool success = gameSys.InitGame();

    if (success)
    {
        gameSys.RunLoop();
    }

    gameSys.Shutdown();

    return 0;
}
