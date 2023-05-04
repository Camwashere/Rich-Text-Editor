#include "textexpression.h"
#include <QJSEngine>
#include <iostream>
#include <math.h>
#include <sstream>
#include <QStringTokenizer>
#include <QRegularExpression>
#include <QTextStream>
#include <assert.h>



// ((8+2)*5 + (25+25))/((2.5+2.5)*2)
QList<QString> toTokens(const QString& expression)
{
    QList<QString> list;
    QString current;
    for (int i=0; i<expression.length(); i++)
    {
        // Number case
        if (expression[i].isDigit())
        {
            current.append(expression[i]);
            if (i+1 == expression.length())
            {
                list.append(current);
            }
            else if (!(expression[i+1].isDigit() || expression[i+1] == '.'))
            {
                list.append(current);
                current.clear();
            }
        }
        else if (expression[i] == '.' && (expression[i+1].isDigit()))
        {
            current.append('.');
        }
        else
        {
            // Operator case
            if (OperatorToken::IsOperator(expression[i]))
            {
                list.append(QString(expression[i]));
            }
            // Seperator case
            else if (SeperatorToken::IsSeperator(expression[i]))
            {
                list.append(QString(expression[i]));
            }
            // function/literal case
            else if (expression[i].isLetter())
            {
                QString func;
                while(expression[i].isLetter())
                {
                    func.append(expression[i]);
                    i++;
                }
                if (FunctionToken::IsFunction(func))
                {
                    list.append(func);
                }

            }

        }
    }

    return list;

}
QString TextExpression::convertToPostfix(const QString& expression)
{

    QList<QString> list = toTokens(expression);

    std::cout << std::endl;


    for (QString s : list)
    {
        if (AbstractToken::IsNumber(s))
        {
            outputQueue.append(s);
        }
        else if (FunctionToken::IsFunction(s))
        {

            operatorStack.push(FunctionToken(s));

        }
        else if (OperatorToken::IsOperator(s))
        {
            OperatorToken o1 = OperatorToken(s);
            while((!operatorStack.isEmpty()) && (operatorStack.top().getType() == TokenType::OPERATOR && operatorStack.top().isLeft())  &&
                  (operatorStack.top().getPrecedence() > o1.getPrecedence() ||
                   (operatorStack.top().getPrecedence() == o1.getPrecedence() && o1.isLeft())))
            {
                outputQueue.append(operatorStack.pop().getValue());
            }
            operatorStack.push(o1);

        }
        else if (SeperatorToken::IsSeperator(s))
        {
            SeperatorToken seperator(s[0]);
            if (seperator.isLeft())
            {
                operatorStack.push(seperator);
            }
            else
            {
                while(! SeperatorToken::IsSeperator_Left(operatorStack.top().getValue()))
                {
                    //assert(! operatorStack.isEmpty());
                    outputQueue.append(operatorStack.pop().getValue());
                    if (operatorStack.isEmpty())
                    {
                        break;
                    }
                }

                if (!operatorStack.isEmpty() && SeperatorToken::IsSeperator_Left(operatorStack.top().getValue()))
                {
                    operatorStack.pop();
                }

                if (! operatorStack.isEmpty())
                {
                    if (operatorStack.top().getType() == TokenType::FUNCTION)
                    {
                        outputQueue.append(operatorStack.pop().getValue());
                    }
                }

            }
        }
    }


    while (! operatorStack.isEmpty())
    {
        outputQueue.append(operatorStack.pop().getValue());
    }
    for (QString s : outputQueue)
    {
        output.append(s + ",");

    }

    return output;
}




double TextExpression::solvePostfix(const QString& postfix)
{

        QStringList list = postfix.split(',');
        QStack<double> nums;
        double res;

        for(int i=0; i<list.length(); i++)
        {
            QString token = list[i];
            if (AbstractToken::IsNumber(token))
            {
                nums.push(token.toDouble());

            }
            else if (OperatorToken::IsOperator(token))
            {
                double num2 = nums.top();
                nums.pop();
                double num1 = 0;
                if (!nums.empty())
                {
                    num1 = nums.top();
                    nums.pop();
                }
                res = OperatorToken::Solve(token[0], num1, num2);

                nums.push(res);

            }
            else if (FunctionToken::IsFunction(token))
            {
                double num2 = nums.top();
                nums.pop();
                res = FunctionToken::Execute(token, num2);
                std::cout << "Function result: " << res << std::endl;
                nums.push(res);
            }
        }

        return res;





}

TextExpression::TextExpression()
{
    QString expression = "5*2 + (2.5+2.5)^2+sin(90)"; //35
    std::cout << "Original: " << expression.toStdString() << std::endl;
    QString postfix = convertToPostfix(expression);
    std::cout << postfix.toStdString() << std::endl;
    double result = solvePostfix(postfix);
    std::cout << "Result: " << result << std::endl;
    //std::cout << "Result: " << result << std::endl;


}


