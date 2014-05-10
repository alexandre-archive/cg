#ifndef UNIVERSE_H
    #define UNIVERSE_H
    #include "universe.h"
#endif


Universe::Universe()
{
    currentObj = -1;
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
        Objects[i]->Draw();
    }
}

/**
    Remove a seleção de todos os objetos filhos.
**/
void Universe::SelectNone()
{
    currentObj = -1;

    // Remove a seleção de todos. Caso contrário ficara com a BBox.
    for (size_t i = 0; i < ObjCount(); i++)
    {
        Objects[i]->SetSelected(false);
    }

    // Remove o ponto dos vertices.
    for (size_t i = 0; i < ObjCount(); ++i)
    {
        Objects[i]->SetSelectedVertex(-1);
    }
}

/**
    Seleciona um poligono. Se possuir um selecionado, troca por outro.
    @return Retorna o poligono selecionado ou NULL.
**/
PGraf Universe::SelectNextObj()
{
    currentObj++;

    if (currentObj >= (int) ObjCount())
    {
        currentObj = -1;
        return NULL;
    }

    return Objects[currentObj];
}

/**
    Retorna o poligono selecionado ou NULL.
    @return Um poligono.
**/
PGraf Universe::GetSelectedObj()
{
    if (currentObj == -1)
    {
        return NULL;
    }

    return Objects[currentObj];
}