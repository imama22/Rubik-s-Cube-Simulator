/******************************************************
 *      Rubik's Cube Simulator
 *      @DoKhuyen 2015, Finand
 *      Information Technology DP
 *      Centria University of Applied Sciences
 *      Unit of Kokkola-Pietarsaari
 ******************************************************/

/*
 * This is my degree project at Centria University of Applied Sciences,
 * Finland. The simulator provides all the necessary features for
 * implementing and testing macros, from that you can design and develop
 * your own solution for solving the Cube. This includes applying a macro
 * to a cube, displaying and resetting the history of the moves, scrambling
 * and resetting the entire cube, reading the cube from input, and solving
 * the Cube with a simple built-in algorithm.
 * Below is the console menu of all the features in the program.
 *
 *
 * MENU
 * 1. Apply a macro
 * 2. Display a move sequences
 * 3. Scramble the Cube
 * 4. Reset the Cube
 * 5. Read the Cube
 * 6. Solve the Cube
 * 7. Reset the move history
 * 8. Display menu
 * 9. Quit
 *
 */

// libraries
#include "SDLDrawer.h"

int main(int argc, char* argv[])
{
    RubikCube cube;         // clone a 3-D cube
    SDLDrawer surfaceDisplay(cube);         // initialize with a cube
    surfaceDisplay.setTranslateSystem(0, 0, -16);
    surfaceDisplay.onExecute();             // execute the SDLDrawer to start drawing
}

