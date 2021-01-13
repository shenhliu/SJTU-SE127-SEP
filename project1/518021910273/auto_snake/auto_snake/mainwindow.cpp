#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"wallnode.h"
#include<iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1000,530);
    m_timeId = startTimer(70-level*6);
    //m_timeId = startTimer(1);

    f = new food(this);
    s = new snake(this);


    GenerateBoundary();

    ScoreLabel=new QLabel(this);
    LevelLabel=new QLabel(this);
    ScoreLabel->setText("Score:");
    ScoreLabel->setGeometry(850,100,120,90);
    LevelLabel->setText("Level:");
    LevelLabel->setGeometry(850,200,120,90);

    ScoreLabelNumber=new QLabel(this);
    LevelLabelNumber=new QLabel(this);
    ScoreLabelNumber->setText(QString::number(score)+"分");
    ScoreLabelNumber->setGeometry(950,100,120,90);
    LevelLabelNumber->setText(QString::number(level)+"级");
    LevelLabelNumber->setGeometry(950,200,120,90);

}

void MainWindow::keyPressEvent(QKeyEvent*key)
{
    switch(key->key())//获取键盘操作，当前前进方向与键盘上获取的方向相反时则操纵无效
        {
           case Qt::Key_Up :    if(s->GetDir() != 2) s->SetDir(1) ; break;
           case Qt::Key_Down :  if(s->GetDir() != 1) s->SetDir(2); break;
           case Qt::Key_Left :  if(s->GetDir() != 4) s->SetDir(3); break;
           case Qt::Key_Right : if(s->GetDir() != 3) s->SetDir(4); break;
        }

}

void MainWindow::timerEvent(QTimerEvent *time)
{
    if (time->timerId() == m_timeId)
    {



        if(CheckEat())//先检查吃没吃到食物
        {
            score++;
            ScoreLabelNumber->setText(QString::number(score)+"分");
            food *tmp = f;
            delete tmp->ff;
            s->eat(CheckEat(),this);
            f = new food(this);

            level = score/5+1; //分数每上升5分，难度上升一档

            if(level >= 10)
            {
                 m_timeId = startTimer(15);
                 LevelLabelNumber->setText(QString::number(level)+"级");
            }
            else {
                m_timeId = startTimer(70-level*5);//难度每上升一档，刷新频率快10ms，如果难度大于10档，之后不再提高刷新速度（否则刷新频率会小于0）
                LevelLabelNumber->setText(QString::number(level)+"级");
            }
        }
        else
        {
            s->moveto(s->GetDir(),this);
            if(s->CheckEatSelf())  //检查各种死亡
            {
//                EatSelfTip();
            }
            if(CheckBoundary())
            {
//               EatBoundaryTip();
            }

        }
        if(s->GetDir() == 1 || s->GetDir() == 2)
        {
            if(s->body[0]->getPos().rx()<f->x)
            {
                s->SetDir(4);
            }
            if(s->body[0]->getPos().rx()>f->x)
            {
                s->SetDir(3);
            }
        }

        if(s->GetDir() == 3 || s->GetDir() ==4)
        {
            if(s->body[0]->getPos().ry()<f->y)
            {
                s->SetDir(2);
            }
            if(s->body[0]->getPos().ry()>f->y)
            {
                s->SetDir(1);
            }
        }

        if(s->body[0]->getPos().rx() == f->x && s->body[0]->getPos().ry()<f->y && s->GetDir() == 1)
        {
            s->SetDir(3);
        }
        if(s->body[0]->getPos().rx() == f->x && s->body[0]->getPos().ry()>f->y && s->GetDir() == 2)
        {
            s->SetDir(3);
        }
        if(s->body[0]->getPos().ry() == f->y && s->body[0]->getPos().rx()<f->x && s->GetDir() == 3)
        {
            s->SetDir(1);
        }
        if(s->body[0]->getPos().ry() == f->y && s->body[0]->getPos().rx()>f->x && s->GetDir() == 4)
        {
            s->SetDir(1);
        }
    }
}


int MainWindow::CheckEat()//检查是否吃到食物，实现方式是比较蛇头部和食物的坐标
{
    if((s->body[0]->getPos().ry()+10 == f->ff->getPos().ry())&&(s->body[0]->getPos().rx() == f->ff->getPos().rx())&&s->GetDir() == 2)
    {
        return 1;
    }
    if((s->body[0]->getPos().ry()-10 == f->ff->getPos().ry())&&(s->body[0]->getPos().rx() == f->ff->getPos().rx())&&s->GetDir() == 1)
    {
        return 2;
    }
    if((s->body[0]->getPos().ry() == f->ff->getPos().ry())&&(s->body[0]->getPos().rx()-10 == f->ff->getPos().rx())&&s->GetDir() == 3)
    {
        return 3;
    }
    if((s->body[0]->getPos().ry() == f->ff->getPos().ry())&&(s->body[0]->getPos().rx()+10 == f->ff->getPos().rx())&&s->GetDir() == 4)
    {
        return 4;
    }

    return 0;
}



void MainWindow::GenerateBoundary()//产生外部边界
{
    for(int i = 0;i<=820;++i)
    {
         wallnode *boundary1 = new wallnode (this,i,0);
         wallnode *boundary2 = new wallnode(this,i,520);

         boundary.push_back(boundary1);
         boundary.push_back(boundary2);


    }
    for(int j = 0;j<=530;++j)
    {
        wallnode *boundary3 = new wallnode(this,0,j);
        wallnode *boundary4 = new wallnode(this,820,j);
        boundary.push_back(boundary3);
        boundary.push_back(boundary4);
    }
}

int MainWindow::CheckBoundary()//检查是否撞到边界
{

    for(int j = 0;j< boundary.size();++j)
    {
        if(s->body[0]->getPos() == boundary[j]->getPos())
            return 1;
    }

    return 0;

}


void MainWindow::EatSelfTip()//咬到自己后的提示
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("你咬到自己了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {//重新开始游戏，只需要重新生成蛇，食物和墙，同时把各种数据清零。
            snake *tmps = s;
            for(int i = 0;i<s->body.length();i++)
            {
                delete tmps->body[i];
            }

            food *tmpf = f;
            delete tmpf->ff;

            score = 0;
            ScoreLabelNumber->setText(QString::number(score)+"分");
            level = 1;
            LevelLabelNumber->setText(QString::number(level)+"级");
            m_timeId = startTimer(70-level*5);
            f = new food(this);
            s = new snake(this);

        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}

void MainWindow::EatBoundaryTip()
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setIconPixmap(QPixmap("E:/lab+project/project/f_try/img/die.JEPG"));
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("你触碰到边界了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {

            snake *tmps = s;
            for(int i = 0;i<s->body.length();i++)
            {
                delete tmps->body[i];
            }

            food *tmpf = f;
            delete tmpf->ff;

            score = 0;
            ScoreLabelNumber->setText(QString::number(score)+"分");
            level = 1;
            LevelLabelNumber->setText(QString::number(level)+"级");
            m_timeId = startTimer(70-level*5);
            f = new food(this);
            s = new snake(this);

        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}


MainWindow::~MainWindow()
{
    delete ui;
}
