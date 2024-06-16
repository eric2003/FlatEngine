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

    //QRectF rect_scene( 0, 0, 1000, 800 );
    //QRectF rect_scene( -200, -200, 1000, 800 );
    //QRectF rect_scene( 0, 0, 100, 80 );
    this->scene = new QGraphicsScene();
    //this->scene->setSceneRect( rect_scene );
    //this->scene->setForegroundBrush(QBrush(Qt::red, Qt::CrossPattern));
    //this->scene->setForegroundBrush(QBrush(Qt::red));
    this->scene->setBackgroundBrush(QBrush(Qt::red));
    this->Initialize();

    this->view = new GraphicsView();
    this->view->setScene( this->scene );
    this->view->show();
    this->view->setFixedSize( 800, 600 );

    QColor color = QColor::fromRgb( 0x1b1b1b );
    this->view->setBackgroundBrush(color);
    QObject::connect(this->view, &GraphicsView::keyPressed,this,&Game::Draw);

    QRectF rect_scene( -200, -100, 400, 200 );
    QPen pen = QPen( Qt::white );
    pen.setWidth( 3 );

    //QGraphicsRectItem * item = new QGraphicsRectItem(rect_scene);
    //item->setPen( pen );
    //this->scene->addItem( item );

    QRectF rect1( 0, 0, 200, 200 );
    QGraphicsRectItem * item1 = new QGraphicsRectItem(rect1);
    item1->setPen( pen );
    this->scene->addItem( item1 );

    QGraphicsTextItem *textItem = new QGraphicsTextItem();
    textItem->setPlainText("Hello, QGraphicsTextItem!");
    //textItem->setPos(100, 100);
    textItem->setPos(0, 0);
    textItem->setDefaultTextColor(Qt::white);

    this->scene->addItem(textItem);

}

Game::~Game()
{
    delete this->view;
    delete this->scene;
}

void Game::Initialize()
{
    //int bodyCount = 10;
    int bodyCount = 2;

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

    //for ( int i = 0; i < bodyCount; ++ i )
    //{
    //    ShapeType type = static_cast< ShapeType >( RandomHelper::RandomInteger(0,1) );
    //    float x = RandomHelper::RandomSingle(left+padding,right-padding);
    //    float y = RandomHelper::RandomSingle(top+padding,bottom-padding);
    //    std::cout << " x, y = " << x << " " << y << "\n";
    //    const int DIAMETER = 50;
    //    auto circle = new QGraphicsEllipseItem(x, y, DIAMETER, DIAMETER);
    //    int r = RandomHelper::RandomInteger(0,255);
    //    int g = RandomHelper::RandomInteger(0,255);
    //    int b = RandomHelper::RandomInteger(0,255);
    //    QColor fillColor( r, g, b );
    //    circle->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    //    circle->setBrush(fillColor);
    //    QPen pen = QPen( Qt::white );
    //    pen.setWidth( 3 );
    //    circle->setPen(pen);
    //    qDebug() << "circle->type() = " << circle->type();
    //    this->scene->addItem(circle);
    //}
    {
        const int DIAMETER = 50;
        {
            int x = 100;
            int y = 100;

            QPen pen = QPen( Qt::white );
            pen.setWidth( 3 );

            auto circle = new QGraphicsEllipseItem( x, y, DIAMETER, DIAMETER );
            int r = RandomHelper::RandomInteger( 0, 255 );
            int g = RandomHelper::RandomInteger( 0, 255 );
            int b = RandomHelper::RandomInteger( 0, 255 );
            QColor fillColor( r, g, b );
            circle->setFlag( QGraphicsItem::ItemClipsChildrenToShape, true );
            circle->setBrush( Qt::red );
            //circle->setBrush( fillColor );
            circle->setPen( pen );
            this->scene->addItem( circle );

            //qDebug() << "centerI" << centerI.x << " " << centerI.y;
            //qDebug() << "circle x() y() " << circle->x() << " " << itemI->y();
            //qDebug() << "circle left() top() " << circle.left() << " " << rectI.top();
        }
        {
            int x = 100 + 60;
            int y = 100;

            QPen pen = QPen( Qt::white );
            pen.setWidth( 3 );

            auto circle = new QGraphicsEllipseItem( x, y, DIAMETER, DIAMETER );
            int r = RandomHelper::RandomInteger( 0, 255 );
            int g = RandomHelper::RandomInteger( 0, 255 );
            int b = RandomHelper::RandomInteger( 0, 255 );
            QColor fillColor( r, g, b );
            circle->setFlag( QGraphicsItem::ItemClipsChildrenToShape, true );
            //circle->setBrush( fillColor );
            circle->setBrush( Qt::blue );
            circle->setPen( pen );
            this->scene->addItem( circle );
        }
    }
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
            dx = -1.0;
            dy = 0.0;
            break;
        }
        case Qt::Key_Right:
        {
            dx = 1.0;
            dy = 0.0;
            break;
        }
        case Qt::Key_Up:
        {
            dx = 0.0;
            dy = -1.0;
            break;
        }
        case Qt::Key_Down:
        {
            dx = 0.0;
            dy = 1.0;
            break;
        }
        default:
            break;
    }

    QList<QGraphicsItem *> itemList = this->scene->items();

    //foreach ( QGraphicsItem *item, itemList)
    //{
    //    item->setPos(item->x()+dx,item->y()+dy);
    //}
    QGraphicsItem *item =itemList[1];
    item->setPos(item->x()+dx,item->y()+dy);
    QGraphicsEllipseItem * cItem = dynamic_cast<QGraphicsEllipseItem *>( item );
    QColor color = cItem->brush().color();
    qDebug() << "color.name()=" << color.name();

    for ( int i = 0; i < itemList.size() - 1; ++ i )
    {
        //qDebug() << "i=" << i;
        
        QGraphicsItem *itemI = itemList[i];
        QRectF rectI = itemI->boundingRect();
        float radiusI = rectI.width() / 2.0;
        FlatVector centerI;
        centerI.x = rectI.left() + radiusI;
        centerI.y = rectI.top() + radiusI;
        qDebug() << "centerI" << centerI.x << " " << centerI.y;
        qDebug() << "itemI x() y() " << itemI->x() << " " << itemI->y();
        qDebug() << "rectI left() top() " << rectI.left() << " " << rectI.top();

        for ( int j = i + 1; j < itemList.size(); ++ j )
        {
            //qDebug() << "j=" << j;
            QGraphicsItem *itemJ = itemList[j];
            QRectF rectJ = itemJ->boundingRect();
            float radiusJ = rectJ.width() / 2.0;
            FlatVector centerJ;
            centerJ.x = rectJ.left() + radiusJ;
            centerJ.y = rectJ.top() + radiusJ;

            qDebug() << "centerJ" << centerJ.x << " " << centerJ.y;
            qDebug() << "itemJ" << itemJ->x() << " " << itemJ->y();
            FlatVector normal;
            float depth;
            if( Collisions::IntersectCircles( centerI, radiusI, centerJ, radiusJ, normal, depth ) )
            {
                qDebug() << "centerI" << centerI.x << " " << centerI.y;
                qDebug() << "centerJ" << centerJ.x << " " << centerJ.y;
                this->Move(itemI, normal*depth);
                this->Move(itemJ, normal*depth);
            }
        }
    }
}


void Game::Move(QGraphicsItem *item, const FlatVector &dr)
{
    item->setPos(item->x()+dr.x,item->y()+dr.y);
}
