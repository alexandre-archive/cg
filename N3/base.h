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

class BBox
{
    public:
        float minX, maxX, minY, maxY;
        void Calculate();
        void IsInside();
};

class GraphicObject
{
    private:
        bool selected;
        int  primitive;
    public:
        GraphicObject();
        ~GraphicObject();
        Color Background;
        BBox Bbox;
        vector<GraphicObject> Objects;
        vector<Point> Points;
        void Draw();
        void DrawBBox();
        void ChangePrimitive();
        bool IsMouseInside(int x, int y);
        void CalculateBBox();
        void SetSelected(bool selected) { this->selected = selected; };
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
    primitive = GL_LINE_LOOP;
    selected = false;
}

GraphicObject::~GraphicObject()
{

}

void GraphicObject::ChangePrimitive()
{
    if (primitive == GL_LINE_LOOP)
    {
        primitive = GL_LINE_STRIP;
    }
    else
    {
        primitive = GL_LINE_LOOP;
    }
}

void GraphicObject::Draw()
{
    glLineWidth(1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(primitive);

    for (size_t i = 0; i < Points.size(); i++)
    {
        glVertex2f(Points[i].x, Points[i].y);
    }

    glEnd();

    if (selected) 
    {
        DrawBBox();
    }
}

void GraphicObject::DrawBBox()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    DrawRectangle(Bbox.minX, Bbox.maxX, Bbox.minY, Bbox.maxY);
}

bool GraphicObject::IsMouseInside(int x, int )
{
    return false;
}

void GraphicObject::CalculateBBox()
{
    Bbox.minX = Points[0].x;
    Bbox.maxX = Points[0].x;
    Bbox.minY = Points[0].y;
    Bbox.maxY = Points[0].y;

    for (size_t i = 1; i < Points.size(); i++)
    {
        if (Points[i].x < Bbox.minX)
        {
            Bbox.minX = Points[i].x;
        }

        if (Points[i].y < Bbox.minY)
        {
            Bbox.minY = Points[i].y;
        }

        if (Points[i].x > Bbox.maxX)
        {
            Bbox.maxX = Points[i].x;
        }

        if (Points[i].y > Bbox.maxY)
        {
            Bbox.maxY = Points[i].y;
        }
    }
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