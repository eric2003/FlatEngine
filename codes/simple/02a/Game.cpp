#include "Game.h"
#include "RandomHelper.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "GraphicsView.h"
#include <iostream>

enum class ShapeType
{
    Circle = 0,
    Box = 1
};

Game::Game()
{
    //create a scene
    this->scene = new QGraphicsScene();
    this->Initialize();
    this->view = new GraphicsView( scene );
    this->view->show();
    this->view->setFixedSize( width, height );

    QColor color = QColor::fromRgb( 0x1b1b1b );
    this->view->setBackgroundBrush(color);
}

Game::~Game()
{
    delete this->view;
    delete this->scene;
}

void Game::Initialize()
{
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
        const int DIAMETER = 50;
        auto circle = new QGraphicsEllipseItem(x, y, DIAMETER, DIAMETER);
        int r = RandomHelper::RandomInteger(0,255);
        int g = RandomHelper::RandomInteger(0,255);
        int b = RandomHelper::RandomInteger(0,255);
        QColor fillColor( r, g, b );
        circle->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
        circle->setBrush(fillColor);
        QPen pen = QPen( Qt::white );
        pen.setWidth( 3 );
        circle->setPen(pen);
        qDebug() << "circle->type() = " << circle->type();
        this->scene->addItem(circle);
        //QList<QGraphicsItem *> itemList = this->scene->items();
    }
}

