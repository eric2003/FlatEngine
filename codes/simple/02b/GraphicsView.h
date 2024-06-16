#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView( QGraphicsScene *scene );

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
signals:
    void keyPressed(QKeyEvent *event);
};

#endif // GRAPHICSVIEW_H
