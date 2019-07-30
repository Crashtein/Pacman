#ifndef SUPERPACMAN_H
#define SUPERPACMAN_H
#include "pacman.h"


class SuperPacman: public Pacman
{
public:
    SuperPacman();
    SuperPacman(int posX,int posY,int pNumber,GameMap *map);
};

#endif // SUPERPACMAN_H
