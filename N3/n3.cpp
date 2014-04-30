#include "base.h"

#ifdef WIN32
    #include <windows.h>
#endif

void resize(int width, int height) 
{

}

void display()
{

}

void keyPress(unsigned char key, int x, int y)
{

}

void specialKeyPress(int key, int x, int y)
{

}

void mouseMove(int x, int y)
{

}

void mouseEvent(int button, int state, int x, int y)
{

}

void createScene()
{
    GraphicObject o1;
    o1.Draw();

    GraphicObject* o2 = new GraphicObject();
    o2->Draw();
}

void init(void)
{
    glClearColor(1.0f,1.0f,1.0f,1.0);

    createScene();
}

int main (int argc, const char * argv[]) 
{
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(300, 250);
    glutInitWindowSize(400, 400);

    glutCreateWindow("N3");

    init();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPress);
    glutSpecialFunc(specialKeyPress);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseEvent);

    glutMainLoop();

    return 0;
}