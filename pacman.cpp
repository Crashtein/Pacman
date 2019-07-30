#include "pacman.h"

Pacman::Pacman()
{

}

Pacman::~Pacman()
{
    delete pixItem;
}

Pacman::Pacman(int posX, int posY, int pNumber)
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
    this->draw();
    pixItem->setZValue(4);

}

void Pacman::draw()
{
    pix=QPixmap(":/Image/PacmanOpen");
    pixItem= new QGraphicsPixmapItem;
    pixItem->setPixmap(pix);
    pixItem->setPos(x,y);
    gamemap->scene->addItem(pixItem);
}

void Pacman::update()
{
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
    this->consumeCoin();
    this->graphicUpdate();
    this->meetMonster();
    gamemap->updateScore(playerNumber,score);
    if(score<0){
        gamemap->playerExecution(this);
    }
}

void Pacman::move(int dir, int num)
{
    if(playerNumber==num && direction!=dir){
        newDirection=dir;
    }
}

void Pacman::graphicUpdate()
{
    if(counter==10*gamemap->gameNumberUpdateCycles){
        if(!graphicPacmanOpen){
            pix=QPixmap(":/Image/PacmanOpen");
        }else{
            pix=QPixmap(":/Image/PacmanClosed");
        }
        directionChanged=true;
        counter=0;
        graphicPacmanOpen=!graphicPacmanOpen;
    }else{
        counter++;
    }

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

void Pacman::consumeCoin()
{
    MapObject *wskMapObject,*wskMapObject2;
    wskMapObject=gamemap->mapObjectHead->nextMapObject;
    wskMapObject2=gamemap->mapObjectHead;
    switch(direction){
    case up:
        while(wskMapObject!=nullptr){
            if(y-wskMapObject->yValue()==picHeight*3/4 && wskMapObject->isConsumable
                    && x-wskMapObject->xValue()<picWidth*3/4 && x-wskMapObject->xValue()>-picWidth*3/4){
                wskMapObject=wskMapObject->nextMapObject;
                delete wskMapObject2->nextMapObject;
                wskMapObject2->nextMapObject=wskMapObject;
                score+=10;
                break;
            }
            wskMapObject2=wskMapObject;
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case left:
        while(wskMapObject!=nullptr){
            if(x-wskMapObject->xValue()==picWidth*3/4 && wskMapObject->isConsumable
                    && y-wskMapObject->yValue()<picHeight*3/4 && y-wskMapObject->yValue()>-picHeight*3/4){
                wskMapObject=wskMapObject->nextMapObject;
                delete wskMapObject2->nextMapObject;
                wskMapObject2->nextMapObject=wskMapObject;
                score+=10;
                break;
            }
            wskMapObject2=wskMapObject;
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case down:
        while(wskMapObject!=nullptr){
            if(y-wskMapObject->yValue()==-picHeight*3/4 && wskMapObject->isConsumable
                    && x-wskMapObject->xValue()<picWidth*3/4 && x-wskMapObject->xValue()>-picWidth*3/4){
                wskMapObject=wskMapObject->nextMapObject;
                delete wskMapObject2->nextMapObject;
                wskMapObject2->nextMapObject=wskMapObject;
                score+=10;
                break;
            }
            wskMapObject2=wskMapObject;
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case right:
        while(wskMapObject!=nullptr){
            if(x-wskMapObject->xValue()==-picWidth*3/4 && wskMapObject->isConsumable
                    && y-wskMapObject->yValue()<picHeight*3/4 && y-wskMapObject->yValue()>-picHeight*3/4){
                wskMapObject=wskMapObject->nextMapObject;
                delete wskMapObject2->nextMapObject;
                wskMapObject2->nextMapObject=wskMapObject;
                score+=10;
            }
            wskMapObject2=wskMapObject;
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    default:
        break;
    }
}

void Pacman::meetMonster()
{
    MapObject *wskMapObject,*wskMapObject2;
    wskMapObject=gamemap->mapObjectHead->nextMapObject;
    wskMapObject2=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(y-wskMapObject->yValue()<picHeight/2 && y-wskMapObject->yValue()>0 && !wskMapObject->isConsumable && !wskMapObject->isBlock
                && x-wskMapObject->xValue()<picWidth/4 && x-wskMapObject->xValue()>-picWidth/4){
            if(wskMapObject->isVulnerable){
                wskMapObject=wskMapObject->nextMapObject;
                delete wskMapObject2->nextMapObject;
                wskMapObject2->nextMapObject=wskMapObject;
                score+=200;
            }else if (wskMapObject->isPlayer) {
                score-=200;
                wskMapObject->score-=200;
            }else{
                score-=50;
            }
            break;
        }
        wskMapObject2=wskMapObject;
        wskMapObject=wskMapObject->nextMapObject;
    }
    wskMapObject=gamemap->mapObjectHead->nextMapObject;
    wskMapObject2=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(x-wskMapObject->xValue()<picWidth/2 && x-wskMapObject->xValue()>0 && !wskMapObject->isConsumable && !wskMapObject->isBlock
                && y-wskMapObject->yValue()<picHeight/4 && y-wskMapObject->yValue()>-picHeight/4){
            if(wskMapObject->isVulnerable){
                wskMapObject=wskMapObject->nextMapObject;
                delete wskMapObject2->nextMapObject;
                wskMapObject2->nextMapObject=wskMapObject;
                score+=200;
            }else if (wskMapObject->isPlayer) {
                score-=200;
                wskMapObject->score-=200;
            }else{
                score-=50;
            }
            break;
        }
        wskMapObject2=wskMapObject;
        wskMapObject=wskMapObject->nextMapObject;
    }
    wskMapObject=gamemap->mapObjectHead->nextMapObject;
    wskMapObject2=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(y-wskMapObject->yValue()>-picHeight/2 && y-wskMapObject->yValue()<0 && !wskMapObject->isConsumable && !wskMapObject->isBlock
                && x-wskMapObject->xValue()<picWidth/4 && x-wskMapObject->xValue()>-picWidth/4){
            if(wskMapObject->isVulnerable){
                wskMapObject=wskMapObject->nextMapObject;
                delete wskMapObject2->nextMapObject;
                wskMapObject2->nextMapObject=wskMapObject;
                score+=200;
            }else if (wskMapObject->isPlayer) {
                score-=200;
                wskMapObject->score-=200;
            }else{
                score-=50;
            }
            break;
        }
        wskMapObject2=wskMapObject;
        wskMapObject=wskMapObject->nextMapObject;
    }
    wskMapObject=gamemap->mapObjectHead->nextMapObject;
    wskMapObject2=gamemap->mapObjectHead;
    while(wskMapObject!=nullptr){
        if(x-wskMapObject->xValue()>-picWidth/2 && x-wskMapObject->xValue()<0 && !wskMapObject->isConsumable && !wskMapObject->isBlock
                && y-wskMapObject->yValue()<picHeight/4 && y-wskMapObject->yValue()>-picHeight/4){
            if(wskMapObject->isVulnerable){
                wskMapObject=wskMapObject->nextMapObject;
                delete wskMapObject2->nextMapObject;
                wskMapObject2->nextMapObject=wskMapObject;
                score+=200;
            }else if (wskMapObject->isPlayer) {
                score-=200;
                wskMapObject->score-=200;
            }else{
                score-=50;
            }
            break;
        }
        wskMapObject2=wskMapObject;
        wskMapObject=wskMapObject->nextMapObject;
    }
}



