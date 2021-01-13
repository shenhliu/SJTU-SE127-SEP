#ifndef SNAKEMAINWINDOW_H
#define SNAKEMAINWINDOW_H

#include <QMainWindow>
#include "snakedialog.h"
#include <QTest>
#include <QMessageBox>

namespace Ui {
class SnakeMainWindow;
}

class SnakeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SnakeMainWindow(QWidget *parent = 0);
    ~SnakeMainWindow();
    void keyPressEvent(QKeyEvent* key);

public:
    int dir,predir;
    SnakeNode *food;

private slots:
    void Triggering(QAction *ac);

private:
    Ui::SnakeMainWindow *ui;
    SnakeDialog *snake;

private:
};

#endif // SNAKEMAINWINDOW_H
