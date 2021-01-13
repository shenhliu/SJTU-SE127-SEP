#ifndef WORDTABLE_H
#define WORDTABLE_H

#include <QObject>
#include <QTableWidget>
#include <QWidget>

class WordTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit WordTable(QWidget *parent = nullptr, int maxCol = 3);
    void addWord(QString word);

    void reset();
signals:

public slots:

private:
    int row;
    int col;
    int maxCol;
};

#endif // WORDTABLE_H
