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
#include "FlatBody.h"
#include <iostream>

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

    QRectF boxRect( 0, 0, 100, 50 );
    QGraphicsRectItem * box = new QGraphicsRectItem( boxRect );

    QGraphicsPolygonItem iii;

    //box->setBrush( Qt::red );
    //box->setPen(pen);
    //this->scene->addItem(box);

    //FlatVector position(0, 0);
    //float width = boxRect.width();
    //float height = boxRect.height();

    //FlatBody flatBody(position, width, height, ShapeType::Box);

    this->Initialize();
}

Game::~Game()
{
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

    //int bodyCount = 10;
    //this->CreateCircles( bodyCount, x1, y1, x2, y2 );
    int bodyCount = 10;
    this->CreateBoxes( bodyCount, x1, y1, x2, y2 );
}

void Game::CreateCircles( int bodyCount, float x1, float y1, float x2, float y2 )
{
    for ( int i = 0; i < bodyCount; ++ i )
    {
        ShapeType type = static_cast< ShapeType >( RandomHelper::RandomInteger(0,1) );
        float x = RandomHelper::RandomSingle( x1, x2 );
        float y = RandomHelper::RandomSingle( y1, y2 );
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

void Game::CreateBoxes( int bodyCount, float x1, float y1, float x2, float y2 )
{
    for ( int i = 0; i < bodyCount; ++ i )
    {
        ShapeType type = static_cast< ShapeType >( RandomHelper::RandomInteger(0,1) );
        float x = RandomHelper::RandomSingle( x1, x2 );
        float y = RandomHelper::RandomSingle( y1, y2 );
        std::cout << " x, y = " << x << " " << y << "\n";
        const int width = 50;
        const int height = 50;
        QRectF boxRect( x, y, width, height );
        QGraphicsRectItem * box = new QGraphicsRectItem( boxRect );

        int r = RandomHelper::RandomInteger(0,255);
        int g = RandomHelper::RandomInteger(0,255);
        int b = RandomHelper::RandomInteger(0,255);
        QColor fillColor( r, g, b );
        box->setBrush(fillColor);
        qDebug() << "box->type() = " << box->type();
        this->scene->addItem(box);

        QPen pen = QPen( Qt::white );
        pen.setColor(Qt::white);
        pen.setWidth( 3 );
        box->setPen(pen);

        FlatVector position(x+width/2, y+height/2);
        FlatBody flatBody(position, width, height, ShapeType::Box);
        this->bodyList.push_back(flatBody);
        this->outlineColors.push_back(Qt::white);
    }
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

void Game::DrawBoxRotate(float delta)
{
    QList<QGraphicsItem *> itemList = this->scene->items();

    for ( int i = 0; i < itemList.size(); ++ i )
    {
        QGraphicsItem * item = itemList[ i ];
        QGraphicsRectItem * rItem = dynamic_cast<QGraphicsRectItem *>( item );
        QPointF offset = rItem->sceneBoundingRect().center();

        qDebug() << "rItem->pos() 000 = " << rItem->pos();

        //QColor cc = 9;
        QColor cc = Qt::GlobalColor(7);
        //QColor cc = Qt::blue;

        QPen pen = rItem->pen();
        //pen.setColor(Qt::red);
        pen.setColor(cc);
        rItem->setPen( pen );

        QTransform transform;
        transform.translate(offset.x(),offset.y());
        transform.rotate(delta);
        transform.translate(-offset.x(),-offset.y());
        rItem->setPos(transform.map(rItem->pos()));
        rItem->setRotation(rItem->rotation() + delta);

        FlatBody &flatBody = this->bodyList[ i ];
        int oColor = this->outlineColors[ i ];
        //QPen pen = rItem->pen();
        //pen.setColor(oColor);
        //rItem->setPen( pen );

        flatBody.Rotate(delta);
        flatBody.GetTransformedVertices();

        qDebug() << "rItem->rect()" << rItem->rect();
        qDebug() << "rItem->rect().center()" << rItem->rect().center();
        qDebug() << "position = " << flatBody.position.x << " " << flatBody.position.y;
        qDebug() << flatBody.transformedVertices[ 0 ].x << " "
            <<flatBody.transformedVertices[ 0 ].y;
        qDebug() << flatBody.transformedVertices[ 1 ].x << " "
            <<flatBody.transformedVertices[ 1 ].y;
        qDebug() << flatBody.transformedVertices[ 2 ].x << " "
            <<flatBody.transformedVertices[ 2 ].y;
        qDebug() << flatBody.transformedVertices[ 3 ].x << " "
            <<flatBody.transformedVertices[ 3 ].y;


        qDebug() << "rItem->pos() 111 = " << rItem->pos();
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

    float delta = 90.0;

    //this->DrawCircleCollisions(dx, dy);
    this->ComputeBoxCollisions();
    this->DrawBoxRotate(delta);

}

void Game::Move(QGraphicsItem *item, const FlatVector &dr)
{
    item->setPos(item->x()+dr.x,item->y()+dr.y);
}

void Game::ComputeBoxCollisions()
{
    QList<QGraphicsItem *> itemList = this->scene->items();

    int nElements = this->bodyList.size();

    for ( int i = 0; i < nElements; ++ i )
    {
        this->outlineColors[i] = Qt::white;
    }

    for ( int i = 0; i < nElements - 1; ++ i )
    {
        FlatBody &flatBodyA = this->bodyList[ i ];
        flatBodyA.GetTransformedVertices();

        for ( int j = i + 1; j < nElements; ++ j )
        {
            FlatBody &flatBodyB = this->bodyList[ j ];
            flatBodyB.GetTransformedVertices();
            if( Collisions::IntersectPolygons(flatBodyA.transformedVertices, 
                                              flatBodyB.transformedVertices ) )
            {
                this->outlineColors[i] = Qt::red;
                this->outlineColors[j] = Qt::red;
            }
        }
    }
}
