#include "mainwindow.h"
#include <QApplication>

extern evalstate Vars;  //初始化变量列表,声明为一个全局变量

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
