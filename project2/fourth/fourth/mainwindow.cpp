#include "mainwindow.h"
#include "ui_mainwindow.h"
# include"console.h"
#include <QLabel>
#include <QApplication>
#include<QMap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("BASIC");
    this->setFixedSize(900, 900);

    Parser = new parser;   //初始化parser

    Tokenizer = new tokenizer;          //初始化分割器

    console = new Console(this);       //初始化代码输入区
    console->setGeometry(0, 0, 600, 600);

    markconsole = new Console(this);
    markconsole->setGeometry(0,600,20,300);

    inputconsole = new Console(this);    //初始化变量赋值区
    inputconsole->setGeometry(20,600,600,300);

    Tipconsole = new Console(this);         //初始化报错和帮助区
    Tipconsole->setGeometry(600,450,300,450);

    varmap = new Console(this);            //初始化显示变量的区域
    varmap->setGeometry(600,0,300,450);

    pro = new program();               //初始化链表
    connect(console,SIGNAL(newLineWritten(QString)),this,SLOT(newStatement(QString)));
    connect(inputconsole,SIGNAL(newLineWritten(QString)),this,SLOT(newInput(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newStatement(QString statement)
{
    QList<QString> tmplist = statement.split(' ',QString::SkipEmptyParts);
    bool ok;
    if(statement == nullptr) return;
    if(statement ==' ') return;
    if(statement == "HELP")
    {
        Tipconsole->write("Fly,bitch!");
        Tipconsole->write("必须手动输入，复制粘贴的代码不认！会出错");
        return;
    }
    if(statement == "CLEAR")
    {
        pro->clear();
        delete pro;
        pro = new program();
        console->setPlainText("");
        Tipconsole->setPlainText("");
        markconsole->setPlainText("");
        return;
    }
    if(statement == "QUIT")
    {
        this->close();
    }
    if(statement =="LIST")
    {
        traverse();
        return;
    }
    if(statement == "RUN")
    {
        RunThePro(Vars,pro->head->next);
        return;
    }
    
    
    
    
    if(tmplist[0]!=nullptr)
    {
        tmplist[0].toInt(&ok);
        if(ok)
        {
            int tmplinenum = tmplist[0].toInt();
            pro->insert(tmplinenum,statement);
        }
    }

}

void MainWindow::traverse()          //用来遍历所有的statement，即完成“LIST”操作
{
    statement *p = pro->head->next;
    while(p!=nullptr)
    {
        console->write(p->text);
        p = p->next;
    }
}



void MainWindow::RunThePro(evalstate &Vars,statement*runpos)
{
    statement * cur = runpos;
    while(cur!=nullptr)
    {

        QList<QString> tmpstatements = cur->text.split(' ',QString::SkipEmptyParts);
        if(tmpstatements[1] == "END")
        {
            break;
        }

        if(tmpstatements[1] == "REM")
        {
            cur = cur->next;
            continue;
        }

        if(tmpstatements[1] == "LET")
        {
            QString sta = "";
            for(int i = 2;i < tmpstatements.length();++i)   //这个循环是为了去掉"LET" 获得一个纯正的expression
            {
                sta += tmpstatements[i];
            }

            QList<QString>tokens;
            tokens.clear();
            tokens = Tokenizer->ToTokens(sta);
            Expression*val = Parser->ToTree(tokens);                   //化成表达树
            val->eval(Vars);                               //进行求值
//            QString ceshi = QString(num);
//            Tipconsole->write(ceshi);
        }

        if(tmpstatements[1] == "PRINT")
        {
            QString sta = "";
            for(int i = 2;i < tmpstatements.length();++i)   //这个循环是为了去掉"PRINT" 获得一个纯正的expression
            {
                sta += tmpstatements[i];
            }
            QList<QString>tokens;
            tokens.clear();
            tokens = Tokenizer->ToTokens(sta);
            Expression*val = Parser->ToTree(tokens);                   //化成表达树
            int num = val->eval(Vars);                               //进行求值
            QString tmp = QString::number(num,10);
            console->write(tmp);
        }

        if(tmpstatements[1] =="INPUT")
        {
            markconsole->write("?");
            inputvar = tmpstatements[2];
            inputpos = cur;
            return;
        }

        if(tmpstatements[1] == "IF")
        {
            QString sta = "";
            for(int i = 2;i < tmpstatements.length();++i)   //找到IF和THEN之间的判断条件
            {
                if(tmpstatements[i] == "THEN")
                    break;
                else
                    sta += tmpstatements[i];
            }
            bool ok = IfCondition(sta);
            if(ok)           //如果if条件成立，就去找then
            {
                int j = 0;
                for(j = 0;j<tmpstatements.length();++j)
                {
                    if(tmpstatements[j] == "THEN")
                        break;
                }
                if(j == tmpstatements.length()-1)
                {
                    //报错，没输行号
                }
                int desnum = tmpstatements[j+1].toInt();
                statement*tmp = pro->head->next;
                while (tmp!=nullptr)
                {
                    QList<QString> tmpst = tmp->text.split(' ',QString::SkipEmptyParts);
                    if(tmpst[0].toInt() == desnum)
                    {
                        break;
                    }
                    tmp = tmp->next;
                }
                if(tmp == nullptr)
                {
                    //报错，没有找到这一行
                }
                cur = tmp;
                continue;
            }
        }

        if(tmpstatements[1] == "GOTO")
        {
            bool ok;
            tmpstatements[2].toInt(&ok);
            if(ok)
            {
                int desnum = tmpstatements[2].toInt();       //要跳转的行号
                statement*tmp = pro->head->next;
                while (tmp!=nullptr)
                {                  
                    QList<QString> tmpst = tmp->text.split(' ',QString::SkipEmptyParts);
                    if(tmpst[0].toInt() == desnum)
                    {
                        break;
                    }
                    tmp = tmp->next;
                }
                if(tmp == nullptr)
                {
                    //报错，没有找到这一行
                }
                cur = tmp;
                continue;
            }
            else {
                //写报错条件,没有写正确的行号
            }
        }

        cur = cur->next;
    }
    varmap->setText(Vars.Tranvrese());
}

void MainWindow::newInput(QString inp)    //inp 应该是 " ? "+输入的变量名
{
    inp.remove(" ");
    int num = inp.toInt();
    Vars.setValue(inputvar,num);
    if(inputpos->next!=nullptr)
        RunThePro(Vars,inputpos->next);
}

bool MainWindow::IfCondition(QString str)
{
    if(str.contains("="))
    {
        QList<QString> ifstrs = str.split('=',QString::SkipEmptyParts);

        QList<QString>tokensleft;
        tokensleft.clear();
        tokensleft = Tokenizer->ToTokens(ifstrs[0]);
        Expression*valleft = Parser->ToTree(tokensleft);                   //化成表达树
        int numleft = valleft->eval(Vars);                               //进行求值

        QList<QString>tokensright;
        tokensright.clear();
        tokensright = Tokenizer->ToTokens(ifstrs[1]);
        Expression*valright = Parser->ToTree(tokensright);                   //化成表达树
        int numright = valright->eval(Vars);                               //进行求值

        if(numleft == numright)
        {
            return true;
        }
        else {
            return false;
        }
    }
    else if (str.contains(">")) {
        QList<QString> ifstrs = str.split('>',QString::SkipEmptyParts);
        QList<QString>tokensleft;
        tokensleft.clear();
        tokensleft = Tokenizer->ToTokens(ifstrs[0]);
        Expression*valleft = Parser->ToTree(tokensleft);                   //化成表达树
        int numleft = valleft->eval(Vars);                               //进行求值

        QList<QString>tokensright;
        tokensright.clear();
        tokensright = Tokenizer->ToTokens(ifstrs[1]);
        Expression*valright = Parser->ToTree(tokensright);                   //化成表达树
        int numright = valright->eval(Vars);                               //进行求值

        if(numleft > numright)
        {
            return true;
        }
        else {
            return false;
        }
    }
    else if (str.contains("<")) {
        QList<QString> ifstrs = str.split('<',QString::SkipEmptyParts);
        QList<QString>tokensleft;
        tokensleft.clear();
        tokensleft = Tokenizer->ToTokens(ifstrs[0]);
        Expression*valleft = Parser->ToTree(tokensleft);                   //化成表达树
        int numleft = valleft->eval(Vars);                               //进行求值

        QList<QString>tokensright;
        tokensright.clear();
        tokensright = Tokenizer->ToTokens(ifstrs[1]);
        Expression*valright = Parser->ToTree(tokensright);                   //化成表达树
        int numright = valright->eval(Vars);                               //进行求值

        if(numleft < numright)
        {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        QList<QString> ifstrs;            //这里要记得写报错条件
    }
    return false;
}
























