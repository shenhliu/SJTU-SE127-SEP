#ifndef WALL_H
#define WALL_H
#include "wallnode.h"
#include <QList>
#include<QWidget>

class wall
{
public:
    wall(QWidget*parent = nullptr);
    QList<wallnode*> ww;
    wallnode *wn;

};

#endif // WALL_H
