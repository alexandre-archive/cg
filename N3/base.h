#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

#ifdef WIN32
    #include <windows.h>
#endif

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

/* 
    Inicialização de Struct requer c++11 para não gerar possíveis erros.
*/

struct Point
{
    float x = 0, y = 0;
};

struct Point3D
{
    float z = 0;
};

struct Point4D : Point3D
{
    float w = 1;
};

struct Color
{
    float r, g, b, a;
};

struct BBox
{
    float minX, maxX, minY, maxY;
};

/**
    Converte o espaço X do mouse, para o espaço X do Ortho.
**/
inline int convertXSpace(int x, int width)
{
    return (x * 2) - width;
}

/**
    Converte o espaço Y do mouse, para o espaço Y do Ortho.
**/
inline int convertYSpace(int y, int height)
{
    return (y * -2) + height;
}

inline void DrawText(int x, int y, char *s)
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

inline void DrawRectangle(float minX, float maxX, float minY, float maxY)
{
    glBegin(GL_LINE_LOOP);
        // Linha inferior.
        glVertex2f(minX, minY);
        // Linha lateral esquerda.
        glVertex2f(minX, maxY);
        // Linha superior.
        glVertex2f(maxX, maxY);
        // Linha lateral direita.
        glVertex2f(maxX, minY);
    glEnd();
}

inline void DrawRectangle(Point p1, Point p2, Point p3, Point p4)
{
    glBegin(GL_LINE_LOOP);
        // Linha inferior.
        glVertex2f(p1.x, p1.y);
        // Linha lateral esquerda.
        glVertex2f(p2.x, p2.y);
        // Linha superior.
        glVertex2f(p3.x, p3.y);
        // Linha lateral direita.
        glVertex2f(p4.x, p4.y);
    glEnd();
}