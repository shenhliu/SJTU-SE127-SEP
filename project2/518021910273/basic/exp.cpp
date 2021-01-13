#include "exp.h"

Expression::Expression()
{

}

Expression::~Expression()
{

}

ConstantExp::ConstantExp(int val)
{
    value = val;
}

QString ConstantExp::getIdentifierName()
{
    return " ";
}

int ConstantExp::eval(evalstate &Vars) {
   Vars.isDefined("a");
   return value;
}

ExpressionType ConstantExp::type()
{
    return CONSTANT;
}

ConstantExp::~ConstantExp()
{

}

IdentifierExp::IdentifierExp(QString name)
{
    this->name = name;
}

ExpressionType IdentifierExp::type()
{
    return IDENTIFIER;
}

QString IdentifierExp::getIdentifierName()
{
    return this->name;
}

int IdentifierExp::eval(evalstate &Vars)
{
    if(!Vars.isDefined(name))
    {
        QString error = "";
        error += name;
        error += " is not defined!";
        throw error;
    }
    else {
        return Vars.getValue(name);
    }
}

IdentifierExp::~IdentifierExp()
{

}

CompoundExp::CompoundExp(QString op, Expression *lhs, Expression *rhs)
{
    this->op = op;
    this->lhs = lhs;
    this->rhs = rhs;
}

CompoundExp::~CompoundExp()
{

}

ExpressionType CompoundExp::type()
{
    return COMPOUND;
}

int CompoundExp::eval(evalstate&Vars)
{
    if(rhs == nullptr)
    {
        QString t = "Illegal operator in expression , an operator must have right value!";
        throw t;
    }
    int right = rhs->eval(Vars);
       if (op == "=") {
          Vars.setValue(lhs->getIdentifierName(), right);
          return right;
       }
       if(lhs == nullptr)
       {
           QString t = "Illegal operator in expression , an operator must have left value!";
           throw t;
       }
       int left = lhs->eval(Vars);
       if (op == "+") return left + right;
       if (op == "-") return left - right;
       if (op == "*") return left * right;
       if (op == "/") {
          if (right == 0)
          {
              QString error = "Division by 0";
              throw(error);
          }
          return left / right;
       }       
       QString err = "Illegal operator in expression";
       throw err;
}

Expression* CompoundExp::getLHS()
{
    return lhs;
}

Expression* CompoundExp::getRHS()
{
    return rhs;
}

QString CompoundExp::getOperator()
{
    return op;
}

QString CompoundExp::getIdentifierName()
{
    return " ";
}





