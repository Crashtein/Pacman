#include "movable.h"

Movable::Movable()
{

}

void Movable::moveLeft()
{
    MapObject *wskMapObject;
    bool isPossible=true;
    wskMapObject=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(x-wskMapObject->xValue()==picWidth && wskMapObject->isBlock && y-wskMapObject->yValue()<picHeight && y-wskMapObject->yValue()>-picHeight){
            isPossible=false;
            break;
        }
        wskMapObject=wskMapObject->nextMapObject;
    }
    if(y==gamemap->mapHeight*picWidth || y==-picHeight){
        isPossible=false;
    }
    if(isPossible){
        if(x==-picWidth){
            x=gamemap->mapWidth*picWidth;
        }else{
            x-=gamemap->gameSpeed;
        }
        pixItem->setX(x);
        if(newDirection==left && direction!=left){
            directionChanged=true;
            direction=left;
        }
    }else{
        switch(direction){
        case up:
            this->moveUp();
            break;
        case down:
            this->moveDown();
            break;
        case right:
            this->moveRight();
            break;
        default:
            break;
        }
    }
}

void Movable::moveRight()
{
    MapObject *wskMapObject;
    bool isPossible=true;
    wskMapObject=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(x-wskMapObject->xValue()==-picWidth && wskMapObject->isBlock && y-wskMapObject->yValue()<picHeight && y-wskMapObject->yValue()>-picHeight){
            isPossible=false;
            break;
        }
        wskMapObject=wskMapObject->nextMapObject;
    }
    if(y==gamemap->mapHeight*picWidth || y==-picHeight){
        isPossible=false;
    }
    if(isPossible){
        if(x==gamemap->mapWidth*picWidth){
            x=-picWidth;
        }else{
            x+=gamemap->gameSpeed;
        }
        pixItem->setX(x);
        if(newDirection==right && direction!=right){
            directionChanged=true;
            direction=right;
        }
    }else{
        switch(direction){
        case up:
            this->moveUp();
            break;
        case left:
            this->moveLeft();
            break;
        case down:
            this->moveDown();
            break;
        default:
            break;
        }
    }
}

void Movable::moveUp()
{
    MapObject *wskMapObject;
    bool isPossible=true;
    wskMapObject=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(y-wskMapObject->yValue()==picHeight && wskMapObject->isBlock && x-wskMapObject->xValue()<picWidth && x-wskMapObject->xValue()>-picWidth){
            isPossible=false;
            break;
        }
        wskMapObject=wskMapObject->nextMapObject;
    }
    if(x==gamemap->mapWidth*picWidth || x==-picWidth){
        isPossible=false;
    }
    if(isPossible){
        if(y==-picHeight){
            y=gamemap->mapHeight*picHeight;
        }else{
            y-=gamemap->gameSpeed;
        }
        pixItem->setY(y);
        if(newDirection==up && direction!=up){
            directionChanged=true;
            direction=up;
        }
    }else{
        switch(direction){
        case left:
            this->moveLeft();
            break;
        case down:
            this->moveDown();
            break;
        case right:
            this->moveRight();
            break;
        default:
            break;
        }
    }
}

void Movable::moveDown()
{
    MapObject *wskMapObject;
    bool isPossible=true;
    wskMapObject=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(y-wskMapObject->yValue()==-picHeight && wskMapObject->isBlock && x-wskMapObject->xValue()<picWidth && x-wskMapObject->xValue()>-picWidth){
            isPossible=false;
            break;
        }
        wskMapObject=wskMapObject->nextMapObject;
    }
    if(x==gamemap->mapWidth*picWidth || x==-picWidth){
        isPossible=false;
    }
    if(isPossible){
        if(y==gamemap->mapHeight*picHeight){
            y=-picHeight;
        }else{
            y+=gamemap->gameSpeed;
        }
        pixItem->setY(y);
        if(newDirection==down && direction!=down){
            directionChanged=true;
            direction=down;
        }
    }else{
        switch(direction){
        case up:
            this->moveUp();
            break;
        case left:
            this->moveLeft();
            break;
        case right:
            this->moveRight();
            break;
        default:
            break;
        }
    }
}


