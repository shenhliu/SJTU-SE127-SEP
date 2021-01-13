#include "Cube.h"

#include <QHBoxLayout>

Cube::Cube(int x,int y,QWidget *parent,bool s) : QWidget(parent)
{
    nx = x;
    ny = y;
    state = s;
    label = new QLabel();
    label->setText("");
    label->setAlignment(Qt::AlignCenter);
    QFont font = label->font();
    font.setPointSize(20);
    label->setFont(font);

    this->setFixedSize(75, 75);
    this->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    setLayout(layout);
}

void Cube::setLetter(QString l)
{
    if(l == "Q")
    {
        label->setText("Qu");
    }
    label->setText(l);
}
QString Cube::getLetter()
{
    return label->text();
}

void Cube::highlight()
{
    this->state = true;
    this->setStyleSheet("background-color:blue; border-radius: 15px; border: 2px solid");
}

void Cube::dehighlight()
{
    this->state = false;
    this->setStyleSheet("background-color: white; border-radius: 15px; border: 2px solid");
}

void Cube::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(state == false){
            this->highlight();
            emit cubeClicked(this->nx, this->ny, this->getLetter());
        }
    }

    if(event->button() == Qt::RightButton){
        if(state == true){
            this->dehighlight();
            emit decubeClicked(this->nx, this->ny);
        }
    }
}
