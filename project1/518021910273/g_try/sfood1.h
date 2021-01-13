#ifndef SFOOD1_H
#define SFOOD1_H
#include"snakenode.h"
#include"snake.h"
#include"foodnode.h"
#include"sfood1node.h"

class SFood1:public SnakeNode{

public:
    SFood1(QWidget *parent);
    SFood1node*ff = nullptr;
};






#endif // SFOOD1_H
