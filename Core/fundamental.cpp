#include "fundamental.h"

Fundamental::Fundamental() : type(NONE)
{

}
Fundamental::Fundamental(double val) : type(NUMBER), var(QString::number(val))
{

}
Fundamental::Fundamental(int val) : type(NUMBER), var(QString::number(val))
{


}

Fundamental::Fundamental(bool val) : type(BOOL), var(val? "true" : "false")
{

}
Fundamental::Fundamental(const QString& val) : type(TEXT), var(val)
{

}
Fundamental::Fundamental(const char* val) : type(TEXT), var(val)
{

}

Fundamental::Fundamental(char val) : type(TEXT), var(val)
{

}

int Fundamental::asInt()const
{
    return var.toInt();
}
double Fundamental::asDouble()const
{
    return var.toDouble();
}
QChar Fundamental::asChar()const
{
    return var.toChar();
}
bool Fundamental::asBool()const
{
    return var.toBool();
}

Fundamental::operator bool() const
{
    return asBool();
}
Fundamental::operator QChar() const
{
    return asChar();
}
Fundamental::operator int() const
{
    return asInt();
}
Fundamental::operator double() const
{
    return asDouble();
}
Fundamental::operator QString() const
{
    return var.toString();
}



