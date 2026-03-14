#ifndef BATTLESHIPGAME_BATTLEFIELDUIX_H
#define BATTLESHIPGAME_BATTLEFIELDUIX_H

#include <QWidget>
#include <QVector>
#include <functional>
#include "Field.h"

class BattlefieldUIX : public QWidget {
public:
    BattlefieldUIX(Field f, QWidget *parent = nullptr, bool isBotField = false);
    
    void markHit(int y, int x);      
    void markMiss(int y, int x);    
    void markDamaged(int y, int x);
    void markSunk(int y, int x);     
    
    void setClickListener(std::function<void(int,int)> callback);

    ~BattlefieldUIX() override = default;
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    
private:
    Field field;
    bool isBot;
    
    struct Shot {
        int y;
        int x;
        int type;  
    };
    
    QVector<Shot> shots;
    std::function<void(int,int)> clickCallback;
};

#endif