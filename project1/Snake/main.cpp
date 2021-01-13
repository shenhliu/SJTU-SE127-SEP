#include "snakemainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnakeMainWindow w;
    w.show();

    return a.exec();
}
