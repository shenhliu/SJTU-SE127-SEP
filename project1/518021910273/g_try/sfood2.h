#ifndef SFOOD2_H
#define SFOOD2_H
#include"snakenode.h"
#include"snake.h"
#include"foodnode.h"
#include"sfood2node.h"

class SFood2:public SnakeNode{

public:
    SFood2(QWidget *parent);
    SFood2node*ff = nullptr;
};

#endif // SFOOD2_H
