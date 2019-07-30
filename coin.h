#ifndef COIN_H
#define COIN_H
#include "mapobject.h"

class Coin: public MapObject
{
public:
    Coin();
    ~Coin();
    Coin(int posX,int posY);    //zalecany konstruktor, podanie wspolrzednych
    void update();      //definicje wirtualnych funkcji z MapObject
    void draw();
    void move(int dir,int num); //nic nie robi
};

#endif // COIN_H
