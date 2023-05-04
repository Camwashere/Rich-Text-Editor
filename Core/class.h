#ifndef CLASS_H
#define CLASS_H
#include "function.h"

class Class : public Variable
{
    private:
        QHash<unsigned int, Variable> variables;
        QHash<unsigned int, Function> functions;
    public:
        Class();
};

#endif // CLASS_H
