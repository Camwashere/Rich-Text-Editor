#ifndef FUNCTION_H
#define FUNCTION_H
#include <QString>
#include "variable.h"
#include<any>


class Function : public Tracked
{

    private:
        unsigned int rtnType;
        QList<Variable> params;
        QString name;


    public:
        Function(const QString& funcName, unsigned int retunType, const Variable& parameters...);

        unsigned int getReturnType()const{return rtnType;}
        QString getName()const{return name;}
        unsigned int getNumberOfParams()const{return params.length();}
        QList<Variable> getParams()const{return params;}
};








#endif // FUNCTION_H
