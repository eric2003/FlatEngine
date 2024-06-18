#include "GraphicsView.h"
#include <QKeyEvent>
#include <iostream>

GraphicsView::GraphicsView()
{
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        QPoint point = event->pos();
        qDebug() << "mousePressEvent point = " << point.x() << " " << point.y();
        //emit mouseClicked( point );
    }
    QGraphicsView::mousePressEvent( event );
}

void GraphicsView::mouseMoveEvent( QMouseEvent * event )
{
    QPoint point = event->pos();
    qDebug() << "mouseMoveEvent point = " << point.x() << " " << point.y();
    //emit mouseClicked( point );
    QGraphicsView::mouseMoveEvent( event );
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
    QGraphicsView::keyPressEvent(event);
}
