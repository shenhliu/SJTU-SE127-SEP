#include "sfood2.h"

SFood2::SFood2(QWidget *parent)//构造函数即在边框范围内生成食物
{
    int x =(qrand()%80)*10+10;
    int y = (qrand()%50)*10+10;

    ff = new SFood2node(parent,x,y);

}
