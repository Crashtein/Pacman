#ifndef MOVABLE_H
#define MOVABLE_H
#include "mapobject.h"


#define none 0
#define left 1
#define up 2
#define right 3
#define down 4

class Movable: public MapObject
{
public:
    Movable();
    virtual void move(int dir,int num)=0;       //move
    int newDirection;       //nowy kierunek, wylosowany lub wskazany przez gracza

protected:
    virtual void graphicUpdate()=0;     //update
    void moveLeft();        //operacje poruszania się obiektu w danym kierunku
    void moveRight();
    void moveUp();
    void moveDown();        //
    int counter;        //licznik, na podstawie timera
    int direction;      //aktualny kierunek
    bool directionChanged;      //true gdy zmieniono kierunek
};

#endif // MOVABLE_H
