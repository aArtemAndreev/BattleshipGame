#include <iostream>
#include <array>
#include <random>
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <optional>

class Ship {
private:
    int size;
    int x;
    int y;
    bool rotation;
public:
    constexpr Ship() = default;
    constexpr Ship(int s, int x, int y, bool r) : size(s), x(x), y(y), rotation(r) {}

    constexpr int getSize() const {
        return size;
    }
    constexpr void setSize(int v) {
        size = v;
    }
    constexpr int getX() const {
        return x;
    }
    constexpr void setX(int v) {
        x = v;
    }
    constexpr int getY() const {
        return y;
    }
    constexpr void setY(int v) {
        y = v;
    }
    constexpr bool getRotation() const {
        return rotation;
    }
    constexpr void setRotation(int v) {
        rotation = v;
    }
    ~Ship() = default;
};


class Field {
private:
    char field[12][12];
    bool checkIfCouldBePut(Ship ship) {
        const int shipX = ship.getX();
        const int shipY = ship.getY();
        const int shipSize = ship.getSize();
        if (ship.getRotation() == 0) {
            if (shipX < 1 || shipX + shipSize > 10) return false;
            for (int i = shipX - 1; i < shipX + shipSize + 1; ++i) {
                if (field[shipY][i] == '.' || field[shipY - 1][i] == '.' || field[shipY + 1][i] == '.') {
                    return false;
                }
            }
        } else {
            if (shipY < 1 || shipY + shipSize > 10) return false;
            for (int i = shipY - 1; i < shipY + shipSize + 1; ++i) {
                if (field[i][shipX] == '.' || field[i][shipX - 1] == '.' || field[i][shipX + 1] == '.') {
                    return false;
                }
            }
        }
        return true;
    }
public:
    constexpr Field() noexcept {
        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j < 12; ++j) {
                field[i][j] = '0';
            }
        }
    }
    Field& operator=(const Field& other) {
        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j < 12; ++j) {
                field[i][j] = other.getCurrentPlace(i, j);
            }
        }
        return *this;
    }
    constexpr void printField() {
        for (int i = 1; i < 11; ++i) {
            for (int j = 1; j < 11; ++j) {
                std::cout << field[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
    constexpr bool setShip(Ship ship) {
        if (!checkIfCouldBePut(ship)) {
            //std::cout << "no" << ship.getX() << ship.getY() << ' ' << ship.getSize() << '\n';
            return false;
        }
        const int shipX = ship.getX();
        const int shipY = ship.getY();
        const int shipSize = ship.getSize();
        if (ship.getRotation() == 0) {
            for (int i = shipX; i < shipX + shipSize; ++i) {
                field[shipY][i] = '.';
            }
        } else {
            for (int i = shipY; i < shipY + shipSize; ++i) {
                field[i][shipX] = '.';
            }
        }
        return true;
    }
    char getCurrentPlace(int y, int x) const {
        return field[y][x];
    }
    ~Field() = default;
};

class StupidBot {
public:
    ~StupidBot() = default;
    std::optional<Field> randomGenerator() {
        Field field;
        std::random_device rd;
        std::mt19937 gen(rd());
        bool isSet = false;
        Ship ship{};
        std::array<int, 10> ships = {0, 1, 2, 3, 1, 2, 3, 2, 3, 3};
        int countSettingAttempts = 0;
        for (const int& currentShip : ships) {
            isSet = false;
            while (!isSet) {
                ship.setSize(4 - currentShip);
                std::uniform_int_distribution<> distX(1, 7);
                std::uniform_int_distribution<> distY(1, 7);
                std::uniform_int_distribution<> dist01(0, 1);
                ship.setX(distX(gen) + currentShip);
                ship.setY(distY(gen) + currentShip);
                ship.setRotation(dist01(gen));
                isSet = field.setShip(ship);
                if (!isSet) ++countSettingAttempts;
                if (countSettingAttempts > 100) {
                    std::cout << "shit\n";
                    return std::nullopt;
                }
            }
        }
        return field;
    }

};

class MyWidget : public QWidget {
private:
    Field field;
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        painter.fillRect(0, 0, 500, 500, QBrush{"#2980b9"});
        for (int i = 1; i <= 9; ++i) {
            painter.drawLine(50 * i, 0, 50 * i, 500);
            painter.drawLine(0, 50 * i, 500, 50 * i);
        }
        for (int i = 1; i < 12; ++i) {
            for (int j = 1; j < 12; ++j) {
                if (field.getCurrentPlace(i, j) == '.') {
                    painter.fillRect(50 * (j - 1), 50 * (i - 1), 50, 50, QBrush{"#ffffff"});
                }
            }
        }
    }
public:
    MyWidget(Field f) : field(f) {}
    ~MyWidget() = default;
};

int main(int argc, char *argv[]) {
    StupidBot bot;
    auto field = bot.randomGenerator();
    while (!field.has_value()) {
        field = bot.randomGenerator();
    }
    field->printField();
    QApplication app(argc, argv);
    MyWidget widget(*field);
    widget.setFixedSize(500, 500);
    widget.setWindowTitle("Field");

    widget.show();
    return app.exec();
}