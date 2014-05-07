#if defined(__APPLE__) || defined(MACOSX)
    #include <OpenGL/gl.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glut.h>
#endif

#include <iostream>
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

typedef struct Point Point;

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

class BBox
{
    public:
        float minX, maxX, minY, maxY;
        void Calculate();
        void IsInside();
};

class GraphicObject
{
    public:
        GraphicObject();
        ~GraphicObject();
        Color Background;
        BBox Bbox;
        vector<GraphicObject> Objects;
        vector<Point> Points;
        int Primitive;
        void Draw();
        void ChangePrimitive();
};

typedef GraphicObject* PGraf;

class Camera
{
    public:
        GLfloat ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY;
        Camera();
};

class World
{
    public:
        Color Background;
        vector<PGraf> Objects;
        GLfloat ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY;
        void Zoom();
        void Pan();
        void Draw();
};

typedef World* PWorld;

GraphicObject::GraphicObject()
{
    Primitive = GL_LINE_LOOP;
}

GraphicObject::~GraphicObject()
{

}

void GraphicObject::ChangePrimitive()
{
    if (Primitive == GL_LINE_LOOP)
    {
        Primitive = GL_LINE_STRIP;
    }
    else
    {
        Primitive = GL_LINE_LOOP;
    }
}

void GraphicObject::Draw()
{
    glLineWidth(1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(Primitive);

    for (size_t i = 0; i < Points.size(); i++)
    {
        glVertex2f(Points[i].x, Points[i].y);
    }

    glEnd();
}

void World::Draw()
{
    if (Objects.size() > 0)
    {
        for (size_t i = 0; i < Objects.size(); i++)
        {
            Objects[i]->Draw();
        }
    }
}

Camera::Camera()
{
    ortho2D_minX = -400.0f;
    ortho2D_maxX =  400.0f;
    ortho2D_minY = -400.0f;
    ortho2D_maxY =  400.0f;
}