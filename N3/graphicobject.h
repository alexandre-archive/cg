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
        int   primitive, currentVertex, selectedChildren;
    public:
        Color          BackColor;
        BBox           Bbox;
        vector<PGraf>  Objects;
        vector<Point>  Points;
        float          LineWidth;

        GraphicObject();
        ~GraphicObject();

        void Draw(bool isChildren = false, bool isParentSelected = false);
        void DrawBBox(bool isChildren = false, bool isParentSelected = false);
        void DrawPoint(Point p);

        void ChangePrimitive();

        size_t ObjCount() { return this->Objects.size(); };

        bool IsMouseInside(int x, int y);
        int  GetSelectedVertexIndex(int x, int y);
        void CalculateBBox();
        bool IsSelected() { return this->selected; };
        void SetSelected(bool selected) { this->selected = selected; };

        bool HasSelectedVertex() { return currentVertex >= 0; };
        void SetSelectedVertex(int index) { this->currentVertex = index; };
        Point& GetSelectedVertex();
        void DeleteSelectedVertex();

        void SetSelectedChildren(int index) { this->selectedChildren = index; };
        PGraf GetSelectedChildren() { return this->selectedChildren < 0 ? NULL : this->Objects[this->selectedChildren]; };
};