#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <random>
#include <iostream>
#include "RandomHelper.h"

void Initialize( QGraphicsScene *scene );

enum class ShapeType
{
    Circle = 0,
    Box = 1
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int width = 1280;
    int height = 768;

    //create a scene
    QGraphicsScene *scene = new QGraphicsScene();
    Initialize( scene );
    QGraphicsView *view = new QGraphicsView(scene);
    view->show();
    view->setFixedSize(width, height);

    return a.exec();
}

void Initialize( QGraphicsScene *scene )
{
    int width = 1280;
    int height = 768;

    int bodyCount = 10;

    for ( int i = 0; i < bodyCount; ++ i )
    {
        int type = RandomHelper::RandomInteger(0,2);
        std::cout << " type = " << type << "\n";
    }

    float left = 0.0;
    float right = width;
    float top = 0.0;
    float bottom = height;
    const float padding = 20.0f;

    for ( int i = 0; i < bodyCount; ++ i )
    {
        ShapeType type = static_cast< ShapeType >( RandomHelper::RandomInteger(0,1) );
        float x = RandomHelper::RandomSingle(left+padding,right-padding);
        float y = RandomHelper::RandomSingle(top+padding,bottom-padding);
        std::cout << " x, y = " << x << " " << y << "\n";
        if ( type == ShapeType::Circle )
        {
            const int DIAMETER = 100;
            auto circle = new QGraphicsEllipseItem(x, y, DIAMETER, DIAMETER);
            circle->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
            circle->setBrush(Qt::green);
            scene->addItem(circle);
        }
        else
        {
            QGraphicsRectItem *rect = new QGraphicsRectItem();
            rect->setBrush( Qt::red );
            rect->setRect(x,y,100,100);
            scene->addItem(rect);
        }

    }



}
