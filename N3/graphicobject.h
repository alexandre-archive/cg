#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

/**
    Representa um Objeto Gráfico no Universo.
**/
class GraphicObject
{
    private:
        bool selected;
        int  primitive;
        Color color;
    public:
        BBox                   Bbox;
        vector<GraphicObject>  Objects;
        vector<Point>          Points;

        GraphicObject();
        ~GraphicObject();

        void Draw();
        void DrawBBox();
        void DrawPoint(Point p);
        void ChangePrimitive();
        bool IsMouseInside(int x, int y);
        void CalculateBBox();
        void SetSelected(bool selected) { this->selected = selected; };
        void SetColor(float r, float g, float b)
        { 
            this->color.r = r;
            this->color.g = g;
            this->color.b = b;
        };
        void ChangeRColor();
        void ChangeGColor();
        void ChangeBColor();
};

typedef GraphicObject* PGraf;