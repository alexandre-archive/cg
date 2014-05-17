#ifndef GRAPHIC_OBJECT_H
    #define GRAPHIC_OBJECT_H
    #include "graphicobject.h"
#endif

//
// GraphicObject implementations
//

GraphicObject::GraphicObject()
{
    primitive = GL_LINE_LOOP;
    IsSelected = false;
    LineWidth = 2.0f;
    BackColor.r = 0.0f;
    BackColor.g = 0.0f;
    BackColor.b = 0.0f;
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
    glLineWidth(LineWidth);
    glColor3f(BackColor.r, BackColor.g, BackColor.b);

    glBegin(primitive);

    for (size_t i = 0; i < PointCount(); i++)
    {
        glVertex2f(GetPoint(i)->x, GetPoint(i)->y);
    }

    glEnd();

    if (IsSelected)
    {
        DrawBBox();
    }

    if (HasSelectedPoint())
    {
        DrawPoint(*GetSelectedPoint());
    }

    for (size_t i = 0; i < ObjCount(); ++i)
    {
        GetObj(i)->Draw();
    }
}

void GraphicObject::DrawBBox()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    DrawRectangle(bbox.minX, bbox.maxX, bbox.minY, bbox.maxY);
}

void GraphicObject::DrawPoint(Point p)
{
    glPointSize(4.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
        glVertex2f(p.x, p.y);
    glEnd();
}

bool GraphicObject::IsSelectable(int x, int y)
{
    size_t size = PointCount();

    if (size < 2)
    {
        return false;
    }

    int count = 0;
    float ti;
    float yint = y;
    float xint = 0;

    for (size_t i = 0; i < size - 1; i++)
    {
        PPoint p1 = GetPoint(i + 1);
        PPoint p2 = GetPoint(i);

        if (p1->x == x && p1->y == y)
        {
            return true;
        }

        ti = 0;

        if ((p2->y - p1->y) != 0)
        {
            ti = (yint - p1->y) / (p2->y - p1->y);
        }

        if (ti > 0 && ti < 1)
        {
            xint = p1->x + (p2->x - p1->x) * ti;

            // HACK: Se possuir apenas 2 pontos é
            // impossível selecioná-los. Adiciona uma margem de erro.
            if (size == 2)
            {
                // TODO: Distancia euclidiana?
                if ((xint + 8) > x || (xint - 8) > x)
                {
                    count++;
                }
            }
            else
            {
                if (xint > x)
                {
                    count++;
                }
            }
        }
    }

    // Calcula o ultimo com o primeiro.
    PPoint p1 = GetPoint(size - 1);
    PPoint p2 = GetPoint(0);

    ti = (yint - p1->y) / (p2->y - p1->y);

    if (ti > 0 && ti < 1)
    {
        xint = p1->x + (p2->x - p1->x) * ti;

        if (xint > x)
        {
            count++;
        }
    }

    return count % 2 != 0;
}

void GraphicObject::CalculateBBox()
{
    bbox.minX = points[0].x;
    bbox.maxX = points[0].x;
    bbox.minY = points[0].y;
    bbox.maxY = points[0].y;

    for (size_t i = 1; i < points.size(); i++)
    {
        if (points[i].x < bbox.minX)
        {
            bbox.minX = points[i].x;
        }

        if (points[i].y < bbox.minY)
        {
            bbox.minY = points[i].y;
        }

        if (points[i].x > bbox.maxX)
        {
            bbox.maxX = points[i].x;
        }

        if (points[i].y > bbox.maxY)
        {
            bbox.maxY = points[i].y;
        }
    }
}

bool InRange(int value, int nominal, int precision)
{
    return value < (nominal + precision) && value > (nominal - precision);
}

void GraphicObject::AddPoint(Point p)
{
    points.push_back(p);
    CalculateBBox();
}

PPoint GraphicObject::GetPoint(int index)
{
    if (index < 0 || index >= (int)PointCount())
    {
        return NULL;
    }

    return &points[index];
}

PPoint GraphicObject::GetLastPoint()
{
    return &points.back();
}

bool GraphicObject::IsPointSelectable(int x, int y)
{
    int nearPointPos = -1;

    for (size_t i = 0; i < points.size(); i++)
    {
        // TODO: Usar distancia euclidiana para calcular.
        if (points[i].x == x && points[i].y == y)
        {
            points[i].is_selected = true;
            return true;
        }

        if (InRange(x, points[i].x, 12) && InRange(y, points[i].y, 12))
        {
            nearPointPos = i;
        }
    }

    if(nearPointPos != -1)
    {
        points[nearPointPos].is_selected = true;
        return true;
    }

    for (size_t j = 0; j < ObjCount(); j++)
    {
        if (GetObj(j)->IsPointSelectable(x, y))
        {
            return true;
        }
    }

    return false;
}

PPoint GraphicObject::GetSelectedPoint()
{
    for (size_t i = 0; i < PointCount(); i++)
    {
        PPoint p = GetPoint(i);

        if (p->is_selected)
        {
            return p;
        }
    }

    for (size_t j = 0; j < ObjCount(); j++)
    {
        PPoint p = GetObj(j)->GetSelectedPoint();

        if (p)
        {
            return p;
        }
    }

    return NULL;
}

bool GraphicObject::HasSelectedPoint()
{
    for (size_t i = 0; i < PointCount(); i++)
    {
        PPoint p = GetPoint(i);

        if (p->is_selected)
        {
            return true;
        }
    }

    for (size_t j = 0; j < ObjCount(); j++)
    {
        if (GetObj(j)->HasSelectedPoint())
        {
            return true;
        }
    }

    return false;
}

void GraphicObject::DeleteSelectedPoint()
{
    for (size_t i = 0; i < PointCount(); i++)
    {
        PPoint p = GetPoint(i);

        if (p->is_selected)
        {
            this->points.erase(this->points.begin() + i);
        }
    }

    for (size_t i = 0; i < ObjCount(); i++)
    {
        GetObj(i)->DeleteSelectedPoint();
    }
}

//
// GraphicContainer implementation
//

void GraphicContainer::AddObj(PGraf g)
{
    objects.push_back(g);
}

PGraf GraphicContainer::GetObj(int index)
{
    if (index < 0 || index >= (int)ObjCount())
    {
        return NULL;
    }

    return objects[index];
}

PGraf GraphicContainer::GetSelectedObj()
{
    for (size_t i = 0; i < ObjCount(); i++)
    {
        PGraf g = GetObj(i);

        if (g->IsSelected)
        {
            return g;
        }
        else
        {
            PGraf g2 = g->GetSelectedObj();

            if (g2)
            {
                return g2;
            }
        }
    }

    return NULL;
}

void GraphicContainer::DeleteSelectedObj()
{
    for (size_t i = 0; i < ObjCount(); i++)
    {
        PGraf g = GetObj(i);

        if (g->IsSelected)
        {
            this->objects.erase(this->objects.begin() + i);
        }
        else
        {
            g->DeleteSelectedObj();
        }
    }
}

bool GraphicContainer::SelectObj(int x, int y)
{
    for (size_t i = 0; i < ObjCount(); i++)
    {
        PGraf g = GetObj(i);

        if (g->IsSelectable(x, y))
        {
            g->IsSelected = true;
            return true;
        }
        else
        {
            for (size_t j = 0; j < g->ObjCount(); ++j)
            {
                if (g->SelectObj(x, y))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void GraphicContainer::SelectNone()
{
    for (size_t i = 0; i < ObjCount(); i++)
    {
        PGraf g = GetObj(i);
        g->IsSelected = false;

        for (size_t j = 0; j < g->PointCount(); j++)
        {
            g->GetPoint(j)->is_selected = false;
        }

        g->SelectNone();
        g->CalculateBBox();
    }
}