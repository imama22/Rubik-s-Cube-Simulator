/*
 * @author Do Khuyen, 2015
 * RubikCube Class
 *
 */

#ifndef RubikCube_H
#define RubikCube_H

// OpenGL/SDL and some standard libraries
#include <random>
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glui.h>

// Some other libraries
#include "Permutation.h"

using namespace std;

class RubikCube
{
public:
	RubikCube();                    // constructor
	virtual ~RubikCube();           // destructor

    void applyMove(char, int);
    void applyMoves(string);
	void drawCube(char);
	void resetCube();
    int* ptr_facets_buffer_data(){return (int*) facets_buffer_data;}
    int* ptr_face_color_buffer_data() {return (int*) face_color_buffer_data;}
    bool isRotating() {return rotating;}
private:
    // rotation/move functions
    void rotateUpFaceClockwise();
    void rotateDownFaceClockwise();
    void rotateFrontFaceClockwise();
    void rotateBackFaceClockwise();
    void rotateLeftFaceClockwise();
    void rotateRightFaceClockwise();
    void rotateUpFaceCounterClockwise();
    void rotateDownFaceCounterClockwise();
    void rotateFrontFaceCounterClockwise();
    void rotateBackFaceCounterClockwise();
    void rotateLeftFaceCounterClockwise();
    void rotateRightFaceCounterClockwise();
    void rotateCubeX();
    void rotateCubeXCounterClockwise();
    void rotateCubeY();
    void rotateCubeYCounterClockwise();
    void rotateCubeZ();
    void rotateCubeZCounterClockwise();
    void rotateMiddle();
    void rotateUpMiddle();

    // private drawing functions
    void drawSolidCube(int*);
	void chooseColor(int);

    // private data fields
    float cubeSize;
    bool rotating;
    float deg;
    int* face_color_buffer_data;
    int* facets_buffer_data;

    // private static const data
    static int const face_cubie_buffer_data[6][9];
    static int const cubie_buffer_data[27][6];
};

#endif // RubikCube_H
