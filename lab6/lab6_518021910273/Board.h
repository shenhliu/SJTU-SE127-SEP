#ifndef BOARD_H
#define BOARD_H

#include "Cube.h"
#include<iostream>
using namespace std;

#include <QWidget>
#include <ctime>
#include <QTime>
#include <QtGlobal>

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = nullptr, int size = 5, const QString *cubeLetters = BIG_BOGGLE_CUBES);
    virtual ~Board();
    inline int index(int i, int j) { return i * size + j; }
    void shake();
    Cube **cubes;
    void Extinguish();
    void reset();
signals:
    void clicked(QString word);

public slots:
    void cubeClicked(int line, int col, QString l);
    void decubeClicked(int line, int col);

private:
    int size = 5;

    QString *letters;
    QList<QPoint> clickedway;
    QList<QString> checkwords;
    QString clickedWord;

    static const QString STANDARD_CUBES[16];
    static const QString BIG_BOGGLE_CUBES[25];
};

#endif // BOARD_H
