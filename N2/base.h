#if defined(__APPLE__) || defined(MACOSX)
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

#include <math.h>

/*
    Funcões Auxiliares

    Utilizadas nos exercícios.
*/

#define KEY_ESCAPE 27
#define KEY_SPACE  32

struct Point
{
    float x, y;
};

inline void DrawCircle(float cx, float cy, float radius, int points, GLenum primitive = GL_LINE_LOOP)
{
    glBegin(primitive);

        for(int i = 0; i < points; i++)
        {
            float angle = 2.0f * M_PI * float(i) / float(points);

            float x = radius * cos(angle);
            float y = radius * sin(angle);

            glVertex2f(x + cx, y + cy);
        }

    glEnd();
}

inline void DrawTriangle(Point p1, Point p2, Point p3, GLenum primitive = GL_LINE_LOOP)
{
    glBegin(primitive);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glVertex2f(p3.x, p3.y);
    glEnd();    
}

inline void DrawXYAxes()
{
    glLineWidth(1.0f);
    glBegin(GL_LINES);
        // Eixo X.
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-200.0f, 0.0f);
        glVertex2f(200.0f, 0.0f);
        // Eixo Y.
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(0.0f, -200.0f);
        glVertex2f(0.0f, 200.0f);
    glEnd();
}