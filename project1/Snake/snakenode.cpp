#include "snakenode.h"

SnakeNode::SnakeNode(QWidget *parent) : QWidget(parent)
{

}

SnakeNode::SnakeNode(QWidget *parent,int x,int y){
    SnakeNode_Init(parent);
    setPos(x,y);
}

SnakeNode::SnakeNode(QWidget *parent,QPoint pos){
    SnakeNode_Init(parent);
    setPos(pos);
}

void SnakeNode::SnakeNode_Init(QWidget *parent){
    item = new QFrame(parent);

    item->setAutoFillBackground(true);
    QPalette pa=item->palette();
    QColor red(Qt::red);
    pa.setColor(QPalette::Background,red);
    item->setPalette(pa);

    item->resize(10,10);

    item->show();

    next=NULL;
}

SnakeNode::~SnakeNode()
{
    delete item;
}

void SnakeNode::setPos(int x,int y){
    spos.setX(x);
    spos.setY(y);
    item->move(spos);
}

void SnakeNode::setPos(QPoint pos){
    spos=pos;
    item->move(spos);
}

QPoint SnakeNode::getPos(void){
    return spos;
}
