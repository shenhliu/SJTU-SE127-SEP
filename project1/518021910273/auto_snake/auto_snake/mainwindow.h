#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"snake.h"
#include"food.h"
#include"wallnode.h"
#include <QKeyEvent>
#include <QMessageBox>
#include<QPushButton>
#include<QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int CheckEat(void);
    int CheckEatSF1(void);
    int CheckEatSF2(void);
    void GenerateBoundary(void);
    int CheckBoundary(void);
    int CheckWall(void);


    void keyPressEvent(QKeyEvent*k);
    void timerEvent(QTimerEvent*);
    void EatSelfTip();
    void EatBoundaryTip();
    void EatWallTip();


public:
    void Trigerring();
private slots:


private:

    Ui::MainWindow *ui;

    int score = 0;
    int level = 1;


    food*f;

    snake *s;



    int m_timeId;

    QList<wallnode*> boundary;
    QLabel *ScoreLabel;
    QLabel *LevelLabel;
    QLabel *ScoreLabelNumber;
    QLabel *LevelLabelNumber;
};

#endif // MAINWINDOW_H
