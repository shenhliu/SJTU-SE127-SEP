#include "Console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>

Console::Console(QWidget *parent) : QTextEdit(parent)
{
}

void Console::clear()
{
    //this->clear();
}

void Console::write(QString msg)
{
    this->append(msg);
}

void Console::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace)
    {
        QTextCursor cursor = this->textCursor();
        if(cursor.hasSelection())
        cursor.clearSelection();
        cursor.deletePreviousChar();
        this->setTextCursor(cursor);
        return;
    }
    if (event->key() == Qt::Key_Delete)
    {
        QTextCursor cursor = this->textCursor();
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        return;
    }

    if (event->key() == Qt::Key_Enter){
        QString newline = this->toPlainText();
        emit newLineWritten(newline);
        return;
    }
    if (this->textCursor().hasSelection())
        return;
    if (event->key() == Qt::Key_Return) {
        QTextCursor cursor = this->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::LineUnderCursor);
        QString lastLine = cursor.selectedText();
        newLineWritten(lastLine);
    }
    QTextEdit::keyPressEvent(event);
}






