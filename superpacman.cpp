#include "superpacman.h"

SuperPacman::SuperPacman()
{

}

SuperPacman::SuperPacman(int posX, int posY, int pNumber, GameMap *map)
{
    x=posX*picWidth;
    y=posY*picHeight;
    isBlock=false;
    isConsumable=false;
    isVulnerable=false;
    isPlayer=true;
    direction=none;
    counter=0;
    score=0;
    graphicPacmanOpen=true;
    directionChanged=true;
    playerNumber=pNumber;
    this->gamemap=map;
    this->draw();
    pixItem->setZValue(4);
}

