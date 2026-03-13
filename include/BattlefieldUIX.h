#ifndef BATTLESHIPGAME_BATTLEFIELDUIX_H
#define BATTLESHIPGAME_BATTLEFIELDUIX_H

#include <QWidget>
#include "Field.h"

class BattlefieldUIX : public QWidget {
public:
    BattlefieldUIX(Field f, std::shared_ptr<bool> whoseStep, QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    Field field;
    std::shared_ptr<bool> whoseStep;
};

#endif
