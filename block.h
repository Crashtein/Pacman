#ifndef BLOCK_H
#define BLOCK_H
#include "mapobject.h"

class Block: public MapObject
{
public:
    Block();
    ~Block();
    Block(int posX,int posY,GameMap *map);  //konstruktor z przypisaniem adresu do static GameMap *gamemap;
    Block(int posX,int posY);   //normalny konstruktor
    void draw();        //definicje wirtualnych funkcji z MapObject
    void update();
    void move(int dir,int num); //nic nie robi
};

#endif // BLOCK_H
