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

    //QObject::connect(this->view, &GraphicsView::keyPressed,this,&Game::Draw);
    QObject::connect(this->view, &GraphicsView::keyPressed,this,&Game::DrawTEST);

    QPen pen = QPen( Qt::white );
    pen.setWidth( 3 );

    this->Initialize();

    QGraphicsRectItem * itemScene = new QGraphicsRectItem(rect_scene);
    itemScene->setPen( QPen( Qt::red ) );
    this->scene->addItem( itemScene );

    //QRectF rect1( 0, 0, 200, 300 );
    //QGraphicsRectItem * item1 = new QGraphicsRectItem(rect1);
    //item1->setPen( pen );
    //this->scene->addItem( item1 );

    //QPoint ptext_view( 0, this->view->height()-30 );
    //QPointF ptext_scene = this->view->mapToScene( ptext_view );

    //QGraphicsTextItem *textItem = new QGraphicsTextItem();
    //textItem->setPlainText("Hello, QGraphicsTextItem!");
    //textItem->setPos(0, 0);
    //textItem->setDefaultTextColor(Qt::white);

    //this->scene->addItem(textItem);
    //textItem->setPos( ptext_scene );
    //int kkk = 1;
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
            circle->setPen( pen );
            this->scene->addItem( circle );

            this->test_item1 = circle;

            QRectF bRect = circle->boundingRect();
            QRectF rect = circle->rect();

            QPolygon ttt = this->view->mapFromScene( rect );
            QPoint aa = this->view->mapFromScene( x, y );


            QPointF p_scene( 0.0, 0.0 );
            QPoint p_view = this->view->mapFromScene( p_scene );
            qDebug() << "p_scene : " << p_scene.x() << " " << p_scene.y();
            qDebug() << "p_view : " << p_view.x() << " " << p_view.y();

            QPointF ipos = circle->pos();
            qDebug() << "ipos " << ipos.x() << " " <<ipos.y();
            QPointF ipos_scene = circle->mapToScene(ipos);
            qDebug() << "ipos_scene " << ipos_scene.x() << " " <<ipos_scene.y();

            qDebug() << "rect " << rect.left() << " " << rect.top() << " " << rect.width() << " " << rect.height();

            FlatVector centerI;
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
            this->test_item2 = circle;

            this->PrintCircleInfo( circle );

            circle->setPos( circle->pos().x() + 10, circle->pos().y() );

            this->PrintCircleInfo( circle );
        }
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

void Game::DrawTEST(QKeyEvent *event)
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

    QGraphicsEllipseItem * itemI = this->test_item1;

    FlatVector centerI;
    float radiusI;
    this->ComputeCenter( itemI, centerI, radiusI );

    qDebug() << "centerI" << centerI.x << " " << centerI.y;
    qDebug() << "itemI" << itemI->x() << " " << itemI->y();

    
    itemI->setPos(itemI->x()+dx,itemI->y()+dy);

    QGraphicsEllipseItem * itemJ = this->test_item2;
    FlatVector centerJ;
    float radiusJ;

    this->ComputeCenter( itemJ, centerJ, radiusJ );

    qDebug() << "centerJ" << centerJ.x << " " << centerJ.y;
    qDebug() << "itemJ" << itemJ->x() << " " << itemJ->y();
    FlatVector normal;
    float depth;
    if( Collisions::IntersectCircles( centerI, radiusI, centerJ, radiusJ, normal, depth ) )
    {
        qDebug() << "centerI" << centerI.x << " " << centerI.y;
        qDebug() << "centerJ" << centerJ.x << " " << centerJ.y;
        qDebug() << "normal" << normal.x << " " << normal.y;
        qDebug() << "depth" << depth;
        FlatVector rd = normal * depth;
        qDebug() << "rd" << rd.x << " " << rd.y;
        //this->Move(itemI, normal*depth);
        this->Move(itemJ, normal*depth);
    }
}


void Game::Move(QGraphicsItem *item, const FlatVector &dr)
{
    item->setPos(item->x()+dr.x,item->y()+dr.y);
}
