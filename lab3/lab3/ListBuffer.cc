#include <fstream>
#include <iostream>
#include "ListBuffer.h"

void ListBuffer::insertLine(int line_idx, const string &text)
{

    if (line_idx > 32767 || line_idx < 0)
    {
        throw "out of scale";
    }
    listnode *p = head;
    listnode *lead = p->next;

    if (lead == NULL)
    {
        listnode *q = new listnode;
        q->linenum = line_idx;
        q->line = text;
        head->next = q;
    }
    else
    {
        while ((lead != NULL) && (line_idx > lead->linenum))
        {
            p = p->next;
            lead = p->next;
        }
        if (lead == NULL)
        {
            listnode *newnode = new listnode;
            newnode->linenum = line_idx;
            newnode->line = text;
            p->next = newnode;
        }
        else
        {
            if (lead->linenum == line_idx)
            {
                lead->line = text;
            }
            else
            {
                listnode *newnode = new listnode;
                newnode->linenum = line_idx;
                newnode->line = text;
                newnode->next = lead;
                p->next = newnode;
            }
        }
    }
}

void ListBuffer::deleteLine(int line_idx)
{
    listnode *p = head;
    listnode *q = p->next;
    while (q != NULL)
    {
        if (q->linenum == line_idx)
        {
            p->next = q->next;
            delete q;
            --currentlength;
            break;
        }
        p = p->next;
        q = p->next;
    }
}

void ListBuffer::showLines()
{
    listnode *m = head->next;
    while (m != NULL)
    {
        cout << m->linenum << '\t' << m->line << endl;
        m = m->next;
    }
}
void ListBuffer::writeToFile(const string &filename) const
{
    listnode *p = head->next;
    ofstream out("Newfile");
    while (p != NULL)
    {
        out << p->linenum << p->line << endl;
        p = p->next;
    }
}
//TODO: your code here
//implement the functions in ListBuffer
