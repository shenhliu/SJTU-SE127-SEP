#ifndef SFOOD2NODE_H
#define SFOOD2NODE_H


#include <QWidget>
#include <QFrame>
#include <QPoint>
#include <QColor>
#include <QPalette>
#include <QtCore>


#include<QPushButton>

class SFood2node : public QWidget
{
    Q_OBJECT
public:
    explicit SFood2node(QWidget *parent = nullptr);
    SFood2node(QWidget *parent,int x,int y);
    SFood2node(QWidget *parent,QPoint pos);
    ~SFood2node();

    void setPos(int x,int y);
    void setPos(QPoint pos);

    QPoint getPos(void);
     QFrame *item;



private:
    void SFood2node_Init(QWidget *parent);

private:
    QPoint spos;


signals:

public slots:
};

#endif // SFOOD2NODE_H
