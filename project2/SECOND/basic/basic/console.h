#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextEdit>
#include <QWidget>
#include <QObject>
#include <iostream>
#include <QDebug>
#include <string>
using namespace std;

class Console : public QTextEdit
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);

    string nowword;

signals:
    void newLineWritten(QString newline);

public slots:
    void clear();
    void write(QString msg);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // CONSOLE_H

