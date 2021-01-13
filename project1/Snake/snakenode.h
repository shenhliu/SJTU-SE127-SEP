#ifndef SNAKENODE_H
#define SNAKENODE_H

#include <QWidget>
#include <QFrame>
#include <QPoint>
#include <QColor>
#include <QPalette>
#include <QtCore>

class SnakeNode : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeNode(QWidget *parent = 0);
    SnakeNode(QWidget *parent,int x,int y);
    SnakeNode(QWidget *parent,QPoint pos);
    ~SnakeNode();

    void setPos(int x,int y);
    void setPos(QPoint pos);

    QPoint getPos(void);

public:
    SnakeNode *next;

private:
    void SnakeNode_Init(QWidget *parent);

private:
    QPoint spos;
    QFrame *item;

signals:

public slots:
};

#endif // SNAKENODE_H
