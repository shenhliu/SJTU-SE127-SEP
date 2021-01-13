#include "snake2node.h"

Snake2Node::Snake2Node(QWidget *parent) : QWidget(parent)//无初始位置的构造函数
{

}

Snake2Node::Snake2Node(QWidget *parent,int x,int y){//以输入x,y坐标形式的构造函数
    Snake2Node_Init(parent);
    setPos(x,y);
}

Snake2Node::Snake2Node(QWidget *parent,QPoint pos){//以Qt自带的坐标形式的构造函数
    Snake2Node_Init(parent);
    setPos(pos);
}

void Snake2Node::Snake2Node_Init(QWidget *parent){
    item = new QFrame(parent);

    item->setAutoFillBackground(true);//把蛇身体模块的颜色设置成蓝色
    QPalette pa=item->palette();
    QColor black(Qt::black);
    pa.setColor(QPalette::Background,black);
    item->setPalette(pa);

    item->resize(10,10);

    item->show();
}

Snake2Node::~Snake2Node()
{
    delete item;
}

void Snake2Node::setPos(int x,int y){//设置模块的位置
    spos.setX(x);
    spos.setY(y);
    item->move(spos);
}

void Snake2Node::setPos(QPoint pos){
    spos=pos;
    item->move(spos);
}

QPoint Snake2Node::getPos(void){//获得模块的位置
    return spos;
}
