#ifndef GRAPHIC_OBJECT_H
    #define GRAPHIC_OBJECT_H
    #include "graphicobject.h"
#endif

/**
    Cria um novo gŕafico.
**/
GraphicObject::GraphicObject()
{
    primitive = GL_LINE_LOOP;
    selected = false;
    selectedVertex = -1;
    LineWidth = 2.0f;
    SetColor(0.0f, 0.0f, 0.0f);
}

GraphicObject::~GraphicObject()
{

}

/**
    Altera a primitiva atual entre GL_LINE_LOOP ou GL_LINE_STRIP.
**/
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

/**
    Desenha o Gráfico e seus filhos.
    Se estiver selecionado desenhará a BBox.
**/
void GraphicObject::Draw()
{
    glLineWidth(LineWidth);

    glColor3f(color.r, color.g, color.b);
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

    if (selectedVertex != -1)
    {
        DrawPoint(Points[selectedVertex]);
    }
}

/**
    Desenha a BBox ao redor do Gráfico.
**/
void GraphicObject::DrawBBox()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    DrawRectangle(Bbox.minX, Bbox.maxX, Bbox.minY, Bbox.maxY);
}

/**
    Desenha um ponto no local do vértice selecionado.
    Facilitando a identificação.
**/
void GraphicObject::DrawPoint(Point p)
{
    glPointSize(4.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
        glVertex2f(p.x, p.y);
    glEnd();
}

/**
    Verifica se o mouse entra dentro do Gráfico.
**/
bool GraphicObject::IsMouseInside(int x, int y)
{
    if (Points.size() < 2)
    {
        return false;
    }

    int count = 0;
    double ti;
    double yint = y;
    double xint = 0;

    for (size_t i = 0; i < Points.size() - 1; i++)
    {
        auto p1 = Points[i + 1];
        auto p2 = Points[i];

        if (p1.x == x && p1.y == y)
        {
            return true;
        }

        ti = 0;

        if ((p2.y - p1.y) != 0)
        {
            ti = (yint - p1.y) / (p2.y - p1.y);
        }

        if (ti > 0 && ti < 1)
        {
            xint = p1.x + (p2.x - p1.x) * ti;

            if (xint > x)
            {
                count++;
            }
        }
    }

    auto p1 = Points[Points.size() - 1];
    auto p2 = Points[0];

    ti = (yint - p1.y) / (p2.y - p1.y);

    if (ti > 0 && ti < 1)
    {
        xint = p1.x + (p2.x - p1.x) * ti;

        if (xint > x)
        {
            count++;
        }
    }

    return count % 2 != 0;
}

/**
    Calcula a nova posição da BBox.
**/
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

void GraphicObject::ChangeRColor()
{
    color.r += 0.1f;

    if (color.r > 1.0f)
    {
        color.r = 0.0f;
    }
}

void GraphicObject::ChangeGColor()
{
    color.g += 0.1f;

    if (color.g > 1.0f)
    {
        color.g = 0.0f;
    }
}

void GraphicObject::ChangeBColor()
{
    color.b += 0.1f;

    if (color.b > 1.0f)
    {
        color.b = 0.0f;
    }
}

bool InRange(int value, int nominal, int precision)
{
    return value < (nominal + precision) && value > (nominal - precision);
}

/**
    Se X e Y corresponderem a um vértice, retorna a posição deste vértice.
    Caso contrário retornará -1;
**/
int GraphicObject::GetSelectedVertex(int x, int y)
{
    int nearPointPos = -1;

    for (size_t i = 0; i < Points.size(); i++)
    {
        // TODO: Usar distancia euclidiana para calcular.
        if (Points[i].x == x && Points[i].y == y)
        {
            return i;
        }

        if (InRange(x, Points[i].x, 12) && InRange(y, Points[i].y, 12))
        {
            nearPointPos = i;
        }
    }

    return nearPointPos;
}
