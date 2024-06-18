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
    //QRectF rect_scene( -300, -200, 600, 400 );
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

    const int width = 50;
    const int height = 50;
    QRectF boxRect( 0, 0, 100, 50 );
    //QGraphicsRectItem * box = new QGraphicsRectItem( boxRect );
    this->box = new QGraphicsRectItem( boxRect );

    this->box->setBrush(Qt::blue);
    this->box->setPen(pen);
    this->scene->addItem(this->box);

    //this->box->setPos( this->box->pos().x() + 200, this->box->pos().y() );

    //this->DrawBoxRotate(this->box, 10);

    //this->Initialize();
}

Game::~Game()
{
    delete this->box;
    delete this->view;
    delete this->scene;
}

void Game::Initialize()
{
    QRectF rect = this->scene->sceneRect();
    float left = rect.left();
    float right = rect.right();
    float top = rect.top();
    float bottom = rect.bottom();

    const float padding = 20.0f;
    float x1 = left + padding;
    float y1 = top + padding;
    float x2 = right - padding;
    float y2 = bottom - padding;

    int bodyCount = 10;
    //this->CreateCircles( bodyCount, x1, y1, x2, y2 );
    //this->CreateBoxes( bodyCount, x1, y1, x2, y2 );
}

void Game::PrintBoxInfo( QGraphicsRectItem * item )
{
    QRectF rect = item->rect();
    QPointF ipos = item->pos();
    qDebug() << "ipos " << ipos.x() << " " <<ipos.y();
    QPointF ipos_scene = item->mapToScene(ipos);
    qDebug() << "ipos_scene " << ipos_scene.x() << " " <<ipos_scene.y();
    qDebug() << "rect " << rect.left() << " " << rect.top() << " " << rect.width() << " " << rect.height();
    qDebug() << "item->rotation() = " << item->rotation();
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

void Game::DrawCircleCollisions( float dx, float dy )
{
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
                FlatVector dr1 = -normal * depth / 2;
                FlatVector dr2 = normal * depth / 2;
                qDebug() << "normal " << normal.x << " " << normal.y;
                qDebug() << "depth " << depth << " depth/2 = " << depth/2;
                qDebug() << "dr1 " << dr1.x << " " << dr1.y;
                qDebug() << "dr2 " << dr2.x << " " << dr2.y;
                this->Move(itemI, -normal*depth/2);
                this->Move(itemJ, normal*depth/2);
            }
        }
    }
}

void Game::DrawBoxTranslate( QGraphicsRectItem * rItem, float dx, float dy )
{
    QRectF brect = rItem->boundingRect();
    QRectF sbrect = rItem->sceneBoundingRect();
    QRectF rect = rItem->rect();
    QPointF center = rect.center();
    qDebug() << "rect:" << rect.left() << " " << rect.top()
        << " " << rect.right() << " " << rect.bottom();
    qDebug() << "boundingRect:" << brect.left() << " " << brect.top()
        << " " << brect.right() << " " << brect.bottom();
    qDebug() << "sceneBoundingRect:" << sbrect.left() << " " << sbrect.top()
        << " " << sbrect.right() << " " << sbrect.bottom();
    qDebug() << "center:" << center.x() << " " << center.y();
    qDebug() << "pos 000:" << rItem->pos().x() << " " << rItem->pos().y();

    rItem->setPos(rItem->pos().x()+dx,rItem->pos().y()+dy);
    qDebug() << "pos 111:" << rItem->pos().x() << " " << rItem->pos().y();
}

void Game::DrawBoxRotate( QGraphicsRectItem * rItem, float delta )
{
    QRectF rect = rItem->rect();
    QPointF center = rect.center();
    qDebug() << "rect:" << rect.left() << " " << rect.top()
        << " " << rect.right() << " " << rect.bottom();
    qDebug() << "center:" << center.x() << " " << center.y();
    qDebug() << "pos 000:" << rItem->pos().x() << " " << rItem->pos().y();

    QTransform t;
    t.translate(center.x(), center.y());
    t.rotate(delta);
    t.translate(-center.x(), -center.y());
    rItem->setPos(t.map(rItem->pos()));
    qDebug() << "pos 111:" << rItem->pos().x() << " " << rItem->pos().y();
    rItem->setRotation(rItem->rotation() + delta);
}

void Game::Draw(QKeyEvent *event)
{
    //qDebug() << "Game::Draw()";
    double dx = 0.0;
    double dy = 0.0;
    switch ( event->key() )
    {
        case Qt::Key_Left:
        {
            dx = -10.0;
            dy = 0.0;
            this->DrawBoxTranslate(this->box,dx,dy);
            break;
        }
        case Qt::Key_Right:
        {
            dx = 10.0;
            dy = 0.0;
            this->DrawBoxTranslate(this->box,dx,dy);
            break;
        }
        case Qt::Key_Up:
        {
            dx = 0.0;
            dy = -10.0;
            this->DrawBoxTranslate(this->box,dx,dy);
            break;
        }
        case Qt::Key_Down:
        {
            dx = 0.0;
            dy = 10.0;
            this->DrawBoxTranslate(this->box,dx,dy);
            break;
        }
        case Qt::Key_Return:
        {
            dx = 0.0;
            dy = 0.0;
            float delta = 10.0;
            this->DrawBoxRotate(this->box,delta);
            break;
        }
        default:
            break;
    }

    //float delta = 10.0;
    //this->DrawBoxRotate(this->box,delta);

}

void Game::Move(QGraphicsItem *item, const FlatVector &dr)
{
    item->setPos(item->x()+dr.x,item->y()+dr.y);
}
