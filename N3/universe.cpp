#ifndef UNIVERSE_H
    #define UNIVERSE_H
    #include "universe.h"
#endif

/**
    Desenha o Mundo e seus Objectos Gráficos.
**/
void Universe::Draw()
{
    if (Objects.size() > 0)
    {
        for (size_t i = 0; i < Objects.size(); i++)
        {
            Objects[i]->Draw();
        }
    }
}