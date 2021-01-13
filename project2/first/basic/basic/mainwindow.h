# include"console.h"
# include"program.h"
# include"evalstate.h"
# include"tokenizer.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void traverse();
    void RunThePro();

public slots:
    void newStatement(QString);

private:
    Ui::MainWindow *ui;
    Console*console;
    program*pro;
    Console*Tipconsole;
    tokenizer * Tokenizer;
};

#endif // MAINWINDOW_H
