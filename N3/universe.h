#ifndef BASE_H
    #define BASE_H
    #include "base.h"
#endif

#ifndef GRAPHIC_OBJECT_H
    #define GRAPHIC_OBJECT_H
    #include "graphicobject.h"
#endif

/**
    Representa o Mundo e contém todos os Objetos Gráficos.
**/
class Universe : public GraphicContainer
{
    public:
        Universe();
        ~Universe();
        void Draw();
        void Clear() { this->objects.clear(); };

        PPoint GetSelectedPoint();
        bool   HasSelectedPoint();
        void   DeleteSelectedPoint();
};

typedef Universe* PUniverse;