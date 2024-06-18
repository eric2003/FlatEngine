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
    void ComputeBoxCollisions();
    void DrawBoxRotate( float delta );
    void DrawBoxTranslate( float dx, float dy );
    void DrawBoxTranslate();
    void CalBoxTranslate( float dx, float dy );
    void CalBoxRotate( float delta );
private:
    void AddBoxAlpha( const QRectF & boxRect, QColor fillColor, float angle );
    void AddBoxTEST( const QRectF & boxRect, QColor fillColor );
    void AddFlatBodyToScene();
private:
    QGraphicsScene * scene;
    GraphicsView * view;
    int width = 800;
    int height = 600;
private:
    std::vector<FlatBody> bodyList;
    std::vector<int> outlineColors;
    std::vector<QGraphicsItem *> itemList;
    std::vector<float> dxList, dyList, rotList;
};
