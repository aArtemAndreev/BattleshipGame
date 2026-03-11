#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "Field.h"

class MyWidget : public QWidget {  // Убрали Q_OBJECT
public:
    MyWidget(Field f, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Field field;
};

#endif