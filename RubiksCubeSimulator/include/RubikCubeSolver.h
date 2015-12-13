#ifndef RUBIKCUBESOLVER_H
#define RUBIKCUBESOLVER_H

#include "RubikCube.h"
#include <string>
#include <sstream>

using namespace std;

class RubikCubeSolver
{
    public:
        RubikCubeSolver();
        virtual ~RubikCubeSolver();

        // start solving the cube to the solved state after executing
        static string solveCube(RubikCube *cube);
    protected:
    private:
        /// HELPER-FUNCTIONS FOR ALGORITHM
        static void solveCross(RubikCube*);
        static void solveFirstLayer(RubikCube*);
        static void solveSecondLayer(RubikCube*);
        static void solveYellowCrossOLL(RubikCube*);
        static void solveYellowCross(RubikCube*);
        static void solveLastFace(RubikCube*);
        static void solveLastLayer(RubikCube*);

        static string moveRe;
};

#endif // RUBIKCUBESOLVER_H
