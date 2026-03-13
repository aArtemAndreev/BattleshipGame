#include "BattlefieldUIX.h"
#include <QPainter>
#include <QMouseEvent>

BattlefieldUIX::BattlefieldUIX(Field f, std::shared_ptr<bool> whoseStep, QWidget *parent) 
    : QWidget(parent),field(f),whoseStep(whoseStep),isBot(false),clickCallback(nullptr){}

void BattlefieldUIX::setClickListener(std::function<void(int,int)> callback) {
    clickCallback = callback;
}

void BattlefieldUIX::markHit(int y, int x) {
    Shot shot;
    shot.y = y;
    shot.x = x; 
    shot.type = 1;  
    shots.append(shot);
    update();
}

void BattlefieldUIX::markMiss(int y, int x) {
    Shot shot;
    shot.y = y;
    shot.x = x;
    shot.type = 0;  
    shots.append(shot);
    update();
}

void BattlefieldUIX::markDamaged(int y, int x) {
    Shot shot;
    shot.y = y;
    shot.x = x;
    shot.type = 2; 
    shots.append(shot);
    update();
}

void BattlefieldUIX::markSunk(int y, int x) {
    Shot shot;
    shot.y = y;
    shot.x = x;
    shot.type = 3;  
    shots.append(shot);
    update();
}

void BattlefieldUIX::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    
    painter.fillRect(0, 0, 500, 500, QBrush("#2980b9"));
    
    painter.setPen(QPen(Qt::black, 2));
    for (int i = 1; i <= 10; ++i) {
        painter.drawLine(50 * i, 0, 50 * i, 500);
        painter.drawLine(0, 50 * i, 500, 50 * i);
    }
    
    if (!isBot) {
        for (int i = 1; i <= 10; ++i) {
            for (int j = 1; j <= 10; ++j) {
                int x = 50 * (j-1);
                int y = 50 * (i-1);
                
                if (field.getCurrentPlace(i, j) == '.') {
                    if (field.isShipSunk(i, j)) {
                        painter.fillRect(x, y, 50, 50, QBrush(Qt::black));
                    } else if (field.isShipDamaged(i, j)) {
                        painter.fillRect(x, y, 50, 50, QBrush(Qt::yellow));
                    } else {
                        painter.fillRect(x, y, 50, 50, QBrush(Qt::white));
                    }
                }
            }
        }
    }
    
    for (const Shot& shot : shots) {
        int x = 50 * (shot.x - 1);
        int y = 50 * (shot.y - 1);
        
        if (shot.type == 0) {
            painter.setBrush(Qt::white);
            painter.setPen(Qt::white);
            painter.drawEllipse(x + 15, y + 15, 20, 20);
        }
        else if (shot.type == 1) {
            
            painter.setPen(QPen(Qt::red, 4));
            painter.drawLine(x + 5, y + 5, x + 45, y + 45);
            painter.drawLine(x + 45, y + 5, x + 5, y + 45);
        }
        else if (shot.type == 2) {
            painter.setPen(QPen(Qt::yellow, 4));
            painter.drawLine(x + 5, y + 5, x + 45, y + 45);
            painter.drawLine(x + 45, y + 5, x + 5, y + 45);
        }
        else if (shot.type == 3) {
            painter.setPen(QPen(Qt::black, 4));
            painter.drawLine(x + 5, y + 5, x + 45, y + 45);
            painter.drawLine(x + 45, y + 5, x + 5, y + 45);
        }
    }
    
    if (!isBot && whoseStep && !(*whoseStep)) {
        painter.setPen(QPen(Qt::white, 12));
        painter.setFont(QFont("Arial", 20, QFont::Bold));
        painter.drawText(rect(), Qt::AlignCenter, "Бот думает...");
    }
}

void BattlefieldUIX::mousePressEvent(QMouseEvent *event) {
    if (!isBot) return;
    if (!whoseStep) return;
    if (!(*whoseStep)) return;
    
    if (event->button() == Qt::LeftButton) {
        int x = event->pos().x() / 50 + 1;
        int y = event->pos().y() / 50 + 1;
        
        if (x >= 1 && x <= 10 && y >= 1 && y <= 10) {
            for (const Shot& shot : shots) {
                if (shot.x == x && shot.y == y) return;
            }
            
            if (clickCallback) {
                clickCallback(y, x);
            }
        }
    }
}