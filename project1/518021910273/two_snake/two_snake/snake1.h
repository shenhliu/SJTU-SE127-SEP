#ifndef SNAKE1_H
#define SNAKE1_H


#include "SnakeNode.h"
#include <QList>
#include<QWidget>
#include<ctime>
using namespace std;

class snake1:public QWidget
{
    friend class food;
    friend class mainwindow;
    Q_OBJECT
public:
    explicit snake1(QWidget *parent = nullptr);
    ~snake1();

    void InsertHead(QWidget *parent);
    void DeleteTail();

    void eat(int dir,QWidget *parent);
    void moveto(int dir,QWidget *parent);
    bool CheckEatSelf(void);

    int GetDir();
    void SetDir(int a);

QList<SnakeNode*> body;

private:

private:
     int dir = 4;
     int predir;

signals:

public slots:

};
#endif // SNAKE1_H
