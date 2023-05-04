#ifndef VARIABLE_H
#define VARIABLE_H
#include "fundamental.h"
#include "id.h"

class Variable : public Fundamental, public Tracked
{
    private:
        const QString name;


    public:
        Variable(const QString& varName, const Fundamental& varValue);
        const QString& getName()const{return name;}






};

/*
template <typename V>
class AbstractVariable
{
        using ValueType = std::conditional_t<sizeof(V) <= 2*sizeof(void*), V, const V&>;

    private:
        static IdManager idManager;
        static QHash<unsigned int, QColor> variableColors;
    protected:
        V value;
        const unsigned char type;
        const unsigned int id;



    public:
        AbstractVariable(unsigned char varType,  ValueType varValue);
        virtual ~AbstractVariable();


        void setValue(ValueType val){value=val;}
        ValueType getValue() const {return value;}
        unsigned char getType() const {return type;}
        QColor getColor() const {return AbstractVariable::variableColors.value(type);}

    public:
        virtual V operator + (ValueType other)const{return value;};
        virtual V operator - (ValueType other)const{return value;};
        virtual V operator * (ValueType other)const{return value;};
        virtual V operator / (ValueType other)const{return value;};
        virtual V operator % (ValueType other)const{return value;};

        // Prefix
        virtual AbstractVariable<V>& operator-(){return *this;};
        virtual AbstractVariable<V>& operator+(){return *this;};
        virtual AbstractVariable<V>& operator--(){return *this;};
        virtual AbstractVariable<V>& operator++(){return *this;};


        // Postfix
        virtual AbstractVariable<V>& operator--(int){return *this;};
        virtual AbstractVariable<V>& operator++(int){return *this;};

        virtual bool operator == (const AbstractVariable& other)const;
        virtual bool operator == (ValueType other) const;
        virtual bool operator != (const AbstractVariable& other) const {return !(*this==other);}
        virtual bool operator != (ValueType other) const {return !(*this == other);}
        virtual void operator = (const AbstractVariable& other);
        virtual void operator = (ValueType other);



    public:
        virtual QString valueAsString() const=0;

};

class NumberVariable : public AbstractVariable<double>
{
    public:
        NumberVariable();
        NumberVariable(double val);
        NumberVariable(int val);



        QString valueAsString()const;
        std::string toString()const{return valueAsString().toStdString();};

    public:
        double operator + (double other){return value + other;};
        double operator - (double other){return value - other;};
        double operator * (double other){return value * other;};
        double operator / (double other){return value / other;};
        int operator % (double other){return (int)value % (int)other;};

        double operator + (int other){return value + other;};
        double operator - (int other){return value - other;};
        double operator * (int other){return value * other;};
        double operator / (int other){return value / other;};
        int operator % (int other){return (int)value % other;};

        // Factorial (if value > 0, otherwise return 0)
        long operator !();

        NumberVariable& operator-(){value *= -1; return *this;};
        NumberVariable& operator+(){value = abs(value); return *this;};
        NumberVariable& operator --(){--value; return *this;};
        NumberVariable& operator ++(){++value; return *this;};

        NumberVariable& operator++(int){value++; return *this;}
        NumberVariable& operator--(int){value--; return *this;}

        void operator+=(const NumberVariable& other){value+=other.value;}
        void operator-=(const NumberVariable& other){value-=other.value;}
        void operator*=(const NumberVariable& other){value*=other.value;}
        void operator/=(const NumberVariable& other){value/=other.value;}
        void operator%=(const NumberVariable& other){int i = value; i %=(int)other.value; value = i;}

        friend bool operator<(const NumberVariable& left, const NumberVariable& right){return left.value < right.value;}
        friend bool operator<=(const NumberVariable& left, const NumberVariable& right){return left.value <= right.value;}
        friend bool operator>(const NumberVariable& left, const NumberVariable& right){return left.value >= right.value;}
        friend bool operator>=(const NumberVariable& left, const NumberVariable& right){return left.value >= right.value;}




        operator double()const{return value;}
};



class BoolVariable : public AbstractVariable<bool>
{
    public:
        BoolVariable(bool varValue=false);

    public:
        QString valueAsString()const{return getValue()? "True" : "False";}
        bool operator !(){return !value;}


        operator bool()const{return value;}
};

class TextVariable : public AbstractVariable<QString>
{
    public:
        TextVariable();
        TextVariable(char varValue);
        TextVariable(double varValue);
        TextVariable(const QString& varValue);
        TextVariable(const char* varValue);






        QString valueAsString()const{return getValue();}

    public:
        QChar getFirst()const;
        QChar getLast()const;
        QString toCapitalized()const;
        QString toLower()const;
        QString toUpper()const;
        QString toInvertCase()const;
        qsizetype length() const;
        bool isEmpty() const {return value.isEmpty();}
        bool isChar()const{return value.length()==1;}



    public:
        QString operator + (const QString& other){return value + other;}
        QString operator + (QChar c){return value + c;}
        QString operator + (const char* other){return value + other;}

        void operator=(const QString& other){value = other;}
        void operator=(const char* other){value = other;}
        operator QString()const{return value;}



};
*/

#endif // VARIABLE_H
