#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include "GameWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QDialog startDialog;
    startDialog.setWindowTitle("Battleship");
    startDialog.setFixedSize(300, 150);
    
    QVBoxLayout layout(&startDialog);
    QPushButton startButton("Start");
    QPushButton exitButton("Exit");
    
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