#include "variable.h"



Variable::Variable(const QString& varName, const Fundamental& varValue) : Fundamental(varValue), name(varName)
{

}
/*
template <typename V>
IdManager AbstractVariable<V>::idManager;

template <typename V>
AbstractVariable<V>::AbstractVariable(unsigned char varType,  ValueType varValue) : type(varType), value(varValue), id(AbstractVariable::idManager.ASSIGN())
{

}

template<typename V>
AbstractVariable<V>::~AbstractVariable()
{
    AbstractVariable<V>::idManager.FREE(id);
}

template <typename V>
bool AbstractVariable<V>::operator == (const AbstractVariable& other) const
{
    return type == other.type && value == other.value;
}

template <typename V>
bool AbstractVariable<V>::operator == (ValueType other) const
{
    return value == other;
}
template<typename V>
void AbstractVariable<V>::operator = (const AbstractVariable& other)
{
    value = other.value;
}
template<typename V>
void AbstractVariable<V>::operator = (ValueType other)
{
    value = other;
}


NumberVariable::NumberVariable() : AbstractVariable(NUMBER, 0)
{

}
NumberVariable::NumberVariable(int varValue) : AbstractVariable<double>(NUMBER, (double)varValue)
{

}

NumberVariable::NumberVariable(double varValue) : AbstractVariable<double>(NUMBER, varValue)
{

}


long NumberVariable::operator!()
{
    int n = (int)value;
    long factorial = 1.0;
    if (n < 0)
    {
        return 0;
    }
    else
    {
        for (int i=1; i<=n; ++i)
        {
            factorial *= i;
        }
    }
    return factorial;
}
QString NumberVariable::valueAsString()const
{
    return QString::number(value);
}



BoolVariable::BoolVariable( bool varValue) : AbstractVariable<bool>(BOOL, varValue)
{

}
TextVariable::TextVariable() : AbstractVariable<QString>(TEXT, "")
{

}
TextVariable::TextVariable(char varValue) : AbstractVariable<QString>(TEXT, QChar(varValue))
{

}
TextVariable::TextVariable(double varValue) : AbstractVariable<QString>(TEXT, QString::number(varValue))
{

}
TextVariable::TextVariable(const QString& varValue) : AbstractVariable<QString>(TEXT, varValue)
{

}
TextVariable::TextVariable(const char* varValue) : AbstractVariable<QString>(TEXT, varValue)
{

}

QChar TextVariable::getFirst()const
{
    return value[0];
}
QChar TextVariable::getLast()const
{

    return value[value.length()-1];
}
QString TextVariable::toCapitalized() const
{
    QString val;
    val.append(value[0].toUpper());
    for (int i=1; i<value.length(); i++)
    {
        val.append(value[i].toLower());
    }
    return val;
}
QString TextVariable::toUpper() const
{
    return value.toUpper();
}
QString TextVariable::toLower() const
{
    return value.toLower();
}
QString TextVariable::toInvertCase() const
{
    QString val;

    for (int i=0; i<value.length(); i++)
    {
        if (value[i].isLower())
        {
            val.append(value[i].toUpper());
        }
        else if (value[i].isUpper())
        {
            val.append(value[i].toLower());
        }
        else
        {
            val.append(value[i]);
        }
    }
    return val;
}
qsizetype TextVariable::length() const
{
    return value.length();
}
*/




