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
#include <cmath>
#include <string.h>
#include <vector>

using namespace std;

/* 
    Inicialização de Struct requer c++11 para não gerar possíveis erros.
*/

struct Point
{
    bool is_selected = false;
    float x = 0, y = 0;
};

typedef Point* PPoint;

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
    @param x
    @param width
**/
inline int convertXSpace(int x, int width)
{
    return (x * 2) - width;
}

/**
    Converte o espaço Y do mouse, para o espaço Y do Ortho.
    @param y
    @param height
**/
inline int convertYSpace(int y, int height)
{
    return (y * -2) + height;
}

/**
    Calcula a distancia euclidiana.
    @param x1
    @param y1
    @param x2
    @param y2
**/
double euclideanDistance(float x1, float y1, float x2, float y2)
{
    /*
    double x = x1 - x2;
    double y = y1 - y2;
    double dist;

    dist = pow(x, 2) + pow(y, 2);
    dist = sqrt(dist);

    return dist; // floor(dist);
*/

    double x = x1 - x2;
    double y = y1 - y2;

    return abs(pow(x, 2) + pow(y, 2));
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