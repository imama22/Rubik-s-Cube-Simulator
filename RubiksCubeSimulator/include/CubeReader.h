#ifndef CUBEREADER_H
#define CUBEREADER_H

#include "RubikCube.h"

class CubeReader
{
    public:
        CubeReader(RubikCube*);
        virtual ~CubeReader();
        void read(string, string, string, string, string, string);
    protected:
    private:
        RubikCube *cube;
};

#endif // CUBEREADER_H
