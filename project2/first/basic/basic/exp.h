/*
 * File: exp.h
 * -----------
 * This interface defines a class hierarchy for arithmetic expressions.
 */

#ifndef EXP_H
#define EXP_H

#include <string>
#include <map>
#include "tokenizer.h"
# include "evalstate.h"



/* Forward reference */

class EvaluationContext;

/*
 * Type: ExpressionType
 * --------------------
 * This enumerated type is used to differentiate the three different
 * expression types: CONSTANT, IDENTIFIER, and COMPOUND.
 */

enum ExpressionType { CONSTANT, IDENTIFIER, COMPOUND };
/*
 * Class: Expression
 * -----------------
 * This class is used to represent a node in an expression tree.
 * Expression itself is an abstract class.  Every Expression object
 * is therefore created using one of the three concrete subclasses:
 * ConstantExp, IdentifierExp, or CompoundExp.
 */

class Expression {

public:

   Expression();

   virtual ~Expression();
   virtual int eval(evalstate &Vars) = 0;
   virtual QString toQString() = 0;
   virtual ExpressionType type() = 0;

/* Getter methods for convenience */

   virtual int getConstantValue();
   virtual QString getIdentifierName();
   virtual QString getOperator();
   virtual Expression *getLHS();
   virtual Expression *getRHS();

};
/*
 * Class: ConstantExp
 * ------------------
 * This subclass represents a constant integer expression.
 */

class ConstantExp: public Expression {

public:

   ConstantExp(int val);
   virtual~ConstantExp();

   virtual int eval(evalstate &Vars);
   virtual QString toQString();
   virtual ExpressionType type();

   virtual int getConstantValue();

private:

   int value;

};
/*
 * Class: IdentifierExp
 * --------------------
 * This subclass represents a expression corresponding to a variable.
 */

class IdentifierExp: public Expression {

public:

   IdentifierExp(QString name);
   virtual~IdentifierExp();
   virtual int eval(evalstate &Vars);
   virtual QString toQString();
   virtual ExpressionType type();

   virtual QString getIdentifierName();

private:

   QString name;

};
/*
 * Class: CompoundExp
 * ------------------
 * This subclass represents a compound expression.
 */

class CompoundExp: public Expression {

public:

   CompoundExp(string op, Expression *lhs, Expression *rhs);
   virtual ~CompoundExp();

   virtual int eval(evalstate &Vars);
   virtual QString toQString();
   virtual ExpressionType type();

   virtual QString getOperator();
   virtual Expression *getLHS();
   virtual Expression *getRHS();

private:

   QString op;
   Expression *lhs, *rhs;

};
/*
 * Class: EvaluationContext
 * ------------------------
 * This class encapsulates the information that the evaluator needs to
 * know in order to evaluate an expression.
 */



#endif








