#ifndef MySolver_H
#define MySolver_H

#include "RubikCube.h"
#include <string>
#include <sstream>

using namespace std;

class MySolver
{
    public:
        MySolver();
        virtual ~MySolver();

        // start solving the cube to the solved state after executing
        static string solveCube(RubikCube*);
    protected:
    private:
        /// HELPER-FUNCTIONS FOR ALGORITHM
        static void solveWhiteCross(RubikCube*);
        static void FLLReduction(RubikCube*);
        static void solveYellowCrossOLL(RubikCube*);
        static void solveYellowCross(RubikCube*);
        static void solveLastFace(RubikCube*);
        static void solveLastLayer(RubikCube*);

        static string moveRe;
};

#endif // MySolver_H
