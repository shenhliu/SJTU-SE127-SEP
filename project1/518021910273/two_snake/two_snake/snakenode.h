#ifndef SNAKENODE_H
#define SNAKENODE_H


#include <QWidget>
#include <QFrame>
#include <QPoint>
#include <QColor>
#include <QPalette>
#include <QtCore>


#include<QPushButton>

class SnakeNode : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeNode(QWidget *parent = nullptr);
    SnakeNode(QWidget *parent,int x,int y);
    SnakeNode(QWidget *parent,QPoint pos);
    ~SnakeNode();

    void setPos(int x,int y);
    void setPos(QPoint pos);

    QPoint getPos(void);
     QFrame *item;



private:
    void SnakeNode_Init(QWidget *parent);

private:
    QPoint spos;


signals:

public slots:
};

#endif // SNAKENODE_H
