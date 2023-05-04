#include "token.h"
#include <math.h>
#include <QHash>

QHash<QString, TokenType> AbstractToken::INIT_KEYS()
{
    QHash<QString, TokenType> map;




    // OPERATORS
    map["+"] = TokenType::OPERATOR;
    map["-"] = TokenType::OPERATOR;
    map["*"] = TokenType::OPERATOR;
    map["/"] = TokenType::OPERATOR;
    map["^"] = TokenType::OPERATOR;
    map["++"] = TokenType::OPERATOR;
    map["--"] = TokenType::OPERATOR;
    map["="] = TokenType::OPERATOR;
    map["=="] = TokenType::OPERATOR;

    // SEPERATORS
    map["("] = TokenType::SEPERATOR_LEFT;
    map["["] = TokenType::SEPERATOR_LEFT;
    map["{"] = TokenType::SEPERATOR_LEFT;
    map[")"] = TokenType::SEPERATOR_RIGHT;
    map["}"] = TokenType::SEPERATOR_RIGHT;
    map["]"] = TokenType::SEPERATOR_RIGHT;
    map[","] = TokenType::SEPERATOR;
    map[";"] = TokenType::SEPERATOR;
    map[":"] = TokenType::SEPERATOR;

    // FUNCTIONS
    map["sin"] = TokenType::FUNCTION;
    map["cos"] = TokenType::FUNCTION;
    map["tan"] = TokenType::FUNCTION;
    map["sec"] = TokenType::FUNCTION;
    map["csc"] = TokenType::FUNCTION;
    map["cot"] = TokenType::FUNCTION;
    map["sind"] = TokenType::FUNCTION;
    map["cosd"] = TokenType::FUNCTION;
    map["tand"] = TokenType::FUNCTION;
    map["secd"] = TokenType::FUNCTION;
    map["cscd"] = TokenType::FUNCTION;
    map["cotd"] = TokenType::FUNCTION;
    map["log"] = TokenType::FUNCTION;
    map["ln"] = TokenType::FUNCTION;
    map["sqrt"] = TokenType::FUNCTION;

    // LITERALS
    map["pi"] = TokenType::LITERAL;
    map["e"] = TokenType::LITERAL;
    map["gr"] = TokenType::LITERAL;

    return map;


}




QHash<QString, TokenType> AbstractToken::KEY_MAPPINGS = AbstractToken::INIT_KEYS();


AbstractToken::AbstractToken(TokenType tType, const QString& vValue) : type(tType), value(vValue)
{

}

bool AbstractToken::IsNumber(const QString& str)
{
    QChar c = str[0];
    if (c.isDigit() || c == '.')
    {
        for (int i=0; i<str.length(); i++)
        {
            if (!(str[i].isDigit() || str[i] == '.'))
            {
                return false;
            }
        }
        return true;
    }
    return false;


}

TokenType AbstractToken::GetType(const QString& str)
{

    TokenType t = KEY_MAPPINGS[str];
    if (t)
    {
        return t;
    }
    else if (str[0] == '$')
    {
        return TokenType::VARIABLE;
    }
    else
    {
        return IsNumber(str)? TokenType::NUMBER : TokenType::NONE;
    }
}





NumberToken::NumberToken(double value) : AbstractToken(TokenType::NUMBER, QString::number(value)), isDouble(true)
{

}

OperatorBaseToken::OperatorBaseToken(TokenType type, const QString& value, int precedenceVal, bool isLeft) : AbstractToken(type, value), precedence(precedenceVal),  left(isLeft)
{

}
bool OperatorToken::IsOperator(const QString& c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^');
}
double OperatorToken::Solve(QChar op, double num1, double num2)
{
    switch(op.unicode())
    {
    case '+':
        return num1+num2;
    case '-':
        return num1-num2;
    case '*':
        return num1*num2;
    case '/':
        return num1/num2;
    case '^':
        return pow(num1, num2);
    default:
        throw std::invalid_argument("Invalid Argument for OperatorToken::Solve");

    }



}
OperatorToken::OperatorToken(const QString& value) : OperatorBaseToken(TokenType::OPERATOR, value)
{
    if (value == "+" || value == "-")
    {
        left = true;
        precedence = 1;
    }
    else if (value == "*" || value == "/" || value == "%")
    {
        left = true;
        precedence=2;
    }
    else if (value == "^")
    {
        precedence=3;
    }
}

bool SeperatorToken::IsSeperator(const QString& c)
{
    return (c == '{' || c == '(' || c == '[' || c == '}' || c == ')' || c == ']');
}
bool SeperatorToken::IsSeperator_Left(const QString& c)
{
    return (c == '{' || c == '(' || c == '[');
}
bool SeperatorToken::IsSeperator_Right(const QString& c)
{
    return (c == '}' || c == ')' || c == ']');
}
SeperatorToken::SeperatorToken(QChar value) : OperatorBaseToken(TokenType::SEPERATOR, value, -1, (value == '(' || value == '{' || value == '['))
{

}


const QString FunctionToken::MATH_FUNCS[] = {"sin", "cos", "tan", "log", "ln"};

bool FunctionToken::IsFunction(const QString& str)
{
    for (QString s : FunctionToken::MATH_FUNCS)
    {
        if (str == s)
        {
            return true;
        }
    }
    return false;
}
double FunctionToken::Execute(const QString& func, double param)
{
    if (func == "sin")
    {
        return sin(param);
    }
    else if (func == "cos")
    {
        return cos(param);
    }
    else
    {
        return 0;
    }
}

FunctionToken::FunctionToken(const QString& value) : OperatorBaseToken(TokenType::FUNCTION, value)
{

}


