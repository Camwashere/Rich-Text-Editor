#ifndef LEXER_H
#define LEXER_H
#include <QHash>
#include <QList>
#include <iostream>


/*
 * Enum representing the different possible states to switch between.
 *  Should in theory be able to handle any given char value
*/
enum LEX_TYPE
{
    REJECT=0,
    INTEGER,
    REAL,
    OPERATOR,
    OPERATOR_UNARY,
    OPERATOR_BINARY,
    SEPERATOR_LEFT,
    SEPERATOR_RIGHT,
    DELIM,
    IDENTIFIER,
    FUNCTION,
    LITERAL,
    STRING,
    SPACE,
    UNKNOWN,
};




// A struct holding the extracted token type and string value of an expression
struct AbstractToken
{
    unsigned char name;
    QString value;

    std::string toString();
    QString toHash() const;
    bool isOperator() const;
    bool isNumber() const;

};



/*
 * The primary finite state machine/tokenizer for parsing equations.
 * Can potentially be made static in the future.
 */
class Lex
{

private:
    // State table of each possible state and all their transitions
    QHash<unsigned char, QList<unsigned char>> map;
    QHash<QString, unsigned char> stringMap;

    void populateInitialStringMap();

    void makeRejectRow();

    // Helper function for filling out all the rows to reduce tedium of manually writing it. Especially if future changes are made
    void makeRow(unsigned char name, const QHash<unsigned char, unsigned char>& approved);

    // Returns the state transition associated with the character 'c'
    unsigned char getColumn(QChar c);


    unsigned char evaluateOperatorHelper(const QString& op);
    unsigned char evaluateOperator(const QString& op, const QList<AbstractToken>& tokens);





public:
    Lex();

    // Seperate expression into seperate tokens for further evaluation
    QList<AbstractToken> toTokens(const QString& expression);


public:
    // Debug function for producing a human readable string from the given LEX_TYPE
    static QString lexToString(unsigned char x);
};





#endif // LEXER_H
