#ifndef STATEMENT_H
#define STATEMENT_H
# include<QString>
# include<string.h>
# include<QList>
using namespace std;
class statement
{
    friend class program;
    friend class MainWindow;
public:
    statement();
    statement(QString state,statement*n = nullptr);
    void cover(QString ntext);
    int getlinenum();
    QString gettext();

private:
    int linenum = 0;
    QString text;
    statement *next;
    QList<QString> lst;
};

#endif // STATEMENT_H
