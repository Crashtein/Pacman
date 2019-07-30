#include "gamemap.h"
#include "ui_gamemap.h"
#include "gamemap.h"
#include "game.h"
#include "mapobject.h"
#include "block.h"
#include "coin.h"
#include "monster.h"
#include "pacman.h"
#include <fstream>


GameMap::GameMap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameMap)
{
    QWidget::grabKeyboard();
    QWidget::setFocusPolicy(Qt::StrongFocus);
    ui->setupUi(this);

    numberOfPlayers=0;
    gameSpeed=1;
    gameNumberUpdateCycles=1;
    scene = new QGraphicsScene();
    timer=new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    srand(time(NULL));

    superPacman=nullptr;
}

GameMap::~GameMap()
{
    while(mapObjectHead!=nullptr){
        MapObject *wskMapObject=mapObjectHead->nextMapObject;
        delete mapObjectHead;
        mapObjectHead=wskMapObject;
    }
    delete timer;
    delete mapObjectHead;
    delete scene;
    delete ui;
}

void GameMap::loadMap(QString mapname){
    int playersToAdd=numberOfPlayers;
    mapObjectHead = new Block(0,0,this);
    delete mapObjectHead;
    mapObjectHead=nullptr;
    MapObject *wskMapObject;
    std::ifstream data;
    data.open(mapname.toStdString().c_str(), std::ios::in);
    int temp;
    if(data.good()==true){
        data>>mapHeight>>mapWidth;
        for(int i=0;i<mapHeight;i++){
            for(int j=0;j<mapWidth;j++){
                data>>temp;
                if(i==0 && j==0){
                    if(temp==0){
                        mapObjectHead=new Block(j,i);
                    }else if(temp==1){
                        mapObjectHead=new Coin(j,i);
                    }else if(temp==2){
                        mapObjectHead=new Monster(j,i);
                    }else if(temp==3 && playersToAdd>0){
                        mapObjectHead=new Pacman(j,i,numberOfPlayers-playersToAdd+1);
                        playersToAdd--;
                    }
                    wskMapObject=mapObjectHead;
                    wskMapObject->nextMapObject=nullptr;
                }else{
                    if(temp==0){
                        wskMapObject->nextMapObject=new Block(j,i);
                        wskMapObject=wskMapObject->nextMapObject;
                        wskMapObject->nextMapObject=nullptr;
                    }else if(temp==1){
                        wskMapObject->nextMapObject=new Coin(j,i);
                        wskMapObject=wskMapObject->nextMapObject;
                        wskMapObject->nextMapObject=nullptr;
                    }else if(temp==2){
                        wskMapObject->nextMapObject=new Monster(j,i);
                        wskMapObject=wskMapObject->nextMapObject;
                        wskMapObject->nextMapObject=nullptr;
                    }else if(temp==3 && playersToAdd>0){
                        wskMapObject->nextMapObject=new Pacman(j,i,numberOfPlayers-playersToAdd+1);
                        playersToAdd--;
                        wskMapObject=wskMapObject->nextMapObject;
                        wskMapObject->nextMapObject=nullptr;
                    }
                }
            }
        }
    }
    data.close();
    ui->graphicsView->setFixedSize(mapWidth*mapObjectHead->picWidth,mapHeight*mapObjectHead->picHeight);
    ui->graphicsView->setScene(scene);
}

void GameMap::updateScore(int pNum, int newScore)
{
    switch(pNum){
    case 1:
        ui->lcdNumber_player1->display(newScore);
        break;
    case 2:
        ui->lcdNumber_player2->display(newScore);
        break;
    case 3:
        ui->lcdNumber_player3->display(newScore);
        break;
    case 4:
        ui->lcdNumber_player4->display(newScore);
        break;
    default:
        break;
    }
}

void GameMap::playerExecution(MapObject *player)
{
    MapObject *wskMapObject,*wskMapObject2;
    wskMapObject=mapObjectHead->nextMapObject;
    wskMapObject2=mapObjectHead;
    while(wskMapObject!=nullptr){
        if(player==wskMapObject){
            wskMapObject=wskMapObject->nextMapObject;
            delete wskMapObject2->nextMapObject;
            wskMapObject2->nextMapObject=wskMapObject;
            break;
        }
        wskMapObject2=wskMapObject;
        wskMapObject=wskMapObject->nextMapObject;
    }
}

void GameMap::update()
{
    for(int i=gameNumberUpdateCycles;i>0;i--){
        MapObject *wskMapObject;
        wskMapObject=mapObjectHead;
        while(wskMapObject!=nullptr){
            wskMapObject->update();
            wskMapObject=wskMapObject->nextMapObject;
        }
        scene->update();
    }
    //sprawdzanie czy pozostały jeszcze jakieś coiny/monstery, jesli nie, zakoncz gre
    bool finishGame=true;
    MapObject *wskMapObject;
    wskMapObject=mapObjectHead;
    while(wskMapObject!=nullptr){
        if(!wskMapObject->isPlayer && !wskMapObject->isBlock){
            finishGame=false;
            break;
        }
        wskMapObject=wskMapObject->nextMapObject;
    }
    if(finishGame){
        timer->stop();
    }
}

void GameMap::keyPressEvent(QKeyEvent *event)
{
    MapObject *wskMapObject;
    wskMapObject=mapObjectHead;
    switch(event->key()){
    case Qt::Key_Space:
        if(timer->isActive()){
            timer->stop();
        }else{
            timer->start(30);
        }
        break;
    case Qt::Key_Escape:
        this->~GameMap();
        break;
    case Qt::Key_Up:
        while(wskMapObject!=nullptr){
            wskMapObject->move(up,1);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_Down:
        while(wskMapObject!=nullptr){
            wskMapObject->move(down,1);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_Left:
        while(wskMapObject!=nullptr){
            wskMapObject->move(left,1);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_Right:
        while(wskMapObject!=nullptr){
            wskMapObject->move(right,1);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_W:
        while(wskMapObject!=nullptr){
            wskMapObject->move(up,2);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_S:
        while(wskMapObject!=nullptr){
            wskMapObject->move(down,2);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_A:
        while(wskMapObject!=nullptr){
            wskMapObject->move(left,2);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_D:
        while(wskMapObject!=nullptr){
            wskMapObject->move(right,2);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_8:
        while(wskMapObject!=nullptr){
            wskMapObject->move(up,3);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_5:
        while(wskMapObject!=nullptr){
            wskMapObject->move(down,3);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_4:
        while(wskMapObject!=nullptr){
            wskMapObject->move(left,3);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_6:
        while(wskMapObject!=nullptr){
            wskMapObject->move(right,3);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_U:
        while(wskMapObject!=nullptr){
            wskMapObject->move(up,4);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_J:
        while(wskMapObject!=nullptr){
            wskMapObject->move(down,4);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_H:
        while(wskMapObject!=nullptr){
            wskMapObject->move(left,4);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    case Qt::Key_K:
        while(wskMapObject!=nullptr){
            wskMapObject->move(right,4);
            wskMapObject=wskMapObject->nextMapObject;
        }
        break;
    default:
        break;
    }
}




