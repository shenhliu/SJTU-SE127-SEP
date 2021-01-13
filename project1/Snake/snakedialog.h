#ifndef SNAKEDIALOG_H
#define SNAKEDIALOG_H

#include <QWidget>
#include "snakenode.h"

class SnakeDialog : public QWidget
{
    Q_OBJECT
public:
    explicit SnakeDialog(QWidget *parent = 0);
    ~SnakeDialog();

    void InsertHead(QWidget *parent);
    void DeleteTail();

    void eat(int dir,QWidget *parent);
    void move(int dir,QWidget *parent);
    unsigned char Check(void);

public:
    SnakeNode *shead;

private:

private:

signals:

public slots:
};

#endif // SNAKEDIALOG_H
