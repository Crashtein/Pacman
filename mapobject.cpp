#include "mapobject.h"

MapObject::~MapObject()
{

}

MapObject::MapObject()
{

}

GameMap* MapObject::gamemap=nullptr;
int MapObject::picWidth=48; //rozdzielczość tesktur
int MapObject::picHeight=48;

MapObject::MapObject(GameMap *map){
    gamemap=map;
}

int MapObject::xValue()
{
    return x;
}

int MapObject::yValue()
{
    return y;
}

