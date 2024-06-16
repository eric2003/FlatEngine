#include "Game.h"
#include "RandomHelper.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QStatusBar>
#include <QVBoxLayout>
#include "GraphicsView.h"
#include "FlatVector.h"
#include "Collisions.h"
#include <iostream>

enum class ShapeType
{
    Circle = 0,
    Box = 1
};

Game::Game()
{
    QRectF rect_scene( 0, 0, 600, 400 );
    this->scene = new QGraphicsScene();
    this->scene->setSceneRect( rect_scene );
    this->scene->setBackgroundBrush(QBrush(Qt::yellow));

    this->view = new GraphicsView();
    this->view->setScene( this->scene );
    this->view->show();
    this->view->setFixedSize( 800, 600 );

    QColor color = QColor::fromRgb( 0x1b1b1b );
    this->view->setBackgroundBrush(color);

    QObject::connect(this->view, &GraphicsView::keyPressed,this,&Game::Draw);

    QPen pen = QPen( Qt::white );
    pen.setWidth( 3 );

    this->Initialize();
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
    float right = 600;
    float top = 0.0;
    float bottom = 400;
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
    }
}

void Game::PrintCircleInfo( QGraphicsEllipseItem * item )
{
    QRectF bRect = item->boundingRect();
    QRectF rect = item->rect();

    QPointF ipos = item->pos();
    qDebug() << "ipos " << ipos.x() << " " <<ipos.y();
    QPointF ipos_scene = item->mapToScene(ipos);
    qDebug() << "ipos_scene " << ipos_scene.x() << " " <<ipos_scene.y();
    qDebug() << "rect " << rect.left() << " " << rect.top() << " " << rect.width() << " " << rect.height();

}

void Game::ComputeCenter( QGraphicsEllipseItem * item, FlatVector &center, float &radius )
{
    QRectF rect = item->rect();
    radius = rect.width() / 2.0;

    center.x = item->pos().x() + rect.left() + radius;
    center.y = item->pos().y() + rect.top() + radius;
}

void Game::Draw(QKeyEvent *event)
{
    qDebug() << "Game::Draw()";
    double dx = 0.0;
    double dy = 0.0;
    switch ( event->key() )
    {
        case Qt::Key_Left:
        {
            dx = -10.0;
            dy = 0.0;
            break;
        }
        case Qt::Key_Right:
        {
            dx = 10.0;
            dy = 0.0;
            break;
        }
        case Qt::Key_Up:
        {
            dx = 0.0;
            dy = -10.0;
            break;
        }
        case Qt::Key_Down:
        {
            dx = 0.0;
            dy = 10.0;
            break;
        }
        default:
            break;
    }

    QList<QGraphicsItem *> itemList = this->scene->items();

    QGraphicsItem *item =itemList[0];
    item->setPos(item->x()+dx,item->y()+dy);

    for ( int i = 0; i < itemList.size() - 1; ++ i )
    {
        QGraphicsItem * itemI = itemList[ i ];
        QGraphicsEllipseItem * cItemI = dynamic_cast<QGraphicsEllipseItem *>( itemI );
        FlatVector centerI;
        float radiusI;
        this->ComputeCenter( cItemI, centerI, radiusI );

        for ( int j = i + 1; j < itemList.size(); ++ j )
        {
            QGraphicsItem *itemJ = itemList[j];
            QGraphicsEllipseItem * cItemJ = dynamic_cast<QGraphicsEllipseItem *>( itemJ );
            FlatVector centerJ;
            float radiusJ;
            this->ComputeCenter( cItemJ, centerJ, radiusJ );
            FlatVector normal;
            float depth;
            if( Collisions::IntersectCircles( centerI, radiusI, centerJ, radiusJ, normal, depth ) )
            {
                //this->Move(itemI, normal*depth);
                this->Move(itemJ, normal*depth);
            }
        }
    }
}

void Game::Move(QGraphicsItem *item, const FlatVector &dr)
{
    item->setPos(item->x()+dr.x,item->y()+dr.y);
}
