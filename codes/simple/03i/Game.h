#pragma once
#include <QObject>
#include "FlatBody.h"
#include <vector>

class QGraphicsScene;
class GraphicsView;
class QKeyEvent;
class QGraphicsItem;
class QGraphicsEllipseItem;
class QGraphicsRectItem;
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
    void PrintBoxInfo( QGraphicsRectItem * item );
    void PrintCircleInfo( QGraphicsEllipseItem * item );
    void ComputeCenter( QGraphicsEllipseItem * item, FlatVector & center, float & radius );
    void CreateCircles( int bodyCount, float x1, float y1, float x2, float y2 );
    void CreateBoxes( int bodyCount, float x1, float y1, float x2, float y2 );
    void DrawCircleCollisions( float dx, float dy );
    void DrawBoxRotate( float delta );
private:
    QGraphicsEllipseItem * test_item1;
    QGraphicsEllipseItem * test_item2;
private:
    QGraphicsScene * scene;
    GraphicsView * view;
    int width = 800;
    int height = 600;
private:
    std::vector<FlatBody> bodyList;
};
