/*
 * The file contains functions for actually drawing the cube
 * on the canvas and doing some animations
 */

#include "RubikCube.h"

void RubikCube::drawSolidCube(int *colors)
{
	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      chooseColor(colors[0]);
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);

      // Bottom face (y = -1.0f)
      chooseColor(colors[1]);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      chooseColor(colors[2]);
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Back face (z = -1.0f)
      chooseColor(colors[3]);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      chooseColor(colors[4]);
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Right face (x = 1.0f)
      chooseColor(colors[5]);
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
   glEnd();  // End of drawing color-cube
}

void RubikCube::drawCube(char _move)
{
    int *cubies;
    if (deg >= 90)
        {
            deg = 0;
            rotating = false;
            SDL_Delay(10);
        }
    if (rotating){
        deg += 1.5;
        switch (_move)
        {
        case 'U':
            cubies = (int*)face_cubie_buffer_data[0]; break;
        case 'D':
            cubies = (int*)face_cubie_buffer_data[1]; break;
        case 'F':
            cubies = (int*)face_cubie_buffer_data[2]; break;
        case 'B':
            cubies = (int*)face_cubie_buffer_data[3]; break;
        case 'L':
            cubies = (int*)face_cubie_buffer_data[4]; break;
        case 'R':
            cubies = (int*)face_cubie_buffer_data[5]; break;
        case 'u':
            cubies = (int*)face_cubie_buffer_data[0]; break;
        case 'd':
            cubies = (int*)face_cubie_buffer_data[1]; break;
        case 'f':
            cubies = (int*)face_cubie_buffer_data[2]; break;
        case 'b':
            cubies = (int*)face_cubie_buffer_data[3]; break;
        case 'l':
            cubies = (int*)face_cubie_buffer_data[4]; break;
        case 'r':
            cubies = (int*)face_cubie_buffer_data[5]; break;
        case 'X':
            cubies = (int*) face_cubie_buffer_data; break;
        case 'Y':
            cubies = (int*) face_cubie_buffer_data; break;
        case 'Z':
            cubies = (int*) face_cubie_buffer_data; break;
        case 'x':
            cubies = (int*) face_cubie_buffer_data; break;
        case 'y':
            cubies = (int*) face_cubie_buffer_data; break;
        case 'z':
            cubies = (int*) face_cubie_buffer_data; break;
        }
    }

    for (int z = 0; z < 3; ++z)
    for (int y = 0; y < 3; ++y)
        for (int x = 0; x < 3; ++x)
        {
            glPushMatrix();

            if (rotating)
            {
                if (_move == 'X')
                    glRotatef(deg, -1, 0, 0);
                else if (_move == 'Y')
                    glRotatef(deg, 0, -1, 0);
                else if (_move == 'Z')
                    glRotatef(deg, 0, 0, 1);
                else
                {
                    int temp = 9;
                    if (_move == 'X' || _move == 'x' ||
                        _move == 'Y' || _move == 'y' ||
                        _move == 'Z' || _move == 'z')
                            temp = 54;
                for (int i = 0; i < temp; ++i)
                if ((z * 9 + y * 3 + x) == cubies[i]){
                    switch (_move)
                    {
                    case 'U':
                        glRotatef(deg, 0, -1, 0);
                        break;
                    case 'D':
                        glRotatef(deg, 0, 1, 0);
                        break;
                    case 'F':
                        glRotatef(deg, 0, 0, -1);
                        break;
                    case 'B':
                        glRotatef(deg, 0, 0, 1);
                        break;
                    case 'L':
                        glRotatef(deg, 1, 0, 0);
                        break;
                    case 'R':
                        glRotatef(deg, -1, 0, 0);
                        break;
                    case 'u':
                        glRotatef(deg, 0, 1, 0);
                        break;
                    case 'd':
                        glRotatef(deg, 0, -1, 0);
                        break;
                    case 'f':
                        glRotatef(deg, 0, 0, 1);
                        break;
                    case 'b':
                        glRotatef(deg, 0, 0, -1);
                        break;
                    case 'l':
                        glRotatef(deg, -1, 0, 0);
                        break;
                    case 'r':
                        glRotatef(deg, 1, 0, 0);
                        break;
                    case 'X':
                        glRotatef(deg, 1, 0, 0);
                        break;
                    case 'x':
                        glRotatef(deg, 1, 0, 0);
                        break;
                    case 'Y':
                        glRotatef(deg, 0, 1, 0);
                        break;
                    case 'y':
                        glRotatef(deg, 0, 1, 0);
                        break;
                    case 'Z':
                        glRotatef(deg, 0, 0, -1);
                        break;
                    case 'z':
                        glRotatef(deg, 0, 0, 1);
                        break;
                    }
                    break;
                }
                }
            }

            // made the center of the cube be the origin of the coordinates
            glTranslatef(cubeSize * x - cubeSize, - cubeSize * y + cubeSize, -cubeSize * z + cubeSize);
            // scale D cubies to 0.9
            glScalef(0.9, 0.9, 0.9);

            int colors[6];
            for (int i = 0; i < 6; ++i){
                if (cubie_buffer_data[z * 9 + y * 3 + x][i] >= 0)
                colors[i] = face_color_buffer_data[cubie_buffer_data[z * 9 + y * 3 + x][i]];
                else
                    colors[i] = 6;
            }
            drawSolidCube((int*) colors);
            glPopMatrix();
    }
}

void RubikCube::chooseColor(int color)
{
    switch(color){
    case 0:
        glColor4f(1, 1, 1, 0.75); break;
    case 1:
        glColor4f(0.8, 0.8, 0.1, 0.75); break;
    case 2:
        glColor4f(0.1, 0.1, 0.7, 0.75); break;
    case 3:
        glColor4f(0.1, 0.8, 0.2, 0.75); break;
    case 4:
        glColor4f(0.8, 0.1, 0.1, 0.75); break;
    case 5:
        glColor4f(0.9, 0.4, 0.1, 0.75); break;
    default:
        glColor4f(0.1, 0.1, 0.1, 0.75);
    }
}
