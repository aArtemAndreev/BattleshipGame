#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPoint>
#include "Field.h"

class GameWindow;

class MyWidget : public QWidget {
public:
    MyWidget(Field& f, GameWindow* gameWindow, QWidget *parent = nullptr);

    ~MyWidget() override = default;
    
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    
private:
    Field& field;
    GameWindow* gameWindow;
    QPoint hoverCell;
    
    QPoint posToCell(const QPoint& pos) const;
};

#endif