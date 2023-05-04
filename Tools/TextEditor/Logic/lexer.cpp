#include "lexer.h"



std::string AbstractToken::toString()
{
    return (Lex::lexToString(name) + ":" + value).toStdString();

}

QString AbstractToken::toHash() const
{
    if (name == OPERATOR_UNARY)
    {
        return 'u' + value;
    }
    else
    {
        return value;
    }

}
bool AbstractToken::isOperator() const
{
    switch(name)
    {
        case OPERATOR_UNARY:
        case OPERATOR_BINARY:
            return true;
        default:
            return false;
    }
}
bool AbstractToken::isNumber() const
{
    switch(name)
    {
        case INTEGER:
        case REAL:
            return true;
        default:
            return false;
    }
}



void Lex::populateInitialStringMap()
{
    //****** OPERATORS ******/
    // UNARY OPERATORS
    stringMap["++"] = OPERATOR_UNARY;
    stringMap["--"] = OPERATOR_UNARY;

    // COMPARISON OPERATORS
    stringMap["=="] = OPERATOR_BINARY;
    stringMap["!="] = OPERATOR_BINARY;
    stringMap["<="] = OPERATOR_BINARY;
    stringMap[">="] = OPERATOR_BINARY;

    // LOGICAL OPERATORS
    stringMap["&&"] = OPERATOR_BINARY;
    stringMap["||"] = OPERATOR_BINARY;
    stringMap["and"] = OPERATOR_BINARY;
    stringMap["or"] = OPERATOR_BINARY;
    stringMap["xor"] = OPERATOR_BINARY;

    // ASSIGNMENT OPERATORS
    stringMap["+="] = OPERATOR_BINARY;
    stringMap["-="] = OPERATOR_BINARY;
    stringMap["*="] = OPERATOR_BINARY;
    stringMap["/="] = OPERATOR_BINARY;
    stringMap["%="] = OPERATOR_BINARY;










    /****** FUNCTIONS ******/
    // BASE FUNCTIONS
    stringMap["sin"] = FUNCTION;
    stringMap["cos"] = FUNCTION;
    stringMap["tan"] = FUNCTION;
    stringMap["csc"] = FUNCTION;
    stringMap["sec"] = FUNCTION;
    stringMap["cot"] = FUNCTION;
    stringMap["arcsin"] = FUNCTION;
    stringMap["arccos"] = FUNCTION;
    stringMap["arctan"] = FUNCTION;
    stringMap["arccsc"] = FUNCTION;
    stringMap["arcsec"] = FUNCTION;
    stringMap["arccot"] = FUNCTION;

    stringMap["sqrt"] = FUNCTION;
    stringMap["xroot"] = FUNCTION;

    stringMap["floor"] = FUNCTION;
    stringMap["ceiling"] = FUNCTION;
    stringMap["abs"] = FUNCTION;
    stringMap["round"] = FUNCTION;
    stringMap["random"] = FUNCTION;

    // LITERALS
    stringMap["e"] = LITERAL;
    stringMap["pi"] = LITERAL;
    stringMap["gr"] = LITERAL;





}

QString Lex::lexToString(unsigned char x)
{
    switch(x)
    {
        case REJECT:
        return "Reject";
        case INTEGER:
            return "Integer";
        case REAL:
            return "Real";
        case OPERATOR:
            return "Operator_Generic";
        case OPERATOR_UNARY:
            return "Operator_Unary";
        case OPERATOR_BINARY:
            return "Operator_Binary";
        case SEPERATOR_LEFT:
            return "Seperator_Left";
        case SEPERATOR_RIGHT:
            return "Seperator_Right";
        case DELIM:
            return "Delim";
        case IDENTIFIER:
            return "Identifier";
        case FUNCTION:
            return "Function";
        case LITERAL:
            return "Literal";
        case STRING:
            return "String";
        case SPACE:
            return "Space";
        default:
            return "Unkown";
    }
}

void Lex::makeRejectRow()
{
    QList<unsigned char> row;
    row.reserve(9);
    row.append(REJECT);
    for (unsigned char i=1; i<UNKNOWN; i++)
    {
        row.append(i);
    }
    map[REJECT] = row;
}
void Lex::makeRow(unsigned char name, const QHash<unsigned char, unsigned char>& approved)
{
    QList<unsigned char> row;
    row.reserve(9);
    row.append(name);
    for (unsigned char i=1; i < UNKNOWN; i++)
    {
        row.append(approved.value(i, REJECT));


    }


    map[name] = row;

}
Lex::Lex()
{
    populateInitialStringMap();
    makeRejectRow();


    makeRow(INTEGER, {{INTEGER, INTEGER}, {REAL, REAL}});
    makeRow(REAL, {{INTEGER, REAL}, {REAL, UNKNOWN}});
    makeRow(OPERATOR, {{STRING, STRING}, {OPERATOR, OPERATOR}});
    makeRow(SEPERATOR_LEFT, {{}});
    makeRow(SEPERATOR_RIGHT, {{}});
    makeRow(DELIM, {{}});
    makeRow(STRING, {{STRING, STRING}, {INTEGER, STRING}});
    makeRow(IDENTIFIER, {{STRING, IDENTIFIER}});
    makeRow(SPACE, {{}});
    makeRow(UNKNOWN, {{INTEGER, UNKNOWN}, {REAL, UNKNOWN}, {OPERATOR, UNKNOWN}, {}});


}

unsigned char Lex::getColumn(QChar c)
{
    if (c.isDigit())
    {
        return INTEGER;
    }
    if (c.isSpace())
    {
        return SPACE;
    }
    if (c.isLetter())
    {
        return STRING;
    }
    switch(c.unicode())
    {
        case '.':
            return REAL;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%':
        case '!':
        case '=':
        case '<':
        case '>':
        case '&':
        case '|':
            return OPERATOR;
        case '(':
        case '[':
        case '{':
            return SEPERATOR_LEFT;
        case ')':
        case ']':
        case '}':
            return SEPERATOR_RIGHT;
        case ',':
        case ';':
        case ':':
            return DELIM;
        case '$':
            return IDENTIFIER;
        default:
            return UNKNOWN;
            break;
    }


}

unsigned char Lex::evaluateOperatorHelper(const QString& op)
{
    if (op.length() == 1)
    {
        switch(op[0].unicode())
        {
            case '!':
                return OPERATOR_UNARY;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case '%':
            case '=':
            case '<':
            case '>':
            case '&':
            case '|':
                return OPERATOR_BINARY;
            default:
                return UNKNOWN;
        }
    }
    else
    {
        if (op == "++" || op == "--")
        {
            return OPERATOR_UNARY;
        }
        else
        {
            return stringMap.value(op, UNKNOWN);

        }

    }
}
unsigned char Lex::evaluateOperator(const QString& op, const QList<AbstractToken>& tokens)
{
    if (tokens.isEmpty())
    {
        return OPERATOR_UNARY;
    }
    else
    {
        switch(tokens.back().name)
        {
            case OPERATOR_BINARY:
            case SEPERATOR_LEFT:
            case DELIM:
                return OPERATOR_UNARY;
            default:
                return evaluateOperatorHelper(op);

        }

    }



}
QList<AbstractToken> Lex::toTokens(const QString& expression)
{

    QList<AbstractToken> tokens;
    AbstractToken access;
    QChar currentChar = ' ';
    unsigned char col = REJECT;
    unsigned char currentState = REJECT;
    unsigned char prevState = REJECT;
    QString currentValue;
    for (int i=0; i<expression.length();)
    {
        currentChar = expression[i];
        col = getColumn(currentChar);
        currentState = map[currentState].value(col);



        if (currentState == REJECT)
        {
            if (prevState != SPACE)
            {
                access.value = currentValue;

                if (prevState == STRING)
                {
                    access.name = stringMap.value(currentValue, UNKNOWN);

                }
                else if (prevState == OPERATOR)
                {
                    access.name = evaluateOperator(currentValue, tokens);

                }
                else
                {
                    access.name = prevState;
                }
                tokens.append(access);

            }
            currentValue = "";
        }
        else
        {
            currentValue.append(currentChar);

            ++i;
        }
        prevState = currentState;


    }


    if (currentState != SPACE && !currentValue.isEmpty())
    {
        access.value = currentValue;
        if (currentState == STRING)
        {
            access.name = stringMap.value(currentValue, UNKNOWN);

        }
        else if (currentState == OPERATOR)
        {
            access.name = evaluateOperator(currentValue, tokens);
        }
        else
        {
            access.name = currentState;
        }

        tokens.append(access);
    }
    return tokens;
}
