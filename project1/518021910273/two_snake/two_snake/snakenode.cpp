#include "snakenode.h"

SnakeNode::SnakeNode(QWidget *parent) : QWidget(parent)//无初始位置的构造函数
{

}

SnakeNode::SnakeNode(QWidget *parent,int x,int y){//以输入x,y坐标形式的构造函数
    SnakeNode_Init(parent);
    setPos(x,y);
}

SnakeNode::SnakeNode(QWidget *parent,QPoint pos){//以Qt自带的坐标形式的构造函数
    SnakeNode_Init(parent);
    setPos(pos);
}

void SnakeNode::SnakeNode_Init(QWidget *parent){
    item = new QFrame(parent);

    item->setAutoFillBackground(true);//把蛇身体模块的颜色设置成蓝色
    QPalette pa=item->palette();
    QColor blue(Qt::blue);
    pa.setColor(QPalette::Background,blue);
    item->setPalette(pa);

    item->resize(10,10);

    item->show();
}

SnakeNode::~SnakeNode()
{
    delete item;
}

void SnakeNode::setPos(int x,int y){//设置模块的位置
    spos.setX(x);
    spos.setY(y);
    item->move(spos);
}

void SnakeNode::setPos(QPoint pos){
    spos=pos;
    item->move(spos);
}

QPoint SnakeNode::getPos(void){//获得模块的位置
    return spos;
}
