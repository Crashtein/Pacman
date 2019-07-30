#include "block.h"

Block::Block()
{

}

Block::~Block()
{
    delete pixItem;
}

Block::Block(int posX, int posY, GameMap *map)
{
    x=posX*picWidth;
    y=posY*picHeight;
    isBlock=true;
    isConsumable=false;
    isVulnerable=false;
    isPlayer=false;
    this->gamemap=map;
    this->draw();
    pixItem->setZValue(1);
}

Block::Block(int posX, int posY)
{
    x=posX*picWidth;
    y=posY*picHeight;
    isBlock=true;
    isConsumable=false;
    isVulnerable=false;
    isPlayer=false;
    this->draw();
    pixItem->setZValue(1);
}

void Block::draw(){
    pix=QPixmap(":/Image/Brick");
    pixItem= new QGraphicsPixmapItem;
    pixItem->setPixmap(pix);
    pixItem->setPos(x,y);
    gamemap->scene->addItem(pixItem);
}

void Block::update()
{

}

void Block::move(int dir, int num)
{
    //do nothing
    dir=num;
    num=dir;
}


