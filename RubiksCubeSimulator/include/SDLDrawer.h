/*
 * @author Do Khuyen, 2015
 * SDLDrawer Class
 *
 * The class inludes all functions and features for creating a drawing
 * window, take the constructor input as a Cube to be drawn on the
 * surface.
 *
 */

#ifndef SDLDrawer_H
#define SDLDrawer_H

// SDL, OpenGL libraries
#include <windows.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <Gl/glui.h>

// other libraries
#include "RubikCubeSolver.h"
#include "MySolver.h"
#include "CubeScrambler.h"
#include "CubeReader.h"
#include <string>
#include <iostream>

using namespace std;

class SDLDrawer
{
    public:
        SDLDrawer(RubikCube);
        virtual ~SDLDrawer();
        void onExecute();
        void setTranslateSystem(float, float, float);
    protected:
    private:
        void onEvent(SDL_Event* evnt);          // read inputs and process external events
        bool onInit();                          // initialize SDL and set up everything for display
        void onCleanup();                       // cleanup event after SDL is shut down
        void onRender(char);                    // render image on display
        void applyMoves(string);                // apply a sequence of moves on the Cube
        void readKeyboardInput();               // read input from keyboard
        void displayAppMenu();
        void displayAppTitle();

        enum APPSTATE { ON, OFF };
        RubikCube cube;
        CubeScrambler *scrambler;
        CubeReader *reader;
        APPSTATE appState;
        string macroHistory = "";
        float delayTime = 10;
        float* system_rotate_buffer_data;
        float* system_translate_buffer_data;
};

#endif // SDLDrawer_H
