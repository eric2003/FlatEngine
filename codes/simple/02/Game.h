#pragma once
#include <cmath>

class QGraphicsScene;
class GraphicsView;
class Game 
{
public:
    Game();
    ~Game();
public:
    void Initialize();
private:
    QGraphicsScene * scene;
    GraphicsView * view;
    int width = 1280;
    int height = 768;
};
