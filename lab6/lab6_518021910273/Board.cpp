#include "Board.h"
#include "Cube.h"

#include <QGridLayout>


const QString Board::STANDARD_CUBES[16]  = {
        "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
        "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
        "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
        "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const QString Board::BIG_BOGGLE_CUBES[25]  = {
        "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
        "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Board::Board(QWidget *parent, int size, const QString *cubeLetters) : QWidget(parent)
{
    this->size = size;
    this->cubes = new Cube*[size * size];
    this->letters = new QString[size * size];
    for (int i = 0; i < size * size; ++i)
        this->letters[i] = cubeLetters[i];

    QGridLayout *layout = new QGridLayout();
    layout->setMargin(20);
    layout->setSpacing(10);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)] = new Cube(i,j,this,false);
            layout->addWidget(this->cubes[index(i, j)], i, j, Qt::AlignmentFlag::AlignCenter);
        }
    }
    setLayout(layout);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)]->setLetter(this->letters[index(i, j)].at(0));
        }
    }
    // this->setStyleSheet("background-color:grey; border: 3px solid");

    for(int i=0; i<= index(4,4); i++)
        connect(cubes[i],SIGNAL(cubeClicked(int, int, QString)),this,SLOT(cubeClicked(int, int, QString)));

    for(int i=0; i<= index(4,4); i++)
        connect(cubes[i],SIGNAL(decubeClicked(int, int)),this,SLOT(decubeClicked(int, int)));
}

Board::~Board()
{
    if (cubes) delete[] cubes;
    if (letters) delete[] letters;
}

void Board::shake()
{
    // Shake Cubes


    qsrand(QTime::currentTime().msec());
    for(int i = 0;i<this->size*this->size;++i)
    {
        int r = qrand()%(this->size*this->size-i)+i;
        Cube *tmp = new Cube(1,1);
        tmp = cubes[i];
        cubes[i] = cubes[r];
        cubes[r] = tmp;
    }
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cubes[index(i, j)]->setLetter(BIG_BOGGLE_CUBES[index(i,j)].at(qrand()%6));
            }
        }

}

void Board::Extinguish()
{
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            this->cubes[index(i, j)]->dehighlight();
        }
    }
}

void Board::reset()
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            this->cubes[index(i, j)]->dehighlight();
        }
    }

    clickedway.clear();
    clickedWord = "";
}

void Board::cubeClicked(int line, int col, QString l)
{
    if(clickedway.isEmpty())
    {
        QPoint tmp(line, col);
        clickedway.append(tmp);
        clickedWord.append(l);
    }

    else {
        int lastline = clickedway.last().rx();
        int lastcol = clickedway.last().ry();
        if(line-lastline>=-1 && line-lastline<=1 && col-lastcol >= -1 && col-lastcol<=1)//检查是否连续
        {
            clickedWord.append(l);
            lastline = line;
            lastcol = col;
            QPoint tmp(line,col);
            clickedway.append(tmp);
            if(clickedWord.length() >= 4)
                emit clicked(clickedWord);
        }
        else
        {
            cubes[index(line, col)]->dehighlight();
        }
    }
}

void Board::decubeClicked(int line, int col)
{
    if(!clickedway.isEmpty())
    {
        int lastCowClicked = clickedway.last().rx();
        int lastRolClicked = clickedway.last().ry();
        if(line == lastCowClicked && col == lastRolClicked)
        {
            clickedWord.chop(1);
            clickedway.removeLast();
        }
        else {
             cubes[index(line,col)]->highlight();
        }
    }
}




