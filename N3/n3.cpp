#include "base.h"

#ifdef WIN32
    #include <windows.h>
#endif

#include <string.h>

#define KEY_TAB 9
#define KEY_ESC 27
#define KEY_DEL 127
#define KEY_SPACE 32

GLint width  = 400,
      height = 400;

GLfloat ortho2D_minX = -400.0f,
        ortho2D_maxX =  400.0f,
        ortho2D_minY = -400.0f,
        ortho2D_maxY =  400.0f;

bool selectionMode = false;

PWorld world;
int currentObj = -1;
bool isMouseDown = false;

void resize(int width, int height)
{

}

void DrawText(int x, int y, char *s)
{
    int len, i;
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2f(x, y);
    len = (int) strlen(s);

    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
    }
}

/**
    Converte o espaço X do mouse, para o espaço X do Ortho.
**/
int convertXSpace(int x)
{
    return (x * 2) - width;
}

/**
    Converte o espaço Y do mouse, para o espaço Y do Ortho.
**/
int convertYSpace(int y)
{
    return (y * -2) + height;
}

void drawMode()
{
    DrawText(ortho2D_minX + 4, ortho2D_minY + 4, (char*)(selectionMode ? "Selecao (Tab)" : "Edicao (Tab)"));
}

void display()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawMode();
    world->Draw();

    glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case KEY_ESC:
            exit(0);
        break;
        case KEY_TAB:
            selectionMode = !selectionMode;
            glutPostRedisplay();
        break;
        case KEY_DEL:
            // Deleta o ponto ou poligono se for seleção.
            // Limpa a tela se for edição.
            if (selectionMode)
            {

            }
            else
            {
                currentObj = -1;
                world->Objects.clear();
                glutPostRedisplay();
            }
        break;
        case KEY_SPACE:
            if (currentObj != -1)
            {
                world->Objects[currentObj]->ChangePrimitive();
                glutPostRedisplay();
            }
        break;
        default:
            cout << key << "\n";
        break;
    }
}

void specialKeyPress(int key, int x, int y)
{

}

void mouseMove(int x, int y)
{
    //cout << "Current Obj = " << currentObj << "\n";
    //cout << "Mouse is Down = " << isMouseDown << "\n";

    if (isMouseDown && currentObj != -1)
    {
        //cout << "x = " << x << " y = " << y << "\n";

        Point& pe = world->Objects[currentObj]->Points.back();
        pe.x = convertXSpace(x);
        pe.y = convertYSpace(y);

        glutPostRedisplay();
    }
}

void mouseEvent(int button, int state, int x, int y)
{
    // button  GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON
    // state GLUT_UP or GLUT_DOWN
    //cout << "x = " << x << " y = " << y << "\n";

    if (selectionMode)
    {

    }
    else
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            if (state == GLUT_DOWN)
            {
                isMouseDown = true;

                // É um novo
                if (currentObj == -1)
                {
                    world->Objects.push_back(new GraphicObject());
                    currentObj = world->Objects.size() - 1;
                }

                Point ps;
                ps.x = convertXSpace(x);
                ps.y = convertYSpace(y);

                world->Objects[currentObj]->Points.push_back(ps);
                world->Objects[currentObj]->Points.push_back(ps);
            }
            else if (state == GLUT_UP)
            {
                isMouseDown = false;

                if (currentObj != -1)
                {
                    Point& pe = world->Objects[currentObj]->Points.back();
                    pe.x = convertXSpace(x);
                    pe.y = convertYSpace(y);
                }
            }

            //cout << "Current Obj = " << currentObj << "\n";
            //cout << "Mouse is Down = " << isMouseDown << "\n";
        }
        else
        {
            currentObj = -1;
        }
    }

    glutPostRedisplay();
}

void createScene()
{
    /*GraphicObject o1;
    o1.Draw();

    GraphicObject* o2 = new GraphicObject();
    o2->Draw();*/
}

void init(void)
{
    /*glClearColor(1.0f,1.0f,1.0f,1.0);

    createScene();*/

    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_LIGHTING);

    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

    world = new World();
/*
    // Draw line test.
    auto o = new GraphicObject();
    Point p1;
    p1.x = -200;
    p1.y = 0;
    Point p2;
    p2.x = 200;
    p2.y = 0;
    o->Points.push_back(p1);
    o->Points.push_back(p2);
    world->Objects.push_back(o);
*/
}

int main(int argc, const char * argv[])
{
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(300, 250);
    glutInitWindowSize(height, width);

    glutCreateWindow("N3");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutSpecialFunc(specialKeyPress);
    glutMotionFunc(mouseMove);
    glutMouseFunc(mouseEvent);

    init();
    glutMainLoop();

    return 0;
}