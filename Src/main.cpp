#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QDesktopWidget *desk = QApplication::desktop();

    MainWindow *chessui =  new MainWindow();
    chessui->setAttribute(Qt::WA_DeleteOnClose);
    chessui->move( ( desk->width() - chessui->width() ) / 2,
                   ( desk->height() - chessui->height() ) / 2  );
    chessui->show();
    return  app.exec();
}

