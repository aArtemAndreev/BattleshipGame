#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPoint>
#include "Field.h"

class GameWindow;

class MyWidget : public QWidget {
public:
    MyWidget(Field& f,  GameWindow* gameWindow, QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    Field& field;
    QPoint hoverCell;
    GameWindow* gameWindow;
    QPoint posToCell(const QPoint& pos) const;
};

#endif