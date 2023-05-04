#ifndef SHUNTINGYARD_H
#define SHUNTINGYARD_H
#include "lexer.h"
#include <QStack>


enum OperatorType
{
    ARITHMETIC=1,
    COMPARISON,
    LOGICAL,
    ASSIGNMENT,

};



class OperatorBase
{
    private:
        unsigned char type;
        QString symbol;
        bool binary;
        int precedence;
        bool association;
        int paramNum;

    public:
        OperatorBase(unsigned char tType, const QString& sym, bool binaryOrUnary,
                     int opPrecedence, bool rightOrLeftAssociation, int argc);

        bool isRightAssociative() const {return association;}
        bool isLeftAssociative() const {return !association;}
        bool isBinary() const {return binary;}
        bool isUnary() const {return !binary;}
        QString getSymbol() const {return symbol;}
        unsigned char getType()const{return type;}
        int getPrecedence()const{return precedence;}
        int getParamNum()const{return paramNum;}

        int comparePrecedence(const OperatorBase& other);


        QString toString() const;




};

class FunctionBase
{



};



class ASTNode
{
    private:
        QString value;
        ASTNode* left;
        ASTNode* right;

    public:
        ASTNode(const QString& val, ASTNode* leftNode, ASTNode* rightNode);

        QString getValue()const{return value;}
        ASTNode* getLeft(){return left;}
        ASTNode* getRight(){return right;}
};

class ShuntingYard
{
    private:
        QHash<QString, OperatorBase*> operators;

        QList<ASTNode> outputQueue;
        QStack<QString> operatorStack;

        void initOperatorMap(const QList<AbstractToken>& input);
        void addNode(const QString& token);



    public:
        ShuntingYard();
        void init(const QList<AbstractToken>& input);


        QString convertToAst(const QList<AbstractToken>& input);




};

#endif // SHUNTINGYARD_H
