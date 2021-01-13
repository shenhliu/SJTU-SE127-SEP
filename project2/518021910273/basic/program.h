#ifndef PROGRAM_H
#define PROGRAM_H
#include "statement.h"
#include<QList>

class program
{
    friend class MainWindow;
public:
    program();
    void clean();
    int getlength();
    statement*move(int lnum) ; //找到插入statement或者更改statement的位置
    void insert(int lnum,QString newtext);
    QString visit(int lnum);
    void clear();
    void del(int lnum);
    statement* findline(int lnum);

private:
    int prolength = 0;
    statement *head;
    bool state = 1; //显示move到的位置是需要替换还是添加新的statement，0为替换，1为添加
};

#endif // PROGRAM_H
