#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
signals:
    void keyPressed(QKeyEvent *event);
};

#endif // GRAPHICSVIEW_H
