#ifndef BATTLESHIPGAME_BATTLEFIELDUIX_H
#define BATTLESHIPGAME_BATTLEFIELDUIX_H

#include <QWidget>
#include "Field.h"

class BattlefieldUIX : public QWidget {
public:
    BattlefieldUIX(Field f, std::shared_ptr<bool> whoseStep, QWidget *parent = nullptr);    void markHit(int y, int x);    
    void markMiss(int y, int x);     
    void markDamaged(int y, int x);  
    void markSunk(int y, int x);
    void setClickListener(std::function<void(int,int)> callback);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private:
    Field field;
    std::shared_ptr<bool> whoseStep;
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

