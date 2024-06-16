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

    QColor color = QColor::fromRgb(0x1b1b1b);

    //view->setBackgroundBrush(Qt::yellow);
    view->setBackgroundBrush(color);

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

    // 将十六进制颜色代码#1b1b1b转换为QColor对象
    QColor color = QColor::fromRgb(0x1b1b1b); // 0x开头表示十六进制

    // 使用颜色对象创建画刷
    QBrush brush(color);

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
