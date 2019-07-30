#include "coin.h"

Coin::Coin()
{

}

Coin::~Coin()
{
    delete pixItem;
}

Coin::Coin(int posX, int posY)
{
    x=posX*picWidth;
    y=posY*picWidth;
    isBlock=false;
    isConsumable=true;
    isVulnerable=false;
    isPlayer=false;
    this->draw();
    pixItem->setZValue(2);
}

void Coin::update()
{

}

void Coin::draw()
{
    pix=QPixmap(":/Image/Coin");
    pixItem= new QGraphicsPixmapItem;
    pixItem->setPixmap(pix);
    pixItem->setPos(x,y);
    gamemap->scene->addItem(pixItem);
}

void Coin::move(int dir, int num)
{
    //do nothing
    dir=num;
    num=dir;
}
