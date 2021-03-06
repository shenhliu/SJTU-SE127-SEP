# include"console.h"
# include"program.h"
# include"evalstate.h"
# include"tokenizer.h"
# include"parser.h"
# include"statement.h"
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
    void RunThePro(evalstate &var,statement*cur);
    bool IsConstantexp(QString);
    bool IsIdentifierexp(QString);
    bool IsCompoundexp(QString);
    evalstate Vars;   //初始化变量列表
    bool IfCondition(QString str);
    void ConditionRun(evalstate &var, statement*cur , statement*breakpoint);
    void tranverseBp();

public slots:
    void newStatement(QString);
    void newInput(QString);

private:
    Ui::MainWindow *ui;
    Console*console;
    program*pro;
    Console*Tipconsole;
    Console*markconsole;   //这块地方只是为了在INPUT的时候打出？
    Console*inputconsole;   //这块地方为了进行输入
    Console*varmap;              //这块地方为了显示已经定义的变量
    tokenizer * Tokenizer;
    parser *Parser;
    statement*inputpos;            //需要input的位置
    QString inputvar;//存储INPUT的变量名
    bool Ifinput = false;//监视是否进行了INPUT操作
    statement*findpointer;     //这个指针是寻找特定的statemen时用的
    statement*findpointer2;
    program*breakpoints; //这个program用来存储断点

    statement* curbpoint;    //记录现在的断点位置
    bool ifdebug = false;
    int circletimes = 0;        //防止陷入死循环
};

#endif // MAINWINDOW_H
