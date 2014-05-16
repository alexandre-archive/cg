#ifndef UNIVERSE_H
    #define UNIVERSE_H
    #include "universe.h"
#endif


Universe::Universe()
{
}

Universe::~Universe()
{
    // TODO: Delete pointers.
}

/**
    Desenha o Mundo e seus Objectos Gráficos.
**/
void Universe::Draw()
{
    for (size_t i = 0; i < ObjCount(); i++)
    {
        GetObj(i)->Draw();
    }
}

PPoint Universe::GetSelectedPoint()
{
    for (size_t i = 0; i < ObjCount(); i++)
    {
        if (GetObj(i)->HasSelectedPoint())
        {
            return GetObj(i)->GetSelectedPoint();
        }
    }

    return NULL;
}

bool Universe::HasSelectedPoint()
{
    for (size_t i = 0; i < ObjCount(); i++)
    {
        if (GetObj(i)->HasSelectedPoint())
        {
            return true;
        }
    }

    return false;
}

void Universe::DeleteSelectedPoint()
{

}
