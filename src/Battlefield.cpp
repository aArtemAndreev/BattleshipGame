#include "Battlefield.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRandomGenerator>
#include "BattlefieldUIX.h"
#include "ShooterBot.h"
#include <functional>

bool isShipFullyHit(Field& field, int y, int x) {
    int startY = y;
    int startX = x;
    
    while (startY > 1 && field.getCurrentPlace(startY-1, x) == '.') {
        startY--;
    }
    while (startX > 1 && field.getCurrentPlace(y, startX-1) == '.') {
        startX--;
    }
    
    bool isHorizontal = false;
    if (startX < 10 && field.getCurrentPlace(startY, startX+1) == '.') {
        isHorizontal = true;
    }
    
    if (isHorizontal) {
        for (int i = startX; i <= 10; i++) {
            if (field.getCurrentPlace(startY, i) != '.') break;
            if (!field.isShipDamaged(startY, i)) {
                return false;
            }
        }
    } else {
        for (int i = startY; i <= 10; i++) {
            if (field.getCurrentPlace(i, startX) != '.') break;
            if (!field.isShipDamaged(i, startX)) {
                return false;
            }
        }
    }
    
    return true;
}

BattlefieldWindow::BattlefieldWindow(QWidget* parent, Field playerF, Field botF) 
    : QWidget(parent), playerField(playerF), botField(botF) {
    
    setWindowTitle("Морской бой");
    setFixedSize(1200, 600);
    
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            playerShots[i][j] = '0';
        }
    }
    
    isPlayerTurn = true;
    playerHits = 0;
    botHits = 0;
    
    botTimer = new QTimer(this);
    
    auto whoseStep = std::make_shared<bool>(false);
    shooterBot = new ShooterBot(playerField, whoseStep, this);
    
    QHBoxLayout* layout = new QHBoxLayout(this);
    
    shooterBot->setFixedSize(500, 500);
    botView = new BattlefieldUIX(botField, this, true);
    botView->setFixedSize(500, 500);
    
    layout->addWidget(shooterBot);
    layout->addWidget(botView);
    
    botView->setClickListener([this](int y, int x) {
        this->onPlayerShot(y, x);
    });
    
    connect(botTimer, &QTimer::timeout, this, [this]() {
        this->onBotShot();
    });
}

void BattlefieldWindow::onPlayerShot(int y, int x) {
    if (!isPlayerTurn) return;
    if (playerShots[y][x] != '0') return;
    
    if (botField.getCurrentPlace(y, x) == '.') {
        playerShots[y][x] = 'H';
        playerHits++;
        
        botField.markShipAsDamaged(y, x);
        botView->markDamaged(y, x);
        
        if (isShipFullyHit(botField, y, x)) {
            int startY = y, startX = x;
            
            while (startY > 1 && botField.getCurrentPlace(startY-1, x) == '.') startY--;
            while (startX > 1 && botField.getCurrentPlace(y, startX-1) == '.') startX--;
            
            bool isHorizontal = (startX < 10 && botField.getCurrentPlace(startY, startX+1) == '.');
            
            if (isHorizontal) {
                for (int i = startX; i <= 10; i++) {
                    if (botField.getCurrentPlace(startY, i) != '.') break;
                    botField.markShipAsSunk(startY, i);
                    botView->markSunk(startY, i);
                }
            } else {
                for (int i = startY; i <= 10; i++) {
                    if (botField.getCurrentPlace(i, startX) != '.') break;
                    botField.markShipAsSunk(i, startX);
                    botView->markSunk(i, startX);
                }
            }            
        }
        
        if (playerHits == 20) {
            QMessageBox::information(this, "ПОБЕДА!", "ТЫ ПОБЕДИЛ! 🎉");
            this->close();
            return;
        }
        
    } else {
        playerShots[y][x] = 'M';
        botView->markMiss(y, x);
        
        isPlayerTurn = false;
        botTimer->start(1000);
    }
}

void BattlefieldWindow::onBotShot() {
    botTimer->stop();
    
    if (isPlayerTurn) return;
    
    std::pair<int, int> shot = shooterBot->makeShot();
    int x = shot.first;
    int y = shot.second;
    
    if (playerField.getCurrentPlace(y, x) == '.') {
        botHits++;
        
        playerField.markShipAsDamaged(y, x);
        
        if (isShipFullyHit(playerField, y, x)) {
            int startY = y, startX = x;
            
            while (startY > 1 && playerField.getCurrentPlace(startY-1, x) == '.') startY--;
            while (startX > 1 && playerField.getCurrentPlace(y, startX-1) == '.') startX--;
            
            bool isHorizontal = (startX < 10 && playerField.getCurrentPlace(startY, startX+1) == '.');
            
            if (isHorizontal) {
                for (int i = startX; i <= 10; i++) {
                    if (playerField.getCurrentPlace(startY, i) != '.') break;
                    playerField.markShipAsSunk(startY, i);
                }
            } else {
                for (int i = startY; i <= 10; i++) {
                    if (playerField.getCurrentPlace(i, startX) != '.') break;
                    playerField.markShipAsSunk(i, startX);
                }
            }
            
            shooterBot->rememberShot(x, y, Kill);
            
        } else {
            shooterBot->rememberShot(x, y, Hit);
        }

        if (botHits == 20) {
            QMessageBox::information(this, "ПОРАЖЕНИЕ","Ты проиграл");
            this->close();
            return;
        }
        
        botTimer->start(1000);
        
    } else {
        shooterBot->rememberShot(x, y, Miss);
        isPlayerTurn = true;
    }
    
    shooterBot->update();
}