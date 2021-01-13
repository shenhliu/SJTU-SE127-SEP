#include "tokenizer.h"

tokenizer::tokenizer()
{

}

QList<QString>tokenizer::ToTokens(QString expression)
{
    Tokens.clear();
    expression.remove(QChar(' '), Qt::CaseInsensitive);         //先把空格给去掉
    int j = -1;        //j用来记录上一个符号所在的位置（为了方便截取两个符号间的东西）
    for(int i = 0;i<expression.length();++i)
    {
        if(IsOpertor(expression[i]))
        {
            string strexp = expression.toStdString();
            string tmp;                           //截取两个符号之间的部分，为什么QString的截取函数这么难用！
            tmp = strexp.substr(unsigned(j+1),unsigned(i-1-j));
            QString Qtmp = QString::fromStdString(tmp);
            Tokens.append(Qtmp);                         //把两个符号中间部分填进去
            Tokens.append(QString(expression[i]));              //把符号也填进去
            j = i;                               //记录当前符号的位置
        }
        else continue;
    }
    //把最后剩下的部分也填进去
    if(j!=-1)                         //正常情况
    {
        string strexp = expression.toStdString();
        string tmp;
        tmp = strexp.substr(unsigned(j+1),unsigned(expression.length()-1));
        QString Qtmp = QString::fromStdString(tmp);
        Tokens.append(Qtmp);


    }
    else {                          //这个表达式里没有符号的情况
        Tokens.append(expression);
    }
    return Tokens;
}

bool tokenizer::IsOpertor(QCharRef x)
{
    if(x == "+" || x =="-" || x == "*" || x == "/" || x == "=" || x == "(" || x == ")")
        return true;
    return false;
}


