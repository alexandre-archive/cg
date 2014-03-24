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

void display()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluOrtho2D(ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Eixo X e Y.
    DrawXYAxes();

    // 3 circulos
    glLineWidth(1.5f);
    glColor3f(0.0, 0.0, 0.0);
    // Direita
    DrawCircle(100, 100, 100, 100, GL_LINE_LOOP);
    // Esquerda
    DrawCircle(-100, 100, 100, 100, GL_LINE_LOOP);
    // Inferior
    DrawCircle(0, -100, 100, 100, GL_LINE_LOOP);

    // Triangulo
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.6f, 1.0f);

    Point p1, p2, p3;
    // Ponto esquerdo.
    p1.x = -100.0f;
    p1.y = 100.0f;
    // Ponto direito.
    p2.x = 100.0f;
    p2.y = 100.0f;
    // Ponto inferior.
    p3.x = 0.0f;
    p3.y = -100.0f;

    DrawTriangle(p1, p2, p3);

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

        default:
            cout << "Invalid key pressed: " << key << "\n";
        break;
    }
}

int main(int argc, char **argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition (300, 250);
    glutInitWindowSize(width, height);
    
    glutCreateWindow("N2 - Exercicio 3");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    initialize();
    glutMainLoop();

    return 0;
}