#include "RubikCube.h"

// default constructor
RubikCube::RubikCube()
{
	cubeSize = 2.0f;    // the size of the cube being drawn
    rotating = false;   // the cube does not rotate at first
    deg = 0;            // initialize the deg

    facets_buffer_data = new int[54];
    face_color_buffer_data = new int[54];
    resetCube();
}

// destructor
RubikCube::~RubikCube()
{
}

// apply the a sequence of moves
void RubikCube::applyMoves(string command)
{
    for (int i = 0; i < command.length(); ++i)
        applyMove(command[i], 1);
}

void RubikCube::applyMove(char _move, int time)
{
    rotating = true;
    for (int i = 0; i < time; ++i){
    switch (_move)
    {
        case 'U': rotateUpFaceClockwise(); break;
        case 'u': rotateUpFaceCounterClockwise(); break;
        case 'D': rotateDownFaceClockwise(); break;
        case 'd': rotateDownFaceCounterClockwise(); break;
        case 'F': rotateFrontFaceClockwise(); break;
        case 'f': rotateFrontFaceCounterClockwise(); break;
        case 'B': rotateBackFaceClockwise(); break;
        case 'b': rotateBackFaceCounterClockwise(); break;
        case 'L': rotateLeftFaceClockwise(); break;
        case 'l': rotateLeftFaceCounterClockwise(); break;
        case 'R': rotateRightFaceClockwise(); break;
        case 'r': rotateRightFaceCounterClockwise(); break;
        case 'X': rotateCubeX(); break;
        case 'Y': rotateCubeY(); break;
        case 'Z': rotateCubeZ(); break;
        case 'x': rotateCubeXCounterClockwise(); break;
        case 'y': rotateCubeYCounterClockwise(); break;
        case 'z': rotateCubeZCounterClockwise(); break;
    }
    }
}

void RubikCube::resetCube()
{
    for (int i = 0; i < 54; ++i)
        facets_buffer_data[i] = i;
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 9;  ++j)
    {
        face_color_buffer_data[i * 9 + j] = i;
    }
    drawCube('N');
}
