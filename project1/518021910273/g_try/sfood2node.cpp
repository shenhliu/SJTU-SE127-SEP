#include "sfood2node.h"


SFood2node::SFood2node(QWidget *parent) : QWidget(parent)
{

}

SFood2node::SFood2node(QWidget *parent,int x,int y){
    SFood2node_Init(parent);
    setPos(x,y);
}

SFood2node::SFood2node(QWidget *parent,QPoint pos){
    SFood2node_Init(parent);
    setPos(pos);
}

void SFood2node::SFood2node_Init(QWidget *parent){
    item = new QFrame(parent);

    item->setAutoFillBackground(true);
    QPalette pa=item->palette();
    QColor yellow(Qt::yellow);
    pa.setColor(QPalette::Background,yellow);
    item->setPalette(pa);

    item->resize(10,10);

    item->show();
}

SFood2node::~SFood2node()
{
    delete item;
}

void SFood2node::setPos(int x,int y){
    spos.setX(x);
    spos.setY(y);
    item->move(spos);
}

void SFood2node::setPos(QPoint pos){
    spos=pos;
    item->move(spos);
}

QPoint SFood2node::getPos(void){
    return spos;
}
