#ifdef WIN32
    #include <windows.h>
#endif

#include "base.h"
#include <iostream>

using namespace std;

GLint width     = 400,
      height    = 400;

GLfloat ortho2D_minX = -400.0f,
        ortho2D_maxX =  400.0f,
        ortho2D_minY = -400.0f,
        ortho2D_maxY =  400.0f;

int GL_CONSTANTS [10] = {
                            GL_POINTS,
                            GL_LINES,
                            GL_LINE_LOOP,
                            GL_LINE_STRIP,
                            GL_TRIANGLES,
                            GL_TRIANGLE_FAN,
                            GL_TRIANGLE_STRIP,
                            GL_QUADS,
                            GL_QUAD_STRIP,
                            GL_POLYGON,
                        };

int GL_CONST = 0;

void display()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluOrtho2D(ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Eixo X e Y;
    DrawXYAxes();

    glLineWidth(2.0f);
    glPointSize(2.0f);

    // Primitivas.
    glBegin(GL_CONSTANTS[GL_CONST]);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(100.0f, -100.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(100.0f,  100.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-100.0f,  100.0f);
        glColor3f(1.0f, 0.078f, 0.576f);
        glVertex2f(-100.0f, -100.0f);
    glEnd();

    glutSwapBuffers();
}

void initialize ()
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_LIGHTING);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void keyboard(unsigned char key, int mousePositionX, int mousePositionY)
{
    switch (key)
    {
        case KEY_ESCAPE:
            exit(0);
        break;

        case KEY_SPACE:
            GL_CONST++;
            if (GL_CONST >= 10) GL_CONST = 0;
            glutPostRedisplay();
        break;

        default:
            cout << "Invalid key pressed: " << key << "\n";
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(300, 250);
    glutInitWindowSize(width, height);
    
    glutCreateWindow("N2 - Exercicio 4");
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    initialize();
    glutMainLoop();

    return 0;
}