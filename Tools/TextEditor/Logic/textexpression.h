#ifndef TEXTEXPRESSION_H
#define TEXTEXPRESSION_H

#include <QString>
#include <QStack>
#include <QQueue>
#include <QList>
#include "Tools/TextEditor/Logic/token.h"


class TextExpression
{

private:
    QStack<OperatorBaseToken> operatorStack;
    QList<QString> outputQueue;
    QList<QString> outputTokens;
    QString output;






public:
    TextExpression();

public:
    QString convertToPostfix(const QString& expression);
    double solvePostfix(const QString& postfix);




};


#endif // TEXTEXPRESSION_H
