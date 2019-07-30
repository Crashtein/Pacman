#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "gamemap.h"
#include "QtCore"

namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

private slots:
    void on_start_pushButton_clicked(); //wywolanie startu
    void on_quit_pushButton_clicked();  //wywolanie zakonczenia dzialania programu

private:
    Ui::Game *ui;
    GameMap *gamemap;
};

#endif // GAME_H
