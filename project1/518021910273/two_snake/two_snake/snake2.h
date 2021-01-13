#ifndef SNAKE2_H
#define SNAKE2_H


#include "Snake2Node.h"
#include <QList>
#include<QWidget>
#include<ctime>
using namespace std;

class snake2:public QWidget
{
    friend class food;
    friend class mainwindow;
    Q_OBJECT
public:
    explicit snake2(QWidget *parent = nullptr);
    ~snake2();

    void InsertHead(QWidget *parent);
    void DeleteTail();

    void eat(int dir,QWidget *parent);
    void moveto(int dir,QWidget *parent);
    bool CheckEatSelf(void);

    int GetDir();
    void SetDir(int a);

QList<Snake2Node*> body;

private:

private:
     int dir = 3;
     int predir;

signals:

public slots:

};
#endif // SNAKE2_H
