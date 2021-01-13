#include "wall.h"

wall::wall(QWidget *parent)//在范围内生成30个墙的模块
{
    int x ;
    x = (qrand()%80)*10+10;
    int y ;
    y = (qrand()%50)*10+10;

    for(int i = 0;i<=30;i++)
    {
        x = (qrand()%80)*10+10;
        y = (qrand()%50)*10+10;
        wn = new wallnode(parent,x,y);
        ww.push_back(wn);
    }
}
