#ifndef BATTLESHIPGAME_BATTLEFIELD_H
#define BATTLESHIPGAME_BATTLEFIELD_H

#include <QWidget>
#include "Field.h"

class BattlefieldWindow : public QWidget {
public:
    BattlefieldWindow(QWidget* parent, Field playerField, Field botField);
private:
    Field playerField;
    Field botField;
};



#endif
