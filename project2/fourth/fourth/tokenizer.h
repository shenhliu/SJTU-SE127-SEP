#ifndef TOKENIZER_H
#define TOKENIZER_H
# include<QString>
# include<QList>
# include"string.h"
using namespace std;
class tokenizer
{
public:
    tokenizer();
    QList<QString>ToTokens(QString expression);
    bool IsOpertor(QCharRef x);
    bool IsCom(QString x);
    bool IsConstantExp(QString x);

private:
    QList<QString>Tokens;
};

#endif // TOKENIZER_H
