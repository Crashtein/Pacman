#include "monster.h"

Monster::Monster()
{

}

Monster::~Monster()
{
    delete pixItem;
}

Monster::Monster(int posX, int posY)
{
    x=posX*picWidth;
    y=posY*picWidth;
    counter=0;
    isBlock=false;
    isConsumable=false;
    isVulnerable=false;
    isPlayer=false;
    this->draw();
    direction=none;
    newDirection=none;
    pixItem->setZValue(3);
}

void Monster::draw()
{
    pix=QPixmap(":/Image/Monster");
    pixItem= new QGraphicsPixmapItem;
    pixItem->setPixmap(pix);
    pixItem->setPos(x,y);
    gamemap->scene->addItem(pixItem);
}

void Monster::update()
{
    //losowanie kierunku
    bool repeatRand=true;
    while(repeatRand){
        repeatRand=false;
        newDirection=(rand() %4 + 1);
        if((newDirection==up && direction==down) || (newDirection==down && direction==up)
                || (newDirection==left && direction==right) || (newDirection==right && direction==left)){
            repeatRand=true;
        }
        if(newDirection==up && direction==down){
            MapObject *wskMapObject=gamemap->mapObjectHead;
            while(wskMapObject!=nullptr){
                if(y-wskMapObject->yValue()==-picHeight && wskMapObject->isBlock && x-wskMapObject->xValue()<picWidth
                        && x-wskMapObject->xValue()>-picWidth){
                    repeatRand=false;
                    break;
                }
                wskMapObject=wskMapObject->nextMapObject;
            }
        }
        if(newDirection==down && direction==up){
            MapObject *wskMapObject=gamemap->mapObjectHead;
            while(wskMapObject!=nullptr){
                if(y-wskMapObject->yValue()==picHeight && wskMapObject->isBlock && x-wskMapObject->xValue()<picWidth
                        && x-wskMapObject->xValue()>-picWidth){
                    repeatRand=false;
                    break;
                }
                wskMapObject=wskMapObject->nextMapObject;
            }
        }
        if(newDirection==left && direction==right){
            MapObject *wskMapObject=gamemap->mapObjectHead;
            while(wskMapObject!=nullptr){
                if(x-wskMapObject->xValue()==-picWidth && wskMapObject->isBlock && y-wskMapObject->yValue()<picHeight
                        && y-wskMapObject->yValue()>-picHeight){
                    repeatRand=false;
                    break;
                }
                wskMapObject=wskMapObject->nextMapObject;
            }
        }
        if(newDirection==right && direction==left){
            MapObject *wskMapObject=gamemap->mapObjectHead;
            while(wskMapObject!=nullptr){
                if(x-wskMapObject->xValue()==picWidth && wskMapObject->isBlock && y-wskMapObject->yValue()<picHeight
                        && y-wskMapObject->yValue()>-picHeight){
                    repeatRand=false;
                    break;
                }
                wskMapObject=wskMapObject->nextMapObject;
            }
        }
    }
    //
//wykrywanie gracza
    MapObject *wskMapObject;
    wskMapObject=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(y-wskMapObject->yValue()<picHeight*2 && y-wskMapObject->yValue()>0 && wskMapObject->isPlayer
                && x-wskMapObject->xValue()<picWidth && x-wskMapObject->xValue()>-picWidth){
            newDirection=up;
            break;
        }
        wskMapObject=wskMapObject->nextMapObject;
    }
    wskMapObject=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(x-wskMapObject->xValue()<picWidth*2 && x-wskMapObject->xValue()>0 && wskMapObject->isPlayer
                && y-wskMapObject->yValue()<picHeight && y-wskMapObject->yValue()>-picHeight){
            newDirection=left;
            break;
        }
        wskMapObject=wskMapObject->nextMapObject;
    }
    wskMapObject=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(y-wskMapObject->yValue()>-picHeight*2 && y-wskMapObject->yValue()<0 && wskMapObject->isPlayer
                && x-wskMapObject->xValue()<picWidth && x-wskMapObject->xValue()>-picWidth){
            newDirection=down;
            break;
        }
        wskMapObject=wskMapObject->nextMapObject;
    }
    wskMapObject=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(x-wskMapObject->xValue()>-picWidth*2 && x-wskMapObject->xValue()<0 && wskMapObject->isPlayer
                && y-wskMapObject->yValue()<picHeight && y-wskMapObject->yValue()>-picHeight){
            newDirection=right;
        }
        wskMapObject=wskMapObject->nextMapObject;
    }
//
    switch(newDirection){
    case up:
        this->moveUp();
        break;
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

    if(counter==500*gamemap->gameNumberUpdateCycles){
        pix=QPixmap(":/Image/MonsterVulnerable");
        counter=-150*gamemap->gameNumberUpdateCycles;
        directionChanged=true;
        isVulnerable=true;
    }else if (counter==0) {
        pix=QPixmap(":/Image/Monster");
        counter++;
        directionChanged=true;
        isVulnerable=false;
    }else{
        counter++;
    }

    this->graphicUpdate();
}

void Monster::move(int dir, int num)
{
    //do nothing
    dir=num;
    num=dir;
}

void Monster::graphicUpdate()
{
    if(directionChanged){
        switch(direction){
        case up:
            pixItem->setPixmap(QPixmap(pix.transformed(QTransform().rotate(270))));
            break;
        case left:
            pixItem->setPixmap(QPixmap(pix.transformed(QTransform().scale(-1,1))));
            break;
        case down:
            pixItem->setPixmap(QPixmap(pix.transformed(QTransform().rotate(90))));
            break;
        default:
            pixItem->setPixmap(pix);
            break;
        }
        directionChanged=false;
    }
}

