#ifndef CUBESCRAMBLER_H
#define CUBESCRAMBLER_H

#include "RubikCube.h"
#include <string>

using namespace std;

class CubeScrambler
{
    public:
        CubeScrambler(RubikCube);
        virtual ~CubeScrambler();
        string scramble(int);
    protected:
    private:
        RubikCube cube;
};

#endif // CUBESCRAMBLER_H
