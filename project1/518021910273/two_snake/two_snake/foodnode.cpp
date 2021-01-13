#include "foodnode.h"


foodnode::foodnode(QWidget *parent) : QWidget(parent)
{

}

foodnode::foodnode(QWidget *parent,int x,int y){
    foodnode_Init(parent);
    setPos(x,y);
}

foodnode::foodnode(QWidget *parent,QPoint pos){
    foodnode_Init(parent);
    setPos(pos);
}

void foodnode::foodnode_Init(QWidget *parent){
    item = new QFrame(parent);

    item->setAutoFillBackground(true);
    QPalette pa=item->palette();
    QColor red(Qt::red);
    pa.setColor(QPalette::Background,red);
    item->setPalette(pa);

    item->resize(10,10);

    item->show();
}

foodnode::~foodnode()
{
    delete item;
}

void foodnode::setPos(int x,int y){
    spos.setX(x);
    spos.setY(y);
    item->move(spos);
}

void foodnode::setPos(QPoint pos){
    spos=pos;
    item->move(spos);
}

QPoint foodnode::getPos(void){
    return spos;
}
