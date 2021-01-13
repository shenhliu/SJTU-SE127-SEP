#include "exp.h"

Expression::Expression()
{

}

ConstantExp::ConstantExp(int val)
{
    value = val;
}

int ConstantExp::eval(evalstate &Vars) {
   return value;
}

ExpressionType ConstantExp::type()
{
    return CONSTANT;
}



IdentifierExp::IdentifierExp(QString name)
{
    this->name = name;
}

ExpressionType IdentifierExp::type()
{
    return IDENTIFIER;
}

int IdentifierExp::eval(evalstate &Vars)
{
    if(Vars.isDefined(name))
    {
        return 0;
    }
    else {
        return Vars.getValue(name);
    }
}










