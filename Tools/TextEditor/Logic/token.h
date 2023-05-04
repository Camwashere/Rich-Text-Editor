#ifndef TOKEN_H
#define TOKEN_H
#include <QString>
#include <QList>
#include <QMap>


enum TokenType
{
    NONE=0,
    NUMBER,
    SEPERATOR,
    OPERATOR,
    FUNCTION,
    VARIABLE,
    LITERAL,
    SEPERATOR_LEFT,
    SEPERATOR_RIGHT,
};



class AbstractToken
{
private:
    static QHash<QString, TokenType> INIT_KEYS();
public:
    static bool IsNumber(const QString& str);
    static QHash<QString, TokenType> KEY_MAPPINGS;
    static TokenType GetType(const QString& str);
protected:
    TokenType type;
    QString value;

public:
    AbstractToken(TokenType type, const QString&  vValue);

public:
    QString getValue() const {return this->value;}
    const TokenType getType() const {return this->type;}



};



class NumberToken : public AbstractToken
{
public:
    static bool IsNumber(const QString& str);
    static double ToDouble(const QString& str);
private:
    bool isDouble;
public:
    NumberToken(double value);
    bool IsDouble()const{return isDouble;}
};


class OperatorBaseToken : public AbstractToken
{
protected:
    bool left;
    int precedence;

protected:
    OperatorBaseToken(TokenType type, const QString& value, int precendenceVal=-1, bool isLeft=false);

public:
    int getPrecedence(){return precedence;}
    bool isLeft()const{return left;}
    bool isRight()const{return !left;}


};

class OperatorToken : public OperatorBaseToken
{

public:
    static bool IsOperator(const QString&  c);
    static double Solve(QChar op, double num1, double num2);


public:
    OperatorToken(const QString& value);


};

class SeperatorToken : public OperatorBaseToken
{
public:
    static bool IsSeperator(const QString& c);
    static bool IsSeperator_Left(const QString& c);
    static bool IsSeperator_Right(const QString& c);

public:
    SeperatorToken(QChar value);

};

class FunctionToken : public OperatorBaseToken
{
private:
    static const QString MATH_FUNCS[];
public:
    static bool IsFunction(const QString& str);
    static double Execute(const QString& func, double param);

public:
    FunctionToken(const QString& value);
};

#endif // TOKEN_H
