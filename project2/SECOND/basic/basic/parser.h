#ifndef PARSER_H
#define PARSER_H
# include"exp.h"
# include<QList>
# include<stack>


class parser
{
public:
    parser();
    Expression * ToTree(QList<QString> tokens);

private:
    stack<QString> Operators;
    stack<Expression*> Operands;

    bool IsCompoundexp(QString);
    bool IsConstantexp(QString);
    bool IsIdentifierexp(QString);

    int ConstantValue(QString);
    int IdentifierValue(QString exp,evalstate&Vars);

    int GetPriority(QString ope);


    bool IsMulDiv(QString); //是不是*/
    bool IsAddSub(QString); //是不是+-
    bool IsEqu(QString);    //是不是=
    bool IsLeftpar(QString); //是不是 (
    bool IsRightpar(QString); //是不是 )
};

#endif // PARSER_H
