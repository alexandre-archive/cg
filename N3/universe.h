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
        /**
            Desenha o universo.
        **/
        void Draw();
        /**
            Remove todos os objetos do universo.
        **/
        void Clear() { this->objects.clear(); };
        PGraf  GetObjSelectedPoint();
        PPoint GetSelectedPoint();
        bool   HasSelectedPoint();
        void   DeleteSelectedPoint();
};

typedef Universe* PUniverse;