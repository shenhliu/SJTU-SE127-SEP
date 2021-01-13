#ifndef SNAKE_H
#define SNAKE_H
#include "SnakeNode.h"
#include <QList>
#include<QWidget>
#include<ctime>
using namespace std;

class snake:public QWidget
{
    friend class food;
    friend class mainwindow;
    Q_OBJECT
public:
    explicit snake(QWidget *parent = nullptr);
    ~snake();

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

#endif // SNAKE_H
