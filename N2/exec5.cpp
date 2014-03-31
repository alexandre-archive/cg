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

GLfloat angle  = 100,
        radius = 100;

Point p1, p2, p3, p4, pSelected;

int selected = 1;
float qtdPointsSpline = 10.0f;

void mouse(int x, int y)
{
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
                    cout << "Ivalid point: " << selected << "\n";
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
    float incT = 1/ qtdPointsSpline;
    float t = 0;
    Point p1p2,p2p3,p3p4, p1p2p3, p2p3p4, p1p2p3p4, pontoInicial;

    // Define a Cor Amarela
    glColor3f(255.0, 255.0, 0.0);
    // Define expessura da linha
    glLineWidth(4.0f);

    // Aqui tem um problema, o T deve ser <= 1, mas nao entrava quando == 1, por isso coloquei < 1,001
    for(t=0; t < 1.0001; t = t + incT)
    {
        p1p2 = SplineIterator(p1,p2,t);
        p2p3 = SplineIterator(p2,p3,t);
        p3p4= SplineIterator(p3,p4,t);
        p1p2p3 = SplineIterator(p1p2,p2p3,t);
        p2p3p4 = SplineIterator(p2p3,p3p4,t);
        p1p2p3p4 = SplineIterator(p1p2p3,p2p3p4,t);

        //A primeira vez nao desenha, pois preciso definir o segundo ponto ainda
        if(t != 0)
        {
            glBegin(GL_LINES);
                glVertex2f(pontoInicial.X, pontoInicial.Y);
                glVertex2f(p1p2p3p4.X, p1p2p3p4.Y);
            glEnd();
        }

        pontoInicial.X = p1p2p3p4.X;
        pontoInicial.Y = p1p2p3p4.Y;
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

    // Define a cor Ciano
    glColor3f(0.0, 255.0, 255.0); 

    // Expessura da Linha
    glLineWidth(4.0f);

    //Desenha as Linhas do poliedro
    glBegin(GL_LINE_STRIP);
        glVertex2f(p1.X, p1.Y);
        glVertex2f(p2.X, p2.Y);
        glVertex2f(p3.X, p3.Y);
        glVertex2f(p4.X, p4.Y);
    glEnd();

    //Rotina para desenhar Spline
    DrawSpline();

    //Define a Cor Vermelha
    glColor3f(255.0, 0.0, 0.0); 
    //Define expessura do ponto
    glPointSize(7.0F);

    //Desenha o ponto na extremidade da Linha
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
                qtdPointsSpline = qtdPointsSpline - 1;
                glutPostRedisplay();
            }
        break; 

        case 'W':
        case 'w':
            qtdPointsSpline = qtdPointsSpline + 1;
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

    //Posicao da Window
    glutInitWindowPosition(300, 250);

    //Tamananho da Window
    glutInitWindowSize(width, height);

    //Cria uma nova Window
    glutCreateWindow("N2 - Exercicio 5");
    //Display do desenho Inicial
    glutDisplayFunc(display);

    //Faz Tratamento das teclas e redesenha
    glutKeyboardFunc(keyboard);

    //Faz Tratamento do mouse
    glutMotionFunc(mouse);

    initialize();

    glutMainLoop();

    return 0;
}
