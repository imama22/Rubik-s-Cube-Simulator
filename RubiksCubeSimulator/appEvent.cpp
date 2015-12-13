#include "SDLDrawer.h"

// onEvent method
void SDLDrawer::onEvent(SDL_Event* evnt)
{
	if (evnt->type == SDL_QUIT)
		appState = OFF;
}

// read the input the keyboard and process the command
void SDLDrawer::readKeyboardInput()
{
	Uint8* keystate = SDL_GetKeyState(NULL);
	if (keystate[SDLK_s])
    {
        while (true)
        {
        cout << "\n\n\[ENT]: Select ";
        string command;
        getline(cin, command);

        // apply a macro
        if (command == "1")
        {
            cout << "\nYour macro = ";
            string macro = "";
            getline(cin, macro);
            cout << "\n     APPLYING THE MACRO\n";
            applyMoves(macro);
        }
        // display move sequences
        else if (command == "2")
        {
            cout << "\n     HISTORY\n";
            string macroStr = macroHistory;
            for (int i = 0; i < macroStr.length(); ++i)
            {
                cout << macroStr[i] << " ";
                if ((i + 1) % 20 == 0) cout << endl;
            }
        }
        // scramble the Cube
        else if (command == "3")
        {
            string moves = scrambler->scramble(20);
            applyMoves(moves);
        }
        // reset the Cube to the solved state
        else if (command == "4"){
            cube.resetCube();
            //cube.resetMacroHistory();
            cout << "\n     RESETTING THE CUBE\n";
        }
        // read the Cube from the user input
        else if (command == "5")
        {
            cout << "\nEnter facet colors of each face as string of numbers\n";
            cout << "\n _____________\n";
            cout <<   "| 0. White    |\n";
            cout <<   "| 1. Yellow   |\n";
            cout <<   "| 2. Blue     |\n";
            cout <<   "| 3. Green    |\n";
            cout <<   "| 4. Red      |\n";
            cout <<   "| 5. Orange   |\n";
            cout <<   "|_____________|\n\n";
            string u, d, f, b, l, r;
            cout << "Up face    = ";
            getline(cin, u);
            cout << "Down face  = ";
            getline(cin, d);
            cout << "Front face = ";
            getline(cin, f);
            cout << "Back face  = ";
            getline(cin, b);
            cout << "Left face  = ";
            getline(cin, l);
            cout << "Right face = ";
            getline(cin, r);
        }
        // solve the Cube
        else if (command == "6")
        {
            cout << "\n     SOLVING THE CUBE\n";
            //cube.resetMacroHistory();
            RubikCube newCube;
            for (int i = 0; i < 54; ++i)
            {
                newCube.ptr_facets_buffer_data()[i] = cube.ptr_facets_buffer_data()[i];
                newCube.ptr_face_color_buffer_data()[i] = cube.ptr_face_color_buffer_data()[i];
            }
            string macroStr;
            macroStr = MySolver::solveCube(&newCube);
            applyMoves(macroStr);
            cout << endl;
            int moveCount = 0, s = 0;
            while (s < macroStr.length())
            {
                int e = s;
                while (macroStr[e + 1] == macroStr[e] &&
                       e < macroStr.length() - 1)
                    ++e;

                if (macroStr[s] == 'X' || macroStr[s] == 'Y' || macroStr[s] == 'Z' ||
                        macroStr[s] == 'x' || macroStr[s] == 'y' || macroStr[s] == 'z')
                    cout << "(" << macroStr[s] << ")";
                else{
                    switch ((e - s) % 4)
                    {
                    case 0:
                        moveCount++;
                        cout << macroStr[s];
                        break;
                    case 1:
                        moveCount++;
                        cout << macroStr[s] << "2";
                        break;
                    case 2:
                        moveCount++;
                        cout << macroStr[s] << "3";
                        break;
                    case 3:
                        break;
                    }
                    }
                s += e - s + 1;
                if ((s + 1) % 10 == 0) cout << endl;
            }
            cout << "\n     Number of moves = " << moveCount << endl;
        }
        else if (command == "7")
        {
            cout << "\n     RESETTING THE HISTORY\n";
            macroHistory = "";
        }
        else if (command == "8")
        {
            displayAppMenu();
        }
        else if (command == "9")
            return;
        }
    }
}







