#include "shuntingyard.h"


OperatorBase::OperatorBase(unsigned char tType, const QString& sym, bool binaryOrUnary, int opPrecedence, bool rightOrLeftAssociation, int argc)
    : type(tType), symbol(sym), binary(binaryOrUnary), precedence(opPrecedence), association(rightOrLeftAssociation), paramNum(argc)
{

}

QString OperatorBase::toString() const
{
    QString str;
    str += binary? 'b' : 'u';
    str += association? 'l' : 'r';
    str += symbol;
    return str;
}

int OperatorBase::comparePrecedence(const OperatorBase& other)
{
    return precedence > other.precedence ? 1 : other.precedence == precedence ? 0 : -1;
}

ASTNode::ASTNode(const QString& val, ASTNode* leftNode, ASTNode* rightNode) : value(val), left(leftNode), right(rightNode)
{

}

void ShuntingYard::initOperatorMap(const QList<AbstractToken>& input)
{


}
void ShuntingYard::init(const QList<AbstractToken>& input)
{
    // UNARY OPERATORS
    operators["u+"] = new OperatorBase(ARITHMETIC, "u+", false, 3, false, 1);
    operators["u-"] = new OperatorBase(ARITHMETIC, "u-", false, 3, false, 1);
    operators["u++"] = new OperatorBase(ARITHMETIC, "u++", false, 3, false, 1);
    operators["u--"] = new OperatorBase(ARITHMETIC, "u--", false, 3, false, 1);
    operators["u!"] = new OperatorBase(LOGICAL, "u!", false, 3, false, 1);
    operators["unot"] = new OperatorBase(LOGICAL, "unot", false, 3, false, 1);

    // ARITHMETIC OPERATORS
    operators["^"] = new OperatorBase(ARITHMETIC, "^", true, 4, false, 2);
    operators["*"] = new OperatorBase(ARITHMETIC, "*", true, 5, true, 2);
    operators["/"] = new OperatorBase(ARITHMETIC, "/", true, 5, true, 2);
    operators["%"] = new OperatorBase(ARITHMETIC, "%", true, 5, true, 2);
    operators["+"] = new OperatorBase(ARITHMETIC, "+", true, 6, true, 2);
    operators["-"] = new OperatorBase(ARITHMETIC, "-", true, 6, true, 2);

    // COMPARISON OPERATORS
    operators["<"] = new OperatorBase(COMPARISON, "<", true, 9, true, 2);
    operators[">"] = new OperatorBase(COMPARISON, ">", true, 9, true, 2);
    operators["<="] = new OperatorBase(COMPARISON, "<=", true, 9, true, 2);
    operators[">="] = new OperatorBase(COMPARISON, ">=", true, 9, true, 2);
    operators["=="] = new OperatorBase(COMPARISON, "==", true, 10, true, 2);
    operators["!="] = new OperatorBase(COMPARISON, "!=", true, 10, true, 2);

    // LOGICAL OPERATORS
    operators["&"] = new OperatorBase(LOGICAL, "&", true, 14, true, 2);
    operators["&&"] = new OperatorBase(LOGICAL, "&&", true, 14, true, 2);
    operators["and"] = new OperatorBase(LOGICAL, "&&", true, 14, true, 2);
    operators["|"] = new OperatorBase(LOGICAL, "|", true, 15, true, 2);
    operators["||"] = new OperatorBase(LOGICAL, "||", true, 15, true, 2);
    operators["or"] = new OperatorBase(LOGICAL, "||", true, 15, true, 2);
    operators["xor"] = new OperatorBase(LOGICAL, "||", true, 15, true, 2);

    // ASSIGNMENT OPERATORS
    operators["="] = new OperatorBase(ASSIGNMENT, "=", true, 16, false, 2);
    operators["+="] = new OperatorBase(ASSIGNMENT, "+=", true, 16, false, 2);
    operators["-="] = new OperatorBase(ASSIGNMENT, "-=", true, 16, false, 2);
    operators["*="] = new OperatorBase(ASSIGNMENT, "*=", true, 16, false, 2);
    operators["/="] = new OperatorBase(ASSIGNMENT, "/=", true, 16, false, 2);
    operators["%="] = new OperatorBase(ASSIGNMENT, "%=", true, 16, false, 2);





}
ShuntingYard::ShuntingYard()
{

}
void ShuntingYard::addNode(const QString& token)
{
    ASTNode* right = &outputQueue.back();
    outputQueue.removeLast();
    ASTNode* left = &outputQueue.back();
    outputQueue.removeLast();
    outputQueue.append(ASTNode(token, left, right));
}

QString ShuntingYard::convertToAst(const QList<AbstractToken>& input)
{
   // SAME AS REGULAR WIKIPEDIA CODE INSTEAD OF ADD TO OUTPUT STRING USE 'addNode' FUNCTION TO PLACE ON TREE.
    for (AbstractToken t : input)
    {
        switch(t.name)
        {
            case INTEGER:
            case REAL:
            case STRING:
                addNode(t.value);
            break;
            case IDENTIFIER:
            case LITERAL:
                // Grab value of identifier/literal and store that instread.
                // For now just add the value
                addNode(t.value);
            break;
            case FUNCTION:
                operatorStack.push(t.value);
                break;
            case OPERATOR_BINARY:
            case OPERATOR_UNARY:
                // Operator while loop


            break;
            case SEPERATOR_LEFT:
                operatorStack.push(t.value);
            break;
            case SEPERATOR_RIGHT:
                // Right seperator loop
            break;
        }
    }

    return "NIGGER";

}
