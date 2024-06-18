#include <QApplication>
#include "Game.h"

std::shared_ptr<Game> game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = std::make_shared<Game>();
    return a.exec();
}
