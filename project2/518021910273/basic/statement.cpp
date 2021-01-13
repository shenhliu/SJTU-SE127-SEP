#include "statement.h"

statement::statement()
{
    next = nullptr;
}

statement::statement(QString state,statement*n)
{
    text = state;
    next = n;
    lst = text.split(' ',QString::SkipEmptyParts);
    bool ok;
    lst[0].toInt(&ok);

    if(ok)
    {
        linenum = lst[0].toInt();   //如果是有行号的statement，那么就存在linenum里
    }
    else
    {
        linenum = 0;    //如果是直接执行的命令，那么就把行号置为0
    }
}

void statement::cover(QString ntext)
{
    text = ntext;
    lst = text.split(' ',QString::SkipEmptyParts);
    linenum = lst[0].toInt();
}

int statement::getlinenum()
{
    return linenum;
}

QString statement::gettext()
{
    return text;
}


