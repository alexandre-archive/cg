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
        int Background;
        BBox Bbox;
        vector<GraphicObject> Objects;
        vector<Point> Points;
        int Primitive;
        void Draw();
};

class Camera
{
    public:
        GLfloat ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY;
        Camera();
};

class World
{
    public:
        int Background;
        vector<GraphicObject> Objects;
        GLfloat ortho2D_minX, ortho2D_maxX, ortho2D_minY, ortho2D_maxY;
        void Zoom();
        void Pan();
};

void GraphicObject::Draw() 
{
    cout << "Draw\n";
}

Camera::Camera()
{
    ortho2D_minX = -400.0f;
    ortho2D_maxX =  400.0f;
    ortho2D_minY = -400.0f;
    ortho2D_maxY =  400.0f;
}