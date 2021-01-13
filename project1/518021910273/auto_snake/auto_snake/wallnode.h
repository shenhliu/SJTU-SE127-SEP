#ifndef SNAKENODE_H
#define SNAKENODE_H

#include <QWidget>
#include <QFrame>
#include <QPoint>
#include <QColor>
#include <QPalette>
#include <QtCore>


#include<QPushButton>

class wallnode : public QWidget
{
    Q_OBJECT
public:
    explicit wallnode(QWidget *parent = nullptr);
    wallnode(QWidget *parent,int x,int y);
    wallnode(QWidget *parent,QPoint pos);
    ~wallnode();

    void setPos(int x,int y);
    void setPos(QPoint pos);

    QPoint getPos(void);
     QFrame *item;



private:
    void wallnode_Init(QWidget *parent);

private:
    QPoint spos;


signals:

public slots:
};

#endif // SNAKENODE_H
