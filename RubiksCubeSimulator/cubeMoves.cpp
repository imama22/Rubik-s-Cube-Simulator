/*
 *
 */

#include "RubikCube.h"

/*  Basic moves used in the program and also in the thesis
 *  U:	The rotation of up face a quarter-turn clockwise.
 *  D:	The rotation of down face a quarter-turn clockwise.
 *  F:	The rotation of front face a quarter-turn clockwise.
 *  B:	The rotation of back face a quarter-turn clockwise.
 *  L:	The rotation of left face a quarter-turn clockwise.
 *  R:	The rotation of right face a quarter-turn clockwise.
 *  u:	The rotation of up face a quarter-turn counter-clockwise.
 *  d:	The rotation of down face a quarter-turn counter-clockwise.
 *  f:	The rotation of front face a quarter-turn counter-clockwise.
 *  b:	The rotation of back face a quarter-turn counter-clockwise.
 *  l:	The rotation of left face a quarter-turn counter-clockwise.
 *  r:	The rotation of right face a quarter-turn counter-clockwise.
 *  U2:	The rotation of up face 1800 clockwise.
 *  D2:	The rotation of down face 1800 clockwise.
 *  F2:	The rotation of front face 1800 clockwise.
 *  B2:	The rotation of back face 1800 clockwise.
 *  L2:	The rotation of left face 1800 clockwise.
 *  R2:	The rotation of right face 1800 clockwise.
 *  X:	The rotation of the entire cube as if doing an R turn.
 *  Y:	The rotation of the entire cube as if doing a U turn.
 *  Z:	The rotation of the whole cube as if doing an F turn.
 *  x:	The rotation of the whole cube as if doing an r turn.
 *  y:	The rotation of the whole cube as if doing a u turn.
 *  z:	The rotation of the whole cube as if doing an f turn.
 */

// The up face move clockwise
void RubikCube::rotateUpFaceClockwise()
{
    int arr[5][4] = {{0, 2, 8, 6},
                    {1, 5, 7, 3},
                    {19, 37, 28, 46},
                    {18, 36, 27, 45},
                    {20, 38, 29, 47},};
    Permutation::MulPermute((int*)facets_buffer_data, (int*)arr, 4, 5);
    Permutation::MulPermute((int*)face_color_buffer_data,(int*)arr, 4, 5);
}

// The up face move counter clockwise
void RubikCube::rotateUpFaceCounterClockwise()
{
    for (int i = 0; i < 3; ++i)
        rotateUpFaceClockwise();
}

// The downface move clockwise
void RubikCube::rotateDownFaceClockwise()
{
    int arr[5][4] = {{9, 11, 17, 15},
                    {10, 14, 16, 12},
                    {24, 51, 33, 42},
                    {25, 52, 34, 43},
                    {26, 53, 35, 44},};
    Permutation::MulPermute((int*)facets_buffer_data, (int*)arr, 4, 5);
    Permutation::MulPermute((int*)face_color_buffer_data, (int*)arr, 4, 5);
}

// the down face move counter clockwise
void RubikCube::rotateDownFaceCounterClockwise()
{
    for (int i = 0; i < 3; ++i)
        rotateDownFaceClockwise();
}

// The front-face move clockwise
void RubikCube::rotateFrontFaceClockwise()
{
    int arr[5][4] = {{18, 20, 26, 24},
                    {19, 23, 25, 21},
                    {6, 45, 11, 44},
                    {7, 48, 10, 41},
                    {8, 51, 9, 38},};
    Permutation::MulPermute((int*)facets_buffer_data, (int*)arr, 4, 5);
    Permutation::MulPermute((int*)face_color_buffer_data, (int*)arr, 4, 5);
}

void RubikCube::rotateFrontFaceCounterClockwise()
{
    for (int i = 0; i < 3; ++i)
        rotateFrontFaceClockwise();
}

/************* The back-face move *************/
void RubikCube::rotateBackFaceClockwise()
{
    int arr[5][4] = {{27, 29, 35, 33},
                    {28, 32, 34, 30},
                    {0, 42, 17, 47},
                    {1, 39, 16, 50},
                    {2, 36, 15, 53},};
    Permutation::MulPermute((int*)facets_buffer_data, (int*)arr, 4, 5);
    Permutation::MulPermute((int*)face_color_buffer_data, (int*)arr, 4, 5);
}

void RubikCube::rotateBackFaceCounterClockwise()
{
    for (int i = 0; i < 3; ++i)
        rotateBackFaceClockwise();
}

/*********** The left-face move ********************/
void RubikCube::rotateLeftFaceClockwise()
{
    int arr[5][4] = {{36, 38, 44, 42},
                    {37, 41, 43, 39},
                    {0, 18, 9, 35},
                    {3, 21, 12, 32},
                    {6, 24, 15, 29},};
    Permutation::MulPermute((int*)facets_buffer_data, (int*)arr, 4, 5);
    Permutation::MulPermute((int*)face_color_buffer_data, (int*)arr, 4, 5);
}

void RubikCube::rotateLeftFaceCounterClockwise()
{
    for (int i = 0; i < 3; ++i)
        rotateLeftFaceClockwise();
}

/************* The right-face move ************/
void RubikCube::rotateRightFaceClockwise()
{
    int arr[5][4] = {{45, 47, 53, 51},
                    {46, 50, 52, 48},
                    {17, 26, 8, 27},
                    {14, 23, 5, 30},
                    {11, 20, 2, 33},};
    Permutation::MulPermute((int*)facets_buffer_data, (int*)arr, 4, 5);
    Permutation::MulPermute((int*)face_color_buffer_data, (int*)arr, 4, 5);
}

void RubikCube::rotateRightFaceCounterClockwise()
{
    for (int i = 0; i < 3; ++i)
        rotateRightFaceClockwise();
}

/*********** Rotate Cube Up *******************/
void RubikCube::rotateCubeX()
{
    rotateRightFaceClockwise();
    rotateUpMiddle();
    rotateLeftFaceCounterClockwise();
}

void RubikCube::rotateCubeXCounterClockwise()
{
    for (int i = 0; i < 3; ++i)
        rotateCubeX();
}

/************* Rotate Cube Clockwise ************/
void RubikCube::rotateCubeY()
{
    rotateUpFaceClockwise();
    rotateMiddle();
    rotateDownFaceCounterClockwise();
}

void RubikCube::rotateCubeYCounterClockwise()
{
    for (int i = 0; i < 3; ++i)
        rotateCubeY();
}

/************ Rotate Cube Counter-Clockwise *********/
void RubikCube::rotateCubeZ()
{
    rotateCubeY();
    rotateCubeXCounterClockwise();
    rotateCubeYCounterClockwise();
}

void RubikCube::rotateCubeZCounterClockwise()
{
    for (int i = 0; i < 3; ++i)
        rotateCubeZ();
}

/******** Move the middle layer clockwise a quarter ***********/
void RubikCube::rotateMiddle()
{
    int arr[3][4] = {{22, 40, 31, 49},
                    {21, 39, 30, 48},
                    {23, 41, 32, 50},};
    Permutation::MulPermute((int*)facets_buffer_data, (int*)arr, 4, 3);
    Permutation::MulPermute((int*)face_color_buffer_data, (int*)arr, 4, 3);
}

void RubikCube::rotateUpMiddle()
{
    int arr[3][4] = {{16, 25, 7, 28},
                    {13, 22, 4, 31},
                    {10, 19, 1, 34},};
    Permutation::MulPermute((int*)facets_buffer_data, (int*)arr, 4, 3);
    Permutation::MulPermute((int*)face_color_buffer_data, (int*)arr, 4, 3);
}

