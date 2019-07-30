#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <stdlib.h>
#include <time.h>

class MapObject;
class Pacman;
class Monster;


namespace Ui {
class GameMap;
}

class GameMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameMap(QWidget *parent = nullptr);
    ~GameMap();
    QGraphicsScene *scene;  //scena pod mape
    int mapWidth;   //szerokoscm mapy, ilosc pol
    int mapHeight;  //wysokosc mapy, ilosc pol
    int numberOfPlayers;    //ilosc graczy
    int gameSpeed;  //ilosc pikseli przeskakiwanych na jeden cykl, domyslnie 1
    int gameNumberUpdateCycles; //ilosc cykli update na jeden cykl timera
    QTimer *timer;  //timer
    MapObject *mapObjectHead;   //glowa listy z obiektami mapy
    void updateScore(int pNum,int newScore);    //wpisanie score do LCD UI
    void playerExecution(MapObject *player);    //usuwa podanego gracza
    void loadMap(QString mapname);     //ladowanie mapy

    MapObject *superPacman;

public slots:
    void update();      //update dla każdego obiektu MapObject

private:
    Ui::GameMap *ui;
    void keyPressEvent(QKeyEvent *event);   //obsluga klawiatury, sterowanie
};

#endif // GAMEMAP_H
