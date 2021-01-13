#include "BoggleWindow.h"
#include "lexicon.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BoggleWindow w;
    w.show();

    return a.exec();
}
