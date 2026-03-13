#ifndef BATTLESHIPGAME_BATTLEFIELD_H
#define BATTLESHIPGAME_BATTLEFIELD_H

#include <QWidget>
#include <QTimer>
#include "Field.h"

class BattlefieldWindow : public QWidget {
public:
    BattlefieldWindow(QWidget* parent, Field playerField, Field botField);
    
private slots:
    void onPlayerShot(int y, int x);
    void onBotShot();
    
private:
    Field playerField;
    Field botField;
    
    bool isPlayerTurn;  
    int playerHits;
    int botHits;
    
    char playerShots[12][12];
    
    class BattlefieldUIX* playerView;
    class BattlefieldUIX* botView;
    class ShooterBot* shooterBot;
    
    QTimer* botTimer;
};

#endif