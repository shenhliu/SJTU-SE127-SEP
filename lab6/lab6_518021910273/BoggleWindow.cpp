#include "BoggleWindow.h"
#include "lexicon.h"

#include <QFile>
#include <QHBoxLayout>
#include <QTextEdit>
#include <iostream>

BoggleWindow::BoggleWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("QBoggle!");
    this->setFixedSize(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);

    me = new WordListWidget(this, "Me");
    computer = new WordListWidget(this, "Computer");
    board = new Board(this);
    console = new Console(this);

    me->setGeometry(20, 20, 230, 300);
    board->setGeometry(230, 0, 300, 300);
    computer->setGeometry(800 - 50 - 200, 20, 230, 300);
    console->setGeometry(30, 320, 740, 260);


    QFile qFile(":/res/EnglishWords.txt");
    if (!qFile.open(QIODevice::ReadOnly)) {
        throw new std::runtime_error("Resource file not found!");
    }
    Lexicon lex(qFile);
    lexi = lex;
    //board->shake();

    /*
    for (std::string s: lex) {
        std::cout << s << std::endl;
    }
    */
    console->write("Welcome to the game Boggle!\n");
    console->write("Start your performance!\n\nYou can press the Enter key to let the computer help you find it.\n" );
    connect(board,SIGNAL(clicked(QString)),this,SLOT(cubeClicked(QString)));
    connect(console,SIGNAL(newLineWritten(QString)),this,SLOT(game(QString)));

}

BoggleWindow::~BoggleWindow()
{
}

void BoggleWindow::game(QString word)
{
    board->Extinguish();
    if(replay)
    {
        if(word=="Y"||word=="y")
        {
           replay=false;
           restart();
           return;
        }
        if(word=="N"||word=="n")
        {
            this->close();
        }
    }
    else {

        if(word=="")
        {
            pc_find();
            return;
        }

        else
        {
            QList<int> way;
            if (word.length() < 4)
               {
                   console->write("Word must be longer than 4 letters.");
                   return;
               }
            if (me->check(word))//判断是否录过该单词
            {
                console->write( "This word has already been written.");
                return;
            }
            if (!lexi.contains(word.toStdString()))
               {
                console->write("Wrong word.");
                return;
               }
            if (human(word)==false)
               {
                console->write("The word is not in the board.");
                return;
               }
            foreach(auto item,way)
            {
                board->cubes[item]->highlight();
            }
                me->addWord(word.toLower());
                me->addScore(word.length()-3);
                return;
        }
    }
}


bool BoggleWindow::human(QString p)
{
    string tmpp = p.toStdString();
    bool flag = false;
    string head = tmpp.substr(0,1);
    for(int x = 0;x<5;x++)
    {
        for(int y = 0;y<5;y++)
        {
            if(board->cubes[board->index(x,y)]->label->text().toLower() == p.at(0))
            {
                me_find(x,y,tmpp,0,flag);
            }
        }
    }
    return flag;
}

void BoggleWindow::me_find(int nx,int ny,string word,unsigned int cur,bool &flag)
{

    //word 为玩家输入的单词
    //nx ny为当前检测的board上的位置
    //cur为当前检测的word的字母位置
    //flag为检测的结果

    QString qtmp = board->cubes[board->index(nx,ny)]->getLetter();

    if(cur + 1 == word.length())
    {
        flag = true;
        return;
    }

    for(int dx = -1;dx<=1;dx++)
    {
        for(int dy = -1;dy<=1;dy++)
        {
            if(nx+dx>=0 && nx+dx<=4 &&
               ny+dy>=0 && ny+dy<=4 &&
               word.substr(cur+1,1) == board->cubes[board->index(nx+dx,ny+dy)]->getLetter().toLower().toStdString()
               &&!(dx == 0 && dy == 0) )
            {
                board->cubes[board->index(nx,ny)]->setLetter("!");
                me_find(nx+dx,ny+dy,word,cur+1,flag);
                board->cubes[board->index(nx,ny)]->setLetter(qtmp);   //防止一个cube中的letter被重复使用
            }
        }
    }
}

void BoggleWindow::onecube_find(int nx, int ny, string cur)
{
    QString qnowletter = board->cubes[board->index(nx,ny)]->getLetter();
    string nowletter = qnowletter.toStdString();
    cur = cur + nowletter;
    if(lexi.contains(cur) && cur.length()>=4)
    {
        bool flag = true;
        foreach(auto item,wordlist) {if(item==cur) flag = false;}//检查是否在word中出现过
        if(flag){
            wordlist.append(cur);
        }
        return;
    }             //找到这个word则返回

    if (!lexi.containsPrefix(cur))  //不含有前缀也返回
    {
        return;
    }

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (nx + dx >= 0 && nx + dx < 5 &&
                ny + dy >= 0 && ny + dy <5 &&
                board->cubes[board->index(nx + dx, ny + dy)]->getLetter()!= "!" &&
                !(dx == 0 && dy == 0) )
            {
                board->cubes[board->index(nx,ny)]->setLetter("!");
                onecube_find(nx+dx,ny+dy,cur);
                board->cubes[board->index(nx,ny)]->setLetter(qnowletter); // 递归结束后取消标记
            }
        }
    }
}

void BoggleWindow::board_find()
{
    for(int x = 0;x<5;x++)
    {
        for(int y = 0;y<5;y++)
        {
            string cur = "";
            onecube_find(x,y,cur);
        }
    }
}

void BoggleWindow::pc_find()
{
    board_find();
    foreach(auto item,wordlist)
    {
        QString qitem = QString::fromStdString(item);
        if(!me->check(qitem))
        {
            computer->addWord(qitem.toLower());
            computer->addScore(qitem.length()-3);
        }
    }
    wordlist.clear();
    console->write("Do you want to play again?(Y/N)");
    replay=true;
}

void BoggleWindow::cubeClicked(QString word)
{
    if(!replay)
    {
        if (me->check(word))
           {
               return;
           }
        if (!lexi.contains(word.toStdString()))
           {
            return;
           }
            me->addWord(word.toLower());
            me->addScore(word.length()-3);
            board->reset();
            return;
    }
    else {
        console->write( "Please write 'Y'/'N'to restart.");
    }
}

void BoggleWindow::restart()
{
    me->reset();
    me->wordTable->reset();
    computer->reset();
    computer->wordTable->reset();
    board->shake();
    console->clear();
    me->scoreLabel->setText("0");
    computer->scoreLabel->setText("0");
}







