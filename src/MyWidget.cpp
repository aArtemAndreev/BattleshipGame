#include "MyWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include "GameWindow.h"
#include <QDebug>

MyWidget::MyWidget(Field& f, GameWindow* gameWindow, QWidget *parent) : QWidget(parent), field(f), gameWindow(gameWindow), hoverCell(-1, -1) {
    setFixedSize(500, 500);
    setMouseTracking(true);
    qDebug() << "🟢 MyWidget создан, gameWindow =" << gameWindow;
}

void MyWidget::paintEvent(QPaintEvent *event) {
    qDebug() << "\n🎨 paintEvent начался";

    if (!gameWindow) {
        qDebug() << "❌ paintEvent: gameWindow = nullptr!";
        return;
    }

    try {
        field.getCurrentPlace(1, 1);  // пробный вызов
    } catch (...) {
        qDebug() << "❌ paintEvent: field reference is invalid!";
        return;
    }

    QPainter painter(this);
    painter.fillRect(0, 0, 500, 500, QBrush{"#2980b9"});
    for (int i = 1; i <= 9; ++i) {
        painter.drawLine(50 * i, 0, 50 * i, 500);
        painter.drawLine(0, 50 * i, 500, 50 * i);
    }

    qDebug() << "  Начинаем отрисовку кораблей...";
    int shipsDrawn = 0;
    
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (field.getCurrentPlace(i, j) == '.') {
                painter.fillRect((j-1) * 50, (i-1) * 50, 50, 50, QBrush(Qt::gray));
                shipsDrawn++;
                qDebug() << "    Корабль в клетке [" << i << "," << j << "]";
            }
        }
    }
    qDebug() << "  Всего нарисовано кораблей:" << shipsDrawn;

    if (hoverCell.x() >= 0 && hoverCell.x() < 10 && hoverCell.y() >= 0 && hoverCell.y() < 10) {
        qDebug() << "  Подсветка клетки [" << hoverCell.y() << "," << hoverCell.x() << "]";
        painter.setOpacity(0.3);
        painter.fillRect(hoverCell.x() * 50, hoverCell.y() * 50, 50, 50, QBrush(Qt::yellow));
        painter.setOpacity(1.0);
    }

    qDebug() << "✅ paintEvent завершён";
}

QPoint MyWidget::posToCell(const QPoint& pos) const {
    int x = pos.x() / 50;
    int y = pos.y() / 50;
    qDebug() << "  posToCell: (" << pos.x() << "," << pos.y() << ") -> (" << x << "," << y << ")";
    return QPoint(x, y);
}

void MyWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint oldHover = hoverCell;
    hoverCell = posToCell(event->pos());
    if (oldHover != hoverCell) {
        qDebug() << "  Мышь переместилась на клетку [" << hoverCell.y() << "," << hoverCell.x() << "]";
        update();
    }
}

void MyWidget::mousePressEvent(QMouseEvent *event) {
    qDebug() << "\n🖱️ mousePressEvent: кнопка" << event->button();
    if (event->button() == Qt::LeftButton) {
        QPoint cell = posToCell(event->pos());
        qDebug() << "  Клик по клетке [" << cell.y() << "," << cell.x() << "]";
        if (cell.x() >= 0 && cell.x() < 10 && 
            cell.y() >= 0 && cell.y() < 10) {
                qDebug() << "  Клетка валидна, вызываем gameWindow->onCellClicked";
                if (!gameWindow) {
                    qDebug() << "  ❌ ОШИБКА: gameWindow = nullptr!";
                    return;
                }
            
            gameWindow->onCellClicked(cell.x(), cell.y());
        } else {
            qDebug() << "  ❌ Клетка вне границ!";
        }
    }
}