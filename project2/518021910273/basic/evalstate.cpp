#include "evalstate.h"

evalstate::evalstate()
{

}

void evalstate::setValue(QString var, int value)
{
    VarMap[var] = value;
}

int evalstate::getValue(QString var)
{
    return VarMap[var];
}

void evalstate::clear()
{
    VarMap.clear();
}

bool evalstate::isDefined(QString var)
{
    return VarMap.count(var);
}

QString evalstate::Tranvrese()
{
    contaning = "";
    map<QString,int>::iterator iter;
        iter = VarMap.begin();
        while(iter != VarMap.end()){
            contaning += iter->first;
            contaning += "\t";
            contaning += QString::number(iter->second);
            contaning += "\n";
            iter++;
        }

    return contaning;
}







