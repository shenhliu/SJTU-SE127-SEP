#include "snake2.h"
#include"food.h"
#include<iostream>


snake2::snake2(QWidget*parent):QWidget (parent)
{
    //srand(static_cast<unsigned int>(time(nullptr)));
    Snake2Node *a = new Snake2Node(this,600,400);   //构造出最开始蛇的身体，开始的长度为两个模块
    Snake2Node *b = new Snake2Node(this,600,410);
    body.push_back(a);
    body.push_back(b);
}

snake2::~snake2()
{

}

void snake2::InsertHead(QWidget *parent)//该函数控制蛇的头前进
{
    Snake2Node *head = new Snake2Node(parent,body[0]->getPos());
    body.prepend(head);
}

void snake2::DeleteTail()//该函数控制蛇的尾巴缩进
{
   Snake2Node*tmp = body.last();
   body.pop_back();
   delete tmp;
}

void snake2::moveto(int dir,QWidget *parent){//该函数控制蛇的移动，通过将蛇的头向dir方向移动，同时缩进蛇的尾巴位置的模块，进而实现蛇的移动
    int x,y;
    QPoint pos=body[0]->getPos();
    x=pos.x();
    y=pos.y();

    InsertHead(parent);

    switch(dir){//获取当前蛇的移动方向，从而改变蛇的位置
    case 1:
        y-=10;
        break;
    case 2:
        y+=10;
        break;
    case 3:
        x-=10;
        break;
    case 4:
        x+=10;
        break;

    }

    body[0]->setPos(x,y);



    DeleteTail();

}

void snake2::eat(int dir,QWidget *parent){//通过只添头不去尾的方式实现
    int x,y;
    QPoint pos=body[0]->getPos();
    x=pos.x();
    y=pos.y();

    InsertHead(parent);

    switch(dir){
    case 1:
        y+=10;
        break;
    case 2:
        y-=10;
        break;
    case 3:
        x-=10;
        break;
    case 4:
        x+=10;
        break;

    }

    body[0]->setPos(x,y);
}

bool snake2::CheckEatSelf()//检查是否咬到自己，通过比对蛇头部的位置和其余节点的位置来实现
{
    for(int i = 1;i<body.size();++i)
    {
        if(body[0]->getPos() == body[i]->getPos())
        {
            return 1;
        }
    }
    return 0;
}



int snake2::GetDir()//获得当前蛇的前进方向
{
    return dir;
}

void snake2::SetDir(int a)//改变当前蛇的前进方向
{
    this->dir = a;
}

