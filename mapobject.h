#ifndef MAPOBJECT_H
#define MAPOBJECT_H
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "gamemap.h"


class MapObject
{
public:
    MapObject();
    MapObject(GameMap *map);
    virtual ~MapObject()=0;
    virtual void update()=0;    //virtual update dla każdego elementu
    virtual void draw()=0;      //rysowanie elementu na scenie gamemap
    virtual void move(int dir,int num)=0;   //funkcja dla ruchu w żądanym kierunku gracza o numerze num
    int xValue();   //zwrocenie pozycji x
    int yValue();   //zwrocenie pozycji y

    static GameMap *gamemap;    //statyczny wskaźnik na GameMap, który stworzył ten MapObject
    static int picHeight;   //rozdzielczosc obrazkow, wysokosc
    static int picWidth;    //rozdzielczosc obrazkow, szerokosc
    bool isConsumable;      //true dla coin
    bool isBlock;           //true dla block
    bool isVulnerable;      //true gdy monster wrazliwy na pacmana
    bool isPlayer;          //true gdy gracz
    int score;              //punktacja
    MapObject *nextMapObject;       //wskaznik na nastepny element listy

protected:
    int x;      //wspolrzedna x
    int y;      //wspolrzedna y
    QGraphicsPixmapItem *pixItem;   //element przypisywany do sceny
    QPixmap pix;                    //tekstura

};

#endif // MAPOBJECT_H
