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
class Universe
{
    private:
        int currentObj;
    public:
        vector<PGraf> Objects;
        Universe();
        ~Universe();
        void   Draw();
        void   SelectNone();
        bool   HasSelectedObj() { return currentObj >= 0; };
        void   SetSelectedObj(int index) { this->currentObj = index; };
        PGraf  GetSelectedObj();
        PGraf  SelectNextObj();
        void   DeleteSelectedObject();
        size_t ObjCount() { return this->Objects.size(); };
        PGraf GetParentObj();
};

typedef Universe* PUniverse;