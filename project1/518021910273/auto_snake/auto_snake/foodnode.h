#ifndef FOODNODE_H
#define FOODNODE_H


#include <QWidget>
#include <QFrame>
#include <QPoint>
#include <QColor>
#include <QPalette>
#include <QtCore>


#include<QPushButton>

class foodnode : public QWidget
{
    Q_OBJECT
public:
    explicit foodnode(QWidget *parent = nullptr);
    foodnode(QWidget *parent,int x,int y);
    foodnode(QWidget *parent,QPoint pos);
    ~foodnode();

    void setPos(int x,int y);
    void setPos(QPoint pos);

    QPoint getPos(void);
     QFrame *item;



private:
    void foodnode_Init(QWidget *parent);

private:
    QPoint spos;


signals:

public slots:
};

#endif // FOODNODE_H
