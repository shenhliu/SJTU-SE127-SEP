#include "program.h"

program::program()
{
    head = new statement;
    prolength = 0;
}

void program::clean()
{
    statement *p = head->next;
    statement *q;
    head->next = nullptr;
    while(p!=nullptr)
    {
        q = p->next;
        delete p;
        p = q;
    }
    prolength = 0;
}

int program::getlength()
{
    return prolength;
}

statement* program::move(int lnum)
{
    statement*p = head->next;
    statement*q = head;
    if(head->next!=nullptr)
    {
        while((p->linenum < lnum ||lnum == 0)&&(p->next!=nullptr))
        {
            p = p->next;
            q = q->next;
        }

        if(p->linenum == lnum)
        {
            state = 0;      //0为要替换，1为要插入
            return p;
        }
        else
        {
            if(p->next == nullptr)
            {
                state = 1;
                return p;
            }
            else {
                state = 1;
                return q;
            }
        }
    }
    else {
        state = 1;
    return head;
    }
}

void program::insert(int lnum,QString newtext)
{
        move(lnum);
        if(state == 0)      //需要替换
        {
            statement *tmp = move(lnum);
            tmp->text = newtext;
            QList<QString> tmplist = newtext.split(' ',QString::SkipEmptyParts);
            int tmplinenum = tmplist[0].toInt();
            tmp->linenum = tmplinenum;
        }
        else          //需要加新命令
        {
            statement *tmp = move(lnum);
            statement *tmpq = tmp;
            if(tmp->next == nullptr)             //如果是在尾部添加statement
            {
               tmp->next = new statement(newtext,nullptr);
               prolength++;
            }
            else{                                //如果是在中间添加
                tmp->next = new statement(newtext,tmpq->next);
                prolength++;
            }
       }
}

void program::clear()
{
    statement *p = head->next;
    statement *q = head;
    while(p!=nullptr)
    {
        q = p;
        delete p;
        p = q;
        p = p->next;
    }
}

void program::del(int num)
{
    statement *p = head->next;
    statement *q = head;
    while(p!=nullptr)
    {
        if(p->linenum == num)
        {
            q->next = p->next;
            delete p;
        }
        p = p->next;
        q = q->next;
    }
}

statement* program::findline(int lnum)
{
    statement*tmp = head->next;
    while(tmp!=nullptr)
    {
        if(tmp->linenum == lnum)
            return tmp;

        tmp = tmp->next;
    }
    return nullptr;
}



















