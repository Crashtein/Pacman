#include "game.h"
#include "gamemap.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;
    game.show();
    return a.exec();
}
