#include "snakemainwindow.h"
#include "ui_snakemainwindow.h"
#include <QTest>

SnakeMainWindow::SnakeMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SnakeMainWindow)
{
    ui->setupUi(this);
    resize(800,500);

    dir=1;

        connect(ui->menuBar,SIGNAL(triggered(QAction*)),this,SLOT(Triggering(QAction*)));
}

SnakeMainWindow::~SnakeMainWindow()
{
    delete ui;
}

void SnakeMainWindow::Triggering(QAction *ac){

    if(ui->startaction == ac){
        food=new SnakeNode(this,(qrand()%80)*10,(qrand()%50)*10);
        snake = new SnakeDialog(this);
        int ms=300;

        while(1){
            snake->move(dir,this);

            if(snake->shead->getPos() == food->getPos()){
                delete food;
                food=new SnakeNode(this,(qrand()%80)*10,(qrand()%50)*10);
                snake->eat(dir,this);
            }
            QPoint pos;
            pos=snake->shead->getPos();
            if(pos.x()<0 || pos.x()>800 || pos.y()<0 || pos.y()>500){
                QMessageBox::critical(this,"游戏结束","跑出边界了！");
                exit(1);
            }
            if(!snake->Check()){
                QMessageBox::critical(this,"游戏结束","吃到自己了！");
                exit(2);
            }

            QTest::qWait(ms);
        }
    }
}

void SnakeMainWindow::keyPressEvent(QKeyEvent* key){
    predir=dir;

    switch(key->key()){
    case 16777235:
        dir=1;
        if(2==predir){
            dir=predir;
            return ;
        }
        break;
    case 16777237:
        dir=2;
        if(1==predir){
            dir=predir;
            return ;
        }
        break;
    case 16777234:
        dir=3;
        if(4==predir){
            dir=predir;
            return ;
        }
        break;
    case 16777236:
        dir=4;
        if(3==predir){
            dir=predir;
            return ;
        }
        break;
    }
    snake->move(dir,this);

    if(snake->shead->getPos() == food->getPos()){
        delete food;
        food=new SnakeNode(this,(qrand()%80)*10,(qrand()%50)*10);
        snake->eat(dir,this);
    }
}










