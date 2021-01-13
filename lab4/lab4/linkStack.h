#include <iostream>
#include "termio.h"
using namespace std;

struct node
{
    int s;
    int e;
    node *next;
    node(int x, int y, node *N = NULL)
    {
        s = x;
        e = y;
        next = N;
    }
    node() : next(NULL) {}

    ~node() {}
};
class linkStack
{

  public:
    node *top_p;

    linkStack();
    ~linkStack();
    bool isEmpty();
    void push(int x, int y);
    node *pop();
};

linkStack::linkStack()
{
    top_p = NULL;
}
linkStack::~linkStack()
{
    node *tmp;
    while (top_p != NULL)
    {
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}

bool linkStack::isEmpty()
{
    return top_p == NULL;
}
void linkStack::push(int x, int y)
{
    top_p = new node(x, y, top_p);
}
node *linkStack::pop()
{
    node *tmp = top_p;
    top_p = top_p->next;
    return tmp;
}
