#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "Field.h"

class MyWidget : public QWidget {

private:
    Field field;
    void paintEvent(QPaintEvent *event) override;
    
public:
    MyWidget(Field f);
    ~MyWidget() = default;
};

#endif