#ifndef FOOD_H
#define FOOD
#include"snakenode.h"
#include"snake.h"
#include"foodnode.h"

class food:public SnakeNode{

public:
    food(QWidget *parent);
    foodnode*ff;
    int x = 100;
    int y = 400;
};

#endif // FOOD_H
