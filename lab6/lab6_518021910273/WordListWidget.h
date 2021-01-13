#ifndef WORDLISTWIDGET_H
#define WORDLISTWIDGET_H

#include "WordTable.h"

#include <QWidget>

#include <QLabel>

#include<iostream>
using namespace std;
class WordListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WordListWidget(QWidget *parent = nullptr, QString label = "");
    void addScore(int s);
    void addWord(QString word);
    void reset();
    bool check(QString word);//检查list是否已经有word
    QLabel *scoreLabel;
    WordTable *wordTable;
signals:

public slots:

private:
    QString label;
    QList<QString> words;
    int score = 0;

};

#endif // WORDLISTWIDGET_H
