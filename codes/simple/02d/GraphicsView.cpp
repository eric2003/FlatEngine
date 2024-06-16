#include "GraphicsView.h"
#include <QKeyEvent>
#include <iostream>

GraphicsView::GraphicsView(QGraphicsScene *scene)
{
    this->setScene(scene);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    std::cout << "GraphicsView::mousePressEvent\n";
    qDebug() << "qDebug():GraphicsView::mousePressEvent";
}

void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "GraphicsView::keyPressEvent(QKeyEvent *event)";
    qDebug() << "text() = " << event->text() << " event->key() = " << event->key();

    emit keyPressed(event);
    QGraphicsView::keyPressEvent(event);
}
