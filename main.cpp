#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])    //主函数
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
