#include "mainwindow.h"
#include "ui_mainwindow.h"
# include"console.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("BASIC");
    this->setFixedSize(600, 900);

    Tokenizer = new tokenizer;          //初始化分割器

    console = new Console(this);       //初始化代码输入区
    console->setGeometry(0, 0, 600, 600);

    Tipconsole = new Console(this);    //初始化提示区
    Tipconsole->setGeometry(0,610,600,290);

    pro = new program();               //初始化链表
    connect(console,SIGNAL(newLineWritten(QString)),this,SLOT(newStatement(QString)));
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
        return;
    }
    if(statement == "CLEAR")
    {
        pro->clear();
        delete pro;
        pro = new program();
        console->setPlainText("");
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
        RunThePro();
        return;
    }
    if(tmplist[0] == "TRY")
    {
        Tokenizer->ToTokens(statement);
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

void MainWindow::RunThePro()
{
    statement * cur = pro->head->next;
    while(pro!=nullptr)
    {
        QList<QString> tmpstatements = cur->text.split(' ',QString::SkipEmptyParts);
        if(tmpstatements[1] == "REM")
        {
            cur = cur->next;
            continue;
        }

        if(tmpstatements[1] == "LET")
        {

        }

        cur = cur->next;
    }
}



























