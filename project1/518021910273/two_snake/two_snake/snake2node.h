#ifndef SNAKE2NODE_H
#define SNAKE2NODE_H

#include <QWidget>
#include <QFrame>
#include <QPoint>
#include <QColor>
#include <QPalette>
#include <QtCore>


#include<QPushButton>

class Snake2Node : public QWidget
{
    Q_OBJECT
public:
    explicit Snake2Node(QWidget *parent = nullptr);
    Snake2Node(QWidget *parent,int x,int y);
    Snake2Node(QWidget *parent,QPoint pos);
    ~Snake2Node();

    void setPos(int x,int y);
    void setPos(QPoint pos);

    QPoint getPos(void);
     QFrame *item;



private:
    void Snake2Node_Init(QWidget *parent);

private:
    QPoint spos;


signals:

public slots:
};

#endif // SNAKE2NODE_H
