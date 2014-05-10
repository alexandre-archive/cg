#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

class GraphicObject;

typedef GraphicObject* PGraf;

/**
    Representa um Objeto Gráfico no Universo.
**/
class GraphicObject
{
    private:
        bool  selected;
        Color color;
        int   primitive, currentVertex, selectedChildren;
    public:
        BBox           Bbox;
        vector<PGraf>  Objects;
        vector<Point>  Points;
        float          LineWidth;

        GraphicObject();
        ~GraphicObject();

        void Draw();
        void DrawBBox();
        void DrawPoint(Point p);
        void ChangePrimitive();
        bool IsMouseInside(int x, int y);
        int  GetSelectedVertexIndex(int x, int y);
        void CalculateBBox();
        void SetSelected(bool selected) { this->selected = selected; };
        void SetSelectedVertex(int index) { this->currentVertex = index; };
        bool HasSelectedVertex() { return currentVertex >= 0; };
        Point& GetSelectedVertex();
        void SetColor(float r, float g, float b)
        { 
            this->color.r = r;
            this->color.g = g;
            this->color.b = b;
        };

        void ChangeRColor();
        void ChangeGColor();
        void ChangeBColor();

        void SetSelectedChildren(int index) { this->selectedChildren = index; };
        PGraf GetSelectedChildren() { return this->selectedChildren < 0 ? NULL : this->Objects[this->selectedChildren]; };
};