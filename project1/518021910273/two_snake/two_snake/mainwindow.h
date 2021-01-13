#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"snake1.h"
#include"snake2.h"
#include"food.h"
#include"wallnode.h"
#include <QKeyEvent>
#include <QMessageBox>
#include<QPushButton>
#include<QLabel>
#include"wall.h"
#include"QWindow"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int Checks1Eat(void);
    int Checks2Eat(void);
    void GenerateBoundary(void);

    int s1CheckBoundary(void);
    int s1CheckWall(void);

    int s2CheckBoundary(void);
    int s2CheckWall(void);


    void keyPressEvent(QKeyEvent*k);
    void timerEvent(QTimerEvent*);
    void s1EatSelfTip();
    void s1EatBoundaryTip();
    void s1EatWallTip();

    void s2EatSelfTip();
    void s2EatBoundaryTip();
    void s2EatWallTip();

    void s1WinTip();
    void s2WinTip();


public:
    void Trigerring();
private slots:


private:

    Ui::MainWindow *ui;

    int score1 = 0;
    int level1 = 1;
    int score2 = 0;
    int level2 = 1;


    food*f;

    snake1 *s1;
    snake2 *s2;
    wall *w;


    int m_timeId1;
    int m_timeId2;

    QList<wallnode*> boundary;
    QLabel *ScoreLabel1;
    QLabel *LevelLabel1;
    QLabel *ScoreLabelNumber1;
    QLabel *LevelLabelNumber1;

    QLabel *ScoreLabel2;
    QLabel *LevelLabel2;
    QLabel *ScoreLabelNumber2;
    QLabel *LevelLabelNumber2;
};

#endif // MAINWINDOW_H
