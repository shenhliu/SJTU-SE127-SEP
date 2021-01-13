#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include "Board.h"
#include "Console.h"
#include "WordListWidget.h"
#include "lexicon.h"

#include <QMainWindow>
#include <QDebug>
#include <string>

class BoggleWindow : public QMainWindow
{
    Q_OBJECT

public:
    BoggleWindow(QWidget *parent = nullptr);
    ~BoggleWindow();
    void onecube_find(int nx,int ny,string cur);
    void board_find();


    void me_find(int nx,int ny,string word, unsigned int cur,bool &flag);
    void pc_find();
    bool human(QString kk);
    void restart();

public slots:
    void game(QString word);
    void cubeClicked(QString word);


private:

    WordListWidget *me;
    WordListWidget *computer;
    Board *board;
    Console *console;
    Lexicon lexi;
    QList<string> wordlist;
    bool replay = false;

    static const int BOGGLE_WINDOW_WIDTH = 800;
    static const int BOGGLE_WINDOW_HEIGHT = 600;
};




#endif // BOGGLEWINDOW_H
