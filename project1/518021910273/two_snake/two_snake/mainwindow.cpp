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
    m_timeId1 = startTimer(70-level1*6);
    m_timeId2 = startTimer(70-level2*6);
    f = new food(this);
    s1 = new snake1(this);
    s2 = new snake2(this);
    w = new wall(this);

    GenerateBoundary();

    ScoreLabel1=new QLabel(this);
    LevelLabel1=new QLabel(this);
    ScoreLabel1->setText("Score1:");
    ScoreLabel1->setGeometry(850,50,120,90);
    LevelLabel1->setText("Level1:");
    LevelLabel1->setGeometry(850,100,120,90);

    ScoreLabelNumber1=new QLabel(this);
    LevelLabelNumber1=new QLabel(this);
    ScoreLabelNumber1->setText(QString::number(score1)+"分");
    ScoreLabelNumber1->setGeometry(950,50,120,90);
    LevelLabelNumber1->setText(QString::number(level2)+"级");
    LevelLabelNumber1->setGeometry(950,100,120,90);

    ScoreLabel2=new QLabel(this);
    LevelLabel2=new QLabel(this);
    ScoreLabel2->setText("Score2:");
    ScoreLabel2->setGeometry(850,250,120,90);
    LevelLabel2->setText("Level2:");
    LevelLabel2->setGeometry(850,300,120,90);

    ScoreLabelNumber2=new QLabel(this);
    LevelLabelNumber2=new QLabel(this);
    ScoreLabelNumber2->setText(QString::number(score1)+"分");
    ScoreLabelNumber2->setGeometry(950,250,120,90);
    LevelLabelNumber2->setText(QString::number(level2)+"级");
    LevelLabelNumber2->setGeometry(950,300,120,90);

}

void MainWindow::keyPressEvent(QKeyEvent*key)
{
    switch(key->key())//获取键盘操作，当前前进方向与键盘上获取的方向相反时则操纵无效
        {
           case Qt::Key_Up :    if(s1->GetDir() != 2) s1->SetDir(1) ; break;
           case Qt::Key_Down :  if(s1->GetDir() != 1) s1->SetDir(2); break;
           case Qt::Key_Left :  if(s1->GetDir() != 4) s1->SetDir(3); break;
           case Qt::Key_Right : if(s1->GetDir() != 3) s1->SetDir(4); break;
        }
    switch(key->key())//获取键盘操作，当前前进方向与键盘上获取的方向相反时则操纵无效
        {
           case Qt::Key_W :    if(s2->GetDir() != 2) s2->SetDir(1) ; break;
           case Qt::Key_S :  if(s2->GetDir() != 1) s2->SetDir(2); break;
           case Qt::Key_A :  if(s2->GetDir() != 4) s2->SetDir(3); break;
           case Qt::Key_D : if(s2->GetDir() != 3) s2->SetDir(4); break;
        }
}

void MainWindow::timerEvent(QTimerEvent *time)
{
    if (time->timerId() == m_timeId1)
    {
        if(Checks1Eat())//先检查吃没吃到食物
        {
            score1++;
            ScoreLabelNumber1->setText(QString::number(score1)+"分");
            food *tmp = f;
            delete tmp->ff;
            s1->eat(Checks1Eat(),this);
            f = new food(this);

            level1 = score1/2+1; //分数每上升2分，难度上升一档

            if(level1 >= 10)
            {
                 m_timeId1 = startTimer(15);
                 LevelLabelNumber1->setText(QString::number(level1)+"级");
            }
            else {
                m_timeId1 = startTimer(70-level1*5);//难度每上升一档，刷新频率快10ms，如果难度大于10档，之后不再提高刷新速度（否则刷新频率会小于0）
                LevelLabelNumber1->setText(QString::number(level1)+"级");
            }


            if(score1 % 5 == 0)//分数每提高五分，就刷新一次随机产生的墙
            {
                wall *tmpw = w;
                for(int i = 0;i<w->ww.length();++i)
                {
                    delete tmpw->ww[i];
                }
                w = new wall(this);
            }

        }
        else
        {
            s1->moveto(s1->GetDir(),this);
            if(s1->CheckEatSelf())  //检查各种死亡
            {
               s1EatSelfTip();
            }
            if(s1CheckBoundary())
            {
               s1EatBoundaryTip();
            }
            if(s1CheckWall())
            {
               s1EatWallTip();
            }
        }
    }

    if (time->timerId() == m_timeId2)
    {
        if(Checks2Eat())//先检查吃没吃到食物
        {
            score2++;
            ScoreLabelNumber2->setText(QString::number(score1)+"分");
            food *tmp = f;
            delete tmp->ff;
            s2->eat(Checks2Eat(),this);
            f = new food(this);

            level2 = score2/2+1; //分数每上升2分，难度上升一档

            if(level2 >= 10)
            {
                 m_timeId2 = startTimer(15);
                 LevelLabelNumber2->setText(QString::number(level2)+"级");
            }
            else {
                m_timeId2 = startTimer(70-level1*5);//难度每上升一档，刷新频率快10ms，如果难度大于10档，之后不再提高刷新速度（否则刷新频率会小于0）
                LevelLabelNumber2->setText(QString::number(level2)+"级");
            }


            if(score1 % 5 == 0)//分数每提高五分，就刷新一次随机产生的墙
            {
                wall *tmpw = w;
                for(int i = 0;i<w->ww.length();++i)
                {
                    delete tmpw->ww[i];
                }
                w = new wall(this);
            }

        }
        else
        {
            s2->moveto(s2->GetDir(),this);
            if(s2->CheckEatSelf())  //检查各种死亡
            {
                s2EatSelfTip();
            }
            if(s2CheckBoundary())
            {
               s2EatBoundaryTip();
            }
            if(s2CheckWall())
            {
                s2EatWallTip();
            }
        }

        if(score1 >= 10)
        {
            s1WinTip();
        }

        if(score2 >= 10)
        {
            s2WinTip();
        }

    }
}


int MainWindow::Checks1Eat()//检查是否吃到食物，实现方式是比较蛇头部和食物的坐标
{
    if((s1->body[0]->getPos().ry()+10 == f->ff->getPos().ry())&&(s1->body[0]->getPos().rx() == f->ff->getPos().rx())&&s1->GetDir() == 2)
    {
        return 1;
    }
    if((s1->body[0]->getPos().ry()-10 == f->ff->getPos().ry())&&(s1->body[0]->getPos().rx() == f->ff->getPos().rx())&&s1->GetDir() == 1)
    {
        return 2;
    }
    if((s1->body[0]->getPos().ry() == f->ff->getPos().ry())&&(s1->body[0]->getPos().rx()-10 == f->ff->getPos().rx())&&s1->GetDir() == 3)
    {
        return 3;
    }
    if((s1->body[0]->getPos().ry() == f->ff->getPos().ry())&&(s1->body[0]->getPos().rx()+10 == f->ff->getPos().rx())&&s1->GetDir() == 4)
    {
        return 4;
    }

    return 0;
}

int MainWindow::Checks2Eat()//检查是否吃到食物，实现方式是比较蛇头部和食物的坐标
{
    if((s2->body[0]->getPos().ry()+10 == f->ff->getPos().ry())&&(s2->body[0]->getPos().rx() == f->ff->getPos().rx())&&s2->GetDir() == 2)
    {
        return 1;
    }
    if((s2->body[0]->getPos().ry()-10 == f->ff->getPos().ry())&&(s2->body[0]->getPos().rx() == f->ff->getPos().rx())&&s2->GetDir() == 1)
    {
        return 2;
    }
    if((s2->body[0]->getPos().ry() == f->ff->getPos().ry())&&(s2->body[0]->getPos().rx()-10 == f->ff->getPos().rx())&&s2->GetDir() == 3)
    {
        return 3;
    }
    if((s2->body[0]->getPos().ry() == f->ff->getPos().ry())&&(s2->body[0]->getPos().rx()+10 == f->ff->getPos().rx())&&s2->GetDir() == 4)
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

int MainWindow::s1CheckBoundary()//检查是否撞到边界
{

    for(int j = 0;j< boundary.size();++j)
    {
        if(s1->body[0]->getPos() == boundary[j]->getPos())
            return 1;
    }

    return 0;

}

int MainWindow::s2CheckBoundary()//检查是否撞到边界
{
    for(int j = 0;j< boundary.size();++j)
    {
        if(s2->body[0]->getPos() == boundary[j]->getPos())
            return 1;
    }
    return 0;
}

int MainWindow::s1CheckWall()//检查是否撞到墙了
{
    for(int j = 0;j<w->ww.length();++j)
    {
        if(s1->body[0]->getPos() == w->ww[j]->getPos())
            return 1;
    }
    return 0;
}

int MainWindow::s2CheckWall()//检查是否撞到墙了
{
    for(int j = 0;j<w->ww.length();++j)
    {
        if(s2->body[0]->getPos() == w->ww[j]->getPos())
            return 1;
    }
    return 0;
}


void MainWindow::s1EatSelfTip()//咬到自己后的提示
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("s1咬到自己了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {//重新开始游戏，只需要重新生成蛇，食物和墙，同时把各种数据清零。
            snake1 *tmps1 = s1;
            for(int i = 0;i<s1->body.length();i++)
            {
                delete tmps1->body[i];
            }

            snake2 *tmps2 = s2;
            for(int i = 0;i<s2->body.length();i++)
            {
                delete tmps2->body[i];
            }
            food *tmpf = f;
            delete tmpf->ff;

            score1 = 0;
            ScoreLabelNumber1->setText(QString::number(score1)+"分");
            level1 = 1;
            LevelLabelNumber1->setText(QString::number(level1)+"级");
            m_timeId1 = startTimer(70-level1*5);
            f = new food(this);
            s1 = new snake1(this);
            wall *tmpw = w;
            for(int i = 0;i<w->ww.length();++i)
            {
                delete tmpw->ww[i];
            }
            w = new wall(this);

            score2 = 0;
            ScoreLabelNumber2->setText(QString::number(score2)+"分");
            level2 = 1;
            LevelLabelNumber2->setText(QString::number(level2)+"级");
            m_timeId2 = startTimer(70-level2*5);

            s2 = new snake2(this);
        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}

void MainWindow::s1EatBoundaryTip()
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setIconPixmap(QPixmap("E:/lab+project/project/f_try/img/die.JEPG"));
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("s1触碰到边界了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {//重新开始游戏，只需要重新生成蛇，食物和墙，同时把各种数据清零。
            snake1 *tmps1 = s1;
            for(int i = 0;i<s1->body.length();i++)
            {
                delete tmps1->body[i];
            }

            snake2 *tmps2 = s2;
            for(int i = 0;i<s2->body.length();i++)
            {
                delete tmps2->body[i];
            }
            food *tmpf = f;
            delete tmpf->ff;

            score1 = 0;
            ScoreLabelNumber2->setText(QString::number(score1)+"分");
            level1 = 1;
            LevelLabelNumber2->setText(QString::number(level1)+"级");
            m_timeId1 = startTimer(70-level1*5);
            f = new food(this);
            s1 = new snake1(this);
            wall *tmpw = w;
            for(int i = 0;i<w->ww.length();++i)
            {
                delete tmpw->ww[i];
            }
            w = new wall(this);

            score2 = 0;
            ScoreLabelNumber2->setText(QString::number(score2)+"分");
            level2 = 1;
            LevelLabelNumber2->setText(QString::number(level2)+"级");
            m_timeId2 = startTimer(70-level2*5);

            s2 = new snake2(this);
        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}

void MainWindow::s1EatWallTip()
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("s1撞到墙了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {//重新开始游戏，只需要重新生成蛇，食物和墙，同时把各种数据清零。
            snake1 *tmps1 = s1;
            for(int i = 0;i<s1->body.length();i++)
            {
                delete tmps1->body[i];
            }

            snake2 *tmps2 = s2;
            for(int i = 0;i<s2->body.length();i++)
            {
                delete tmps2->body[i];
            }
            food *tmpf = f;
            delete tmpf->ff;

            score1 = 0;
            ScoreLabelNumber1->setText(QString::number(score1)+"分");
            level1 = 1;
            LevelLabelNumber1->setText(QString::number(level1)+"级");
            m_timeId1 = startTimer(70-level1*5);
            f = new food(this);
            s1 = new snake1(this);
            wall *tmpw = w;
            for(int i = 0;i<w->ww.length();++i)
            {
                delete tmpw->ww[i];
            }
            w = new wall(this);

            score2 = 0;
            ScoreLabelNumber2->setText(QString::number(score2)+"分");
            level2 = 1;
            LevelLabelNumber2->setText(QString::number(level2)+"级");
            m_timeId2 = startTimer(70-level2*5);

            s2 = new snake2(this);
        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}

void MainWindow::s2EatSelfTip()//咬到自己后的提示
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("s2咬到自己了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {//重新开始游戏，只需要重新生成蛇，食物和墙，同时把各种数据清零。
            snake1 *tmps1 = s1;
            for(int i = 0;i<s1->body.length();i++)
            {
                delete tmps1->body[i];
            }

            snake2 *tmps2 = s2;
            for(int i = 0;i<s2->body.length();i++)
            {
                delete tmps2->body[i];
            }
            food *tmpf = f;
            delete tmpf->ff;

            score1 = 0;
            ScoreLabelNumber1->setText(QString::number(score1)+"分");
            level1 = 1;
            LevelLabelNumber1->setText(QString::number(level1)+"级");
            m_timeId1 = startTimer(70-level1*5);
            f = new food(this);
            s1 = new snake1(this);
            wall *tmpw = w;
            for(int i = 0;i<w->ww.length();++i)
            {
                delete tmpw->ww[i];
            }
            w = new wall(this);

            score2 = 0;
            ScoreLabelNumber2->setText(QString::number(score2)+"分");
            level2 = 1;
            LevelLabelNumber2->setText(QString::number(level2)+"级");
            m_timeId2 = startTimer(70-level2*5);

            s2 = new snake2(this);
        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}

void MainWindow::s2EatBoundaryTip()
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setIconPixmap(QPixmap("E:/lab+project/project/f_try/img/die.JEPG"));
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("s2触碰到边界了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {//重新开始游戏，只需要重新生成蛇，食物和墙，同时把各种数据清零。
            snake1 *tmps1 = s1;
            for(int i = 0;i<s1->body.length();i++)
            {
                delete tmps1->body[i];
            }

            snake2 *tmps2 = s2;
            for(int i = 0;i<s2->body.length();i++)
            {
                delete tmps2->body[i];
            }
            food *tmpf = f;
            delete tmpf->ff;

            score1 = 0;
            ScoreLabelNumber1->setText(QString::number(score1)+"分");
            level1 = 1;
            LevelLabelNumber1->setText(QString::number(level1)+"级");
            m_timeId1 = startTimer(70-level1*5);
            f = new food(this);
            s1 = new snake1(this);
            wall *tmpw = w;
            for(int i = 0;i<w->ww.length();++i)
            {
                delete tmpw->ww[i];
            }
            w = new wall(this);

            score2 = 0;
            ScoreLabelNumber2->setText(QString::number(score2)+"分");
            level2 = 1;
            LevelLabelNumber2->setText(QString::number(level2)+"级");
            m_timeId2 = startTimer(70-level2*5);

            s2 = new snake2(this);
        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}

void MainWindow::s2EatWallTip()
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("s2撞到墙了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {//重新开始游戏，只需要重新生成蛇，食物和墙，同时把各种数据清零。
            snake1 *tmps1 = s1;
            for(int i = 0;i<s1->body.length();i++)
            {
                delete tmps1->body[i];
            }

            snake2 *tmps2 = s2;
            for(int i = 0;i<s2->body.length();i++)
            {
                delete tmps2->body[i];
            }
            food *tmpf = f;
            delete tmpf->ff;

            score1 = 0;
            ScoreLabelNumber1->setText(QString::number(score1)+"分");
            level1 = 1;
            LevelLabelNumber1->setText(QString::number(level1)+"级");
            m_timeId1 = startTimer(70-level1*5);
            f = new food(this);
            s1 = new snake1(this);
            wall *tmpw = w;
            for(int i = 0;i<w->ww.length();++i)
            {
                delete tmpw->ww[i];
            }
            w = new wall(this);

            score2 = 0;
            ScoreLabelNumber2->setText(QString::number(score2)+"分");
            level2 = 1;
            LevelLabelNumber2->setText(QString::number(level2)+"级");
            m_timeId2 = startTimer(70-level2*5);

            s2 = new snake2(this);
        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}

void MainWindow::s1WinTip()
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("s1赢了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {//重新开始游戏，只需要重新生成蛇，食物和墙，同时把各种数据清零。
            snake1 *tmps1 = s1;
            for(int i = 0;i<s1->body.length();i++)
            {
                delete tmps1->body[i];
            }

            snake2 *tmps2 = s2;
            for(int i = 0;i<s2->body.length();i++)
            {
                delete tmps2->body[i];
            }
            food *tmpf = f;
            delete tmpf->ff;

            score1 = 0;
            ScoreLabelNumber1->setText(QString::number(score1)+"分");
            level1 = 1;
            LevelLabelNumber1->setText(QString::number(level1)+"级");
            m_timeId1 = startTimer(70-level1*5);
            f = new food(this);
            s1 = new snake1(this);
            wall *tmpw = w;
            for(int i = 0;i<w->ww.length();++i)
            {
                delete tmpw->ww[i];
            }
            w = new wall(this);

            score2 = 0;
            ScoreLabelNumber2->setText(QString::number(score2)+"分");
            level2 = 1;
            LevelLabelNumber2->setText(QString::number(level2)+"级");
            m_timeId2 = startTimer(70-level2*5);

            s2 = new snake2(this);
        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}

void MainWindow::s2WinTip()
{
    QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setIcon(QMessageBox::Warning);
        messageBox->setWindowTitle("游戏结束");
        messageBox->setText("s2赢了，是否重新游戏？");
        messageBox->addButton("退出游戏", QMessageBox::RejectRole); //自定义退出游戏按钮
        messageBox->addButton("重新玩", QMessageBox::AcceptRole); //自定义重新玩按钮
        if(messageBox->exec() == QDialog::Accepted) {//重新开始游戏，只需要重新生成蛇，食物和墙，同时把各种数据清零。
            snake1 *tmps1 = s1;
            for(int i = 0;i<s1->body.length();i++)
            {
                delete tmps1->body[i];
            }

            snake2 *tmps2 = s2;
            for(int i = 0;i<s2->body.length();i++)
            {
                delete tmps2->body[i];
            }
            food *tmpf = f;
            delete tmpf->ff;

            score1 = 0;
            ScoreLabelNumber1->setText(QString::number(score1)+"分");
            level1 = 1;
            LevelLabelNumber1->setText(QString::number(level1)+"级");
            m_timeId1 = startTimer(70-level1*5);
            f = new food(this);
            s1 = new snake1(this);
            wall *tmpw = w;
            for(int i = 0;i<w->ww.length();++i)
            {
                delete tmpw->ww[i];
            }
            w = new wall(this);

            score2 = 0;
            ScoreLabelNumber2->setText(QString::number(score2)+"分");
            level2 = 1;
            LevelLabelNumber2->setText(QString::number(level2)+"级");
            m_timeId2 = startTimer(70-level2*5);

            s2 = new snake2(this);
        }
        if(messageBox->exec()== QDialog::Rejected){

            MainWindow::close();
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}
