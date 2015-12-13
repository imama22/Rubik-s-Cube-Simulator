// libraries
#include "SDLDrawer.h"

// constructor
SDLDrawer::SDLDrawer(RubikCube c)
{
    appState = ON;
    cube = c;
    system_rotate_buffer_data = new float[3]{30.0, 40.0, 0.0};
    system_translate_buffer_data = new float[3]{0.0, 0.0, 0.0};
    scrambler = new CubeScrambler(cube);
    reader = new CubeReader(&cube);
}

// destructor
SDLDrawer::~SDLDrawer()
{
}

// Create the windows, set the background color and set up everything
bool SDLDrawer::onInit(){
	// Initialize SDL, return false if any error occurs
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	freopen( "CON", "w", stdout );
    freopen( "CON", "w", stderr );
    // If not, SDL_SetVideoMode opens a window
	if ((SDL_SetVideoMode(700, 400, 32, SDL_SWSURFACE | SDL_OPENGL)) == NULL) {
		return false;
	}
	// Set the background to rgb(0, 0, 0);
	glClearColor(0.9, 0.9, 0.9, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 640.0 / 480.0, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);

	return true;
}

// The main function to execute the program, draw the cube
// and process the commands read from keyboard.
void SDLDrawer::onExecute(){
	if (onInit() == false) return;  // return of initialization fails
	displayAppTitle();              // display application title
	displayAppMenu();               // display application menu
    cube.resetCube();               //

	SDL_Event evnt;                 // create SDL_event variable
	while (appState == ON)
	{
		while (SDL_PollEvent(&evnt)){
			onEvent(&evnt);
		}
		readKeyboardInput();
		onRender('N');
	}
	onCleanup();
}

// onCleanup method
void SDLDrawer::onCleanup()
{
	SDL_Quit();
}

// onRender method
void SDLDrawer::onRender(char _move)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    glPushMatrix();
    glTranslatef(system_translate_buffer_data[0] - 3, system_translate_buffer_data[1], system_translate_buffer_data[2]);
    glRotatef(system_rotate_buffer_data[0], 1, 0, 0);
    glRotatef(system_rotate_buffer_data[1], 0, 1, 0);
    glRotatef(system_rotate_buffer_data[2], 0, 0, 1);
    cube.drawCube(_move);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6, 3, -20);
    glRotatef(-20, 1, 0, 0);
    glRotatef(110, 0, 1, 0);
    glScalef(0.7, 0.7, 0.7);
    cube.drawCube(_move);
    glPopMatrix();

    SDL_GL_SwapBuffers();
}

// apply a sequence of moves on the Cube
void SDLDrawer::applyMoves(string command)
{
    macroHistory += command;
    int i = 0;
    while(i < command.length()){
        int time = 1;
        if ((i + 1) < command.length() && command[i + 1] == command[i])
            time = 2;
        char _move = command[i];
        if (!cube.isRotating())
        {
            cube.applyMove(_move, time);
            i += time;
        }
        onRender(_move);
    }
}

// display the application title with information
void SDLDrawer::displayAppTitle()
{
    cout << " __________________________________________\n";
    cout << "|                                          |\n";
    cout << "|                                          |\n";
    cout << "|          RUBIK'S CUBE SIMULATION         |\n";
    cout << "|          @Khuyen Do, 2015                |\n";
    cout << "|__________________________________________|\n";

    cout << "\n\n";
    cout << "Rubik's Cube Simulation\n";
    cout << "Rubik's Cube 10.2015\n";
    cout << "Enter 's' to switch between 2 windows\n";
}

// display the application  menu
void SDLDrawer::displayAppMenu()
{
    cout << "\n\n  MENU\n";
    cout << "  1. Appy a macro\n";
    cout << "  2. Display move sequences\n";
    cout << "  3. Scramble the Cube\n";
    cout << "  4. Reset the Cube\n";
    cout << "  5. Read the Cube\n";
    cout << "  6. Solve the Cube\n";
    cout << "  7. Reset move history\n";
    cout << "  8. Display menu\n";
    cout << "  9. Quit\n";
}

void SDLDrawer::setTranslateSystem(float x, float y, float z)
    {
        system_translate_buffer_data[0] += x;
        system_translate_buffer_data[1] += y;
        system_translate_buffer_data[2] += z;
    }
