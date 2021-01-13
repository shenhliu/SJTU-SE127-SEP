#ifndef SFOOD1NODE_H
#define SFOOD1NODE_H

#include<iostream>
#include <QWidget>
#include <QFrame>
#include <QPoint>
#include <QColor>
#include <QPalette>
#include <QtCore>



#include<QPushButton>

class SFood1node : public QWidget
{
    Q_OBJECT
public:
    explicit SFood1node(QWidget *parent = nullptr);
    SFood1node(QWidget *parent,int x,int y);
    SFood1node(QWidget *parent,QPoint pos);
    ~SFood1node();

    void setPos(int x,int y);
    void setPos(QPoint pos);

    QPoint getPos(void);
     QFrame *item;

     QPoint spos;



private:
    void SFood1node_Init(QWidget *parent);

private:



signals:

public slots:
};
#endif // SFOOD1NODE_H
