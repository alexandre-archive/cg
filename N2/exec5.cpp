#ifdef WIN32
    #include <windows.h>
#endif

#include "base.h"
#include <iostream>

#include <stdio.h>

using namespace std;

GLint width     = 400,
      height    = 400;

GLfloat ortho2D_minX = -400.0f,
        ortho2D_maxX =  400.0f,
        ortho2D_minY = -400.0f,
        ortho2D_maxY =  400.0f;

GLfloat angle  = 100,
        radius = 100;

Point p1, p2, p3, p4, pSelected;

int selected        = 1,
    qtdPointsSpline = 10;

bool isMouseOK = false;

void mouse(int x, int y)
{
    if (!isMouseOK) return;

    switch (selected)
        {
            case 1:
                p1.X = (x * 2) - width;
                pSelected.X = p1.X;
                p1.Y = (y * -2) + height;
                pSelected.Y = p1.Y;
            break;

            case 2:
                p2.X = (x * 2) - width;
                pSelected.X = p2.X;
                p2.Y = (y * -2) + height;
                pSelected.Y = p2.Y;
            break;

            case 3:
                p3.X = (x * 2) - width;
                pSelected.X = p3.X;
                p3.Y = (y * -2) + height;
                pSelected.Y = p3.Y;
            break;

            case 4:
                p4.X = (x * 2) - width;
                pSelected.X = p4.X;
                p4.Y = (y * -2) + height;
                pSelected.Y = p4.Y;
            break;

            default:
                cout << "Invalid point: " << selected << "\n";
            break;
        }

    glutPostRedisplay();
}

Point SplineIterator(Point a, Point b, float t)
{
    Point p;
    p.X = a.X + (b.X - a.X) * t;
    p.Y = a.Y + (b.Y - a.Y) * t;
    return p;
}

void DrawSpline()
{
    float incT = 1.0f / qtdPointsSpline;
    float t;
    Point p1p2, p2p3, p3p4, p1p2p3, p2p3p4, p1p2p3p4, p0;

    glColor3f(1.0, 1.0, 0.0);
    glLineWidth(4.0f);

    // 1.00000 = Floating-Point Arithmetic Correction.
    for(t = 0; t <= 1.000001; t += incT)
    {
        p1p2     = SplineIterator(p1, p2, t);
        p2p3     = SplineIterator(p2, p3, t);
        p3p4     = SplineIterator(p3, p4, t);
        p1p2p3   = SplineIterator(p1p2, p2p3, t);
        p2p3p4   = SplineIterator(p2p3, p3p4, t);
        p1p2p3p4 = SplineIterator(p1p2p3, p2p3p4, t);

        // A primeira vez nao desenha, pois preciso definir o segundo ponto ainda.
        if(t != 0)
        {
            glBegin(GL_LINES);
                glVertex2f(p0.X, p0.Y);
                glVertex2f(p1p2p3p4.X, p1p2p3p4.Y);
            glEnd();
        }

        p0.X = p1p2p3p4.X;
        p0.Y = p1p2p3p4.Y;
    }
}

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

    glColor3f(0.0, 1.0, 1.0);
    glLineWidth(4.0f);

    // Desenha as Linhas do poliedro.
    glBegin(GL_LINE_STRIP);
        glVertex2f(p1.X, p1.Y);
        glVertex2f(p2.X, p2.Y);
        glVertex2f(p3.X, p3.Y);
        glVertex2f(p4.X, p4.Y);
    glEnd();

    DrawSpline();

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(7.0F);

    // Desenha o ponto na extremidade da linha.
     glBegin(GL_POINTS);
        glVertex2f(pSelected.X, pSelected.Y);
     glEnd();

    glutSwapBuffers();
}

void initialize()
{
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_LIGHTING);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Pontos Iniciais
    p1.X = -100;
    p1.Y = -100;

    p2.X = -100;
    p2.Y = 100;

    p3.X = 100;
    p3.Y = 100;

    p4.X = 100;
    p4.Y = -100;

    pSelected.X = p1.X;
    pSelected.Y = p1.Y;
}

void keyboard(unsigned char key, int mousePositionX, int mousePositionY)
{
    switch (key)
    {
        case KEY_ESCAPE:
            exit(0);
        break;

        case '1':
            pSelected.X = p1.X;
            pSelected.Y = p1.Y;
            selected = 1;
            glutPostRedisplay();
            
        break;
        
        case '2':
            pSelected.X = p2.X;
            pSelected.Y = p2.Y;
            selected = 2;
            glutPostRedisplay();
        break;

        case '3':
            pSelected.X = p3.X;
            pSelected.Y = p3.Y;
            selected = 3;
            glutPostRedisplay();
        break;

        case '4':
            pSelected.X = p4.X;
            pSelected.Y = p4.Y;
            selected = 4;
            glutPostRedisplay();
        break;

        case 'Q':
        case 'q':
            if(qtdPointsSpline > 1)
            {
                qtdPointsSpline -= 1;
                glutPostRedisplay();
            }
        break; 

        case 'W':
        case 'w':
            qtdPointsSpline += 1;
            glutPostRedisplay();
        break;

        default:
            cout << "Invalid key pressed: " << key << "\n";
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    isMouseOK = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowPosition(300, 250);
    glutInitWindowSize(width, height);
    glutCreateWindow("N2 - Exercicio 5");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(mouse);
    glutMouseFunc(mouse);

    initialize();

    glutMainLoop();

    return 0;
}
