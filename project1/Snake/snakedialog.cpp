#include "snakedialog.h"

SnakeDialog::SnakeDialog(QWidget *parent) : QWidget(parent)
{
    shead = new SnakeNode(parent,100,100);
}

SnakeDialog::~SnakeDialog()
{
    delete shead;
}

void SnakeDialog::InsertHead(QWidget *parent){

    SnakeNode *node=new SnakeNode(parent,shead->getPos());

    node->next = shead->next;
    shead->next = node;

}

void SnakeDialog::DeleteTail(){
    SnakeNode *first,*mid,*last;

    mid = shead;
    first=mid;
    last = shead->next;
    if(last==NULL){
        return ;
    }
    while(last != NULL){
        first=mid;
        mid=last;

        last=last->next;
    }

    first->next = NULL;
    delete mid;

}

void SnakeDialog::move(int dir,QWidget *parent){
    int x,y;
    QPoint pos=shead->getPos();
    x=pos.x();
    y=pos.y();

    InsertHead(parent);

    switch(dir){
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

    shead->setPos(x,y);

    DeleteTail();

}

void SnakeDialog::eat(int dir,QWidget *parent){
    int x,y;
    QPoint pos=shead->getPos();
    x=pos.x();
    y=pos.y();

    InsertHead(parent);

    switch(dir){
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

    shead->setPos(x,y);

}

unsigned char SnakeDialog::Check(){
    SnakeNode *first,*mid,*last;

    mid=shead;
    first=mid;
    last=shead->next;
    while(last!=NULL){
        if(last->getPos() == shead->getPos())
            return 0;
        first=mid;
        mid=last;
        last=last->next;
    }

    return 1;
}








