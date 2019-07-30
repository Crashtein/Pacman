#include "game.h"
#include "ui_game.h"
#include <sys/stat.h>


Game::Game(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    QPixmap background(":/Image/GameBackground");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
}

Game::~Game()
{
    delete ui;
}

void Game::on_start_pushButton_clicked()
{
    struct stat buf;
    QString mapName;
    mapName=ui->lineEdit->text();
    if ( stat(mapName.toStdString().c_str(), &buf) == 0 ){
        gamemap = new GameMap;
        gamemap->numberOfPlayers=ui->PlayerNumberBox->value();
        gamemap->loadMap(mapName);
        gamemap->gameNumberUpdateCycles=ui->GameSpeedBox->value();
        gamemap->show();
    }
}

void Game::on_quit_pushButton_clicked()
{
    exit(0);
}

