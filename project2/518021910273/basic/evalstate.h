#ifndef EVALSTATE_H
#define EVALSTATE_H
#include<map>
#include<QString>


using namespace std;
class evalstate
{
public:
    evalstate();
    void setValue(QString var,int value);   //用来改变变量的值或者添加新的变量
    int getValue (QString var);
    bool isDefined (QString var);
    void clear();
    QString Tranvrese();//遍历
private:
     map<QString,int> VarMap;
     QString contaning;
};

#endif // EVALSTATE_H






