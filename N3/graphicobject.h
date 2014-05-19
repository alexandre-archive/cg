#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

class GraphicObject;

typedef GraphicObject* PGraf;

/**
    Representa um Container Gráfico.
    Um container é uma coleção de objetos gráficos.
**/
class GraphicContainer
{
protected:
    vector<PGraf> objects;
public:
    /** 
        Adiciona um objeto gráfico.
        @param g objeto gŕafico.
    **/
    virtual void  AddObj(PGraf g);
    /**
        Procura um objeto pelo indece.
        @param index Indece.
        @return um objeto gráfico ou NULL.
    **/
    virtual PGraf  GetObj(int index);
    /**
        @return Total de objetos gráficos.
    **/
    size_t ObjCount() { return this->objects.size(); };
    /**
        Retorna o objeto gráfico selecionado pelo mode de seleção.
        @return Objeto gráfico.
    **/
    virtual PGraf  GetSelectedObj();
    /**
        Deleta o objeto gráfico selecionado.
    **/
    virtual void   DeleteSelectedObj();
    /**
        Seleciona um objeto gráfico.
        @param x Posição X do mouse.
        @param y Posição Y do mouse.
        @return true se selecionou o objeto.
    **/
    virtual bool   SelectObj(int x, int y);
    /**
        Remove a seleção de todos os objetos ou pontos.
    **/
    virtual void   SelectNone();
};

/**
    Representa um Objeto Gráfico no Universo.
**/
class GraphicObject : public GraphicContainer
{
protected:
    int            primitive;
    vector<Point>  points;
    BBox           bbox;
    /**
        Desenha um ponto no local do vértice selecionado.
        Facilitando a identificação.
    **/
    void DrawPoint(Point p);
    /**
        Desenha a BBox ao redor do Gráfico.
    **/
    void DrawBBox();
public:
    bool   IsSelected;
    Color  BackColor;
    float  LineWidth;

    GraphicObject();
    ~GraphicObject();

    /**
    Calcula a nova posição da BBox.
    **/
    void CalculateBBox();
    /**
        Altera a primitiva atual entre
        GL_LINE_LOOP ou GL_LINE_STRIP.
    **/
    void   ChangePrimitive();
    /**
        Desenha o Gráfico e seus filhos.
        Se estiver selecionado desenhará a BBox.
    **/
    void   Draw();
    /**
        Verifica se o gráfico é selecionável
        de acordo com a posição X e Y.

        @param x Posição X do mouse.
        @param y Posição Y do mouse.
    **/
    bool   IsSelectable(int x, int y);

    void   AddPoint(Point p);
    PPoint GetPoint(int index);
    PPoint GetLastPoint();
    size_t PointCount() { return this->points.size(); };
    /**
        Se X e Y corresponderem a um vértice, retorna a posição deste vértice.
        Caso contrário retornará -1.
        @param x
        @param y
        @return true se estiver dentro.
    **/
    bool   IsPointSelectable(int x, int y);
    PPoint GetSelectedPoint();
    bool   HasSelectedPoint();
    void   DeleteSelectedPoint();
};