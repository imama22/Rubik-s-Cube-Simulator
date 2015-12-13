#include <cmath>
#include <random>
#include <ctime>
#include <stdlib.h>
#include "CubeScrambler.h"

CubeScrambler::CubeScrambler(RubikCube c)
{
    cube = c;
}

CubeScrambler::~CubeScrambler()
{
    //dtor
}

string CubeScrambler::scramble(int n)
{
    string moveStr = "";
    srand(time(0));
    for (int i = 0; i < n; ++i)
    {
        int num = rand() % 6;
        if (num == 0)       moveStr += "U";
        else if (num == 1)  moveStr += "D";
        else if (num == 2)  moveStr += "F";
        else if (num == 3)  moveStr += "B";
        else if (num == 4)  moveStr += "L";
        else if (num == 5)  moveStr += "R";
    }
    cube.applyMoves(moveStr);
    return moveStr;
}
