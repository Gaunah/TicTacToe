#include "mainwindow.h"
#include "tictactoewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();

    return a.exec();
}
