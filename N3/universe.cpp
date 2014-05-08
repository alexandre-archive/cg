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
void Universe::SelectNone()
{
    // Remove a seleção de todos. Caso contrário ficara com a BBox.
    for (size_t i = 0; i < Objects.size(); i++)
    {
        Objects[i]->SetSelected(false);
    }

    // Remove o ponto dos vertices.
    for (size_t i = 0; i < Objects.size(); ++i)
    {
        Objects[i]->SetSelectedVertex(-1);
    }
}