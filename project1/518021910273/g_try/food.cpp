#include "food.h"
#include<iostream>


food::food(QWidget *parent)//构造函数即在边框范围内生成食物
{
    int x =(qrand()%80)*10+10;
    int y = (qrand()%50)*10+10;

    ff = new foodnode(parent,x,y);

}

