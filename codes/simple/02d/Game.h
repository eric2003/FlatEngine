#pragma once
#include <QObject>

class QGraphicsScene;
class GraphicsView;
class QKeyEvent;
class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    ~Game();
public:
    void Initialize();
public slots:
    void Draw(QKeyEvent *event);
private:
    QGraphicsScene * scene;
    GraphicsView * view;
    int width = 1280;
    int height = 768;
};
