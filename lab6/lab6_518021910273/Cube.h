#ifndef CUBE_H
#define CUBE_H

#include <QLabel>
#include <QWidget>
#include <string>
#include <QString>
#include <QMouseEvent>

class Cube : public QWidget
{
    Q_OBJECT
public:
    explicit Cube(int x,int y,QWidget *parent = nullptr,bool s = false);
    void setLetter(QString l);
    QLabel *label;
    QString getLetter();
    void highlight();
    void dehighlight();
    bool state;
    void mousePressEvent(QMouseEvent* event);
signals:
    void cubeClicked(int Cow, int Rol, QString l);
    void decubeClicked(int Cow, int Rol);

public slots:

private:
    int nx;
    int ny;
};

#endif // CUBE_H
