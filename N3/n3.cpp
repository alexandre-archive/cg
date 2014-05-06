#include "base.h"

#ifdef WIN32
    #include <windows.h>
#endif

#include <string.h>

#define KEY_TAB 9
#define KEY_ESC 27

GLfloat ortho2D_minX = -400.0f,
        ortho2D_maxX =  400.0f,
        ortho2D_minY = -400.0f,
        ortho2D_maxY =  400.0f;

bool selection = false;

void resize(int width, int height) 
{

}

void DrawText(int x, int y, char *s)
{
    int len, i;
    glRasterPos2f(x, y);
    glColor3f(1.0f, 0.0f, 0.0f);
    len = (int) strlen(s);

    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
    }
}

void drawMode()
{
    DrawText(ortho2D_minX + 4, ortho2D_minY + 4, (char*)(selection ? "Selecao" : "Edicao"));
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
            selection = !selection;
            glutPostRedisplay();
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

}

void mouseEvent(int button, int state, int x, int y)
{
    // button  GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON
    // state GLUT_UP or GLUT_DOWN

    if (state == GLUT_DOWN)
    {

    }
    else if (state == GLUT_UP)
    {

    }
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

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

int main(int argc, const char * argv[]) 
{
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(300, 250);
    glutInitWindowSize(400, 400);

    glutCreateWindow("N3");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutSpecialFunc(specialKeyPress);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseEvent);

    init();
    glutMainLoop();

    return 0;
}