#include "sfood1node.h"

SFood1node::SFood1node(QWidget *parent) : QWidget(parent)
{

}

SFood1node::SFood1node(QWidget *parent,int x,int y){
    SFood1node_Init(parent);
    setPos(x,y);
}

SFood1node::SFood1node(QWidget *parent,QPoint pos){
    SFood1node_Init(parent);
    setPos(pos);
}

void SFood1node::SFood1node_Init(QWidget *parent){
    item = new QFrame(parent);

    item->setAutoFillBackground(true);
    QPalette pa=item->palette();
    QColor black(Qt::black);
    pa.setColor(QPalette::Background,black);
    item->setPalette(pa);

    item->resize(10,10);

    item->show();
}

SFood1node::~SFood1node()
{
    delete item;
}

void SFood1node::setPos(int x,int y){
    spos.setX(x);
    spos.setY(y);
    item->move(spos);
}

void SFood1node::setPos(QPoint pos){
    spos=pos;
    item->move(spos);
}

QPoint SFood1node::getPos(void){
    return spos;
}
