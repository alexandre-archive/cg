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
        void SelectNone();
        void Draw();
        void SetSelectedObj(int index) { this->currentObj = index; };
        bool HasSelectedObj() { return currentObj >= 0; };
        PGraf GetSelectedObj();
        size_t ObjCount() { return this->Objects.size(); };
        PGraf SelectNextObj();
};

typedef Universe* PUniverse;