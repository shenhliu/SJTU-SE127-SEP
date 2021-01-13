#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T22:58:11
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Snake
TEMPLATE = app


SOURCES += main.cpp\
        snakemainwindow.cpp \
    snakenode.cpp \
    snakedialog.cpp

HEADERS  += snakemainwindow.h \
    snakenode.h \
    snakedialog.h

FORMS    += snakemainwindow.ui
