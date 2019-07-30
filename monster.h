#ifndef MONSTER_H
#define MONSTER_H
#include "movable.h"

class Monster: public Movable
{
public:
    Monster();
    ~Monster();
    Monster(int posX, int posY);
    void draw();            //definicje wirtualnych funkcji z MapObject
    void update();
    void move(int dir,int num);
    void graphicUpdate();
};

#endif // MONSTER_H
