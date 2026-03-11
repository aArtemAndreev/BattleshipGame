#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include "GameWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QDialog startDialog;
    startDialog.setWindowTitle("Морской бой");
    startDialog.setFixedSize(300, 150);
    
    QVBoxLayout layout(&startDialog);
    QPushButton startButton("Начать игру");
    QPushButton exitButton("Выход");
    
    layout.addWidget(&startButton);
    layout.addWidget(&exitButton);
    
    QObject::connect(&exitButton, &QPushButton::clicked, &startDialog, &QDialog::reject);
    QObject::connect(&startButton, &QPushButton::clicked, &startDialog, &QDialog::accept);
    
    if (startDialog.exec() == QDialog::Accepted) {
        GameWindow window;
        window.show();
        return app.exec();
    }
    return 0;
}