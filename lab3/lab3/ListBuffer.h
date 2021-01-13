#pragma once

#include <string>

using namespace std;

class ListBuffer
{
  private:
    struct listnode
    {
        int linenum;
        string line;
        listnode *next = NULL;

        listnode()
        {
            next = NULL;
        }
        listnode(int num, string li, listnode *nex = NULL)
        {
            linenum = num;
            line = li;
            next = nex;
        }
    };

    listnode *head;
    int currentlength = 0;
    //TODO: add a List here for storing the input lines

  public:
    ListBuffer()
    {
        head = new listnode;
    }
    ~ListBuffer()
    {
        listnode *p = head->next;
        while (p != NULL)
        {
            listnode *q = p->next;
            delete p;
            p = q;
        }
    }

    void writeToFile(const string &filename) const;

    void showLines();
    void deleteLine(int line_idx);
    void insertLine(int line_idx, const string &text);
};
