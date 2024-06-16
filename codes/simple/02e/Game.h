#pragma once
#include <QObject>

class QGraphicsScene;
class GraphicsView;
class QKeyEvent;
class QGraphicsItem;
class FlatVector;
class Game : public QObject
{
    Q_OBJECT
public:
    Game();
    ~Game();
public:
    void Initialize();
private:
    void Move(QGraphicsItem *item, const FlatVector &dr);
public slots:
    void Draw(QKeyEvent *event);
private:
    QGraphicsScene * scene;
    GraphicsView * view;
    int width = 800;
    int height = 600;
};
