#ifndef PACMAN_H
#define PACMAN_H
#include "movable.h"
#include <QKeyEvent>
#include <QTimer>



class Pacman: public Movable
{
public:
    Pacman();
    ~Pacman();
    Pacman(int posX, int posY,int pNumber);
    void draw();        //definicje funkcji z MapObject
    void update();
    void move(int dir,int num);     //wywolanie ruchu w nowym kierunku
    int playerNumber;               //numer gracza

protected:
    bool graphicPacmanOpen;     //true gdy pacman otwarty, false dla pacmana zamknietego
    void consumeCoin();         //zjedz coin ktory jest przed toba
    void meetMonster();         //rozbudowana funkcja, wykrywa czy pacman spotkal monster lub drugiego pacmana, odejmuje score/zabija pacmana/monstera
    void graphicUpdate();       //aktualizacja graficzna

};

#endif // PACMAN_H
