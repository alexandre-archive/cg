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

Point& Universe::GetSelectedPoint()
{

}

bool Universe::HasSelectedPoint()
{

}

void Universe::DeleteSelectedPoint()
{

}
