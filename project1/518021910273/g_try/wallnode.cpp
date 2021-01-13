//这个类和snakenode类基本相同，只是换了颜色


#include "wallnode.h"

wallnode::wallnode(QWidget *parent) : QWidget(parent)
{

}

wallnode::wallnode(QWidget *parent,int x,int y){
    wallnode_Init(parent);
    setPos(x,y);
}

wallnode::wallnode(QWidget *parent,QPoint pos){
    wallnode_Init(parent);
    setPos(pos);
}

void wallnode::wallnode_Init(QWidget *parent){
    item = new QFrame(parent);

    item->setAutoFillBackground(true);
    QPalette pa=item->palette();
    QColor green(Qt::green);
    pa.setColor(QPalette::Background,green);
    item->setPalette(pa);

    item->resize(10,10);

    item->show();
}

wallnode::~wallnode()
{
    delete item;
}

void wallnode::setPos(int x,int y){
    spos.setX(x);
    spos.setY(y);
    item->move(spos);
}

void wallnode::setPos(QPoint pos){
    spos=pos;
    item->move(spos);
}

QPoint wallnode::getPos(void){
    return spos;
}
