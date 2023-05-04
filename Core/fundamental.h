#ifndef FUNDAMENTAL_H
#define FUNDAMENTAL_H
#include <QString>
#include <QVariant>

enum FundamentalType
{
    NONE=0,
    NUMBER,
    BOOL,
    TEXT,
    FUNCTION,

};



class Fundamental
{
    private:
        unsigned int type;
        QVariant var;




    public:
        Fundamental();
        Fundamental(double val);
        Fundamental(int val);
        Fundamental(bool val);
        Fundamental(const QString& val);
        Fundamental(const char* val);
        Fundamental(char val);
        template<typename F>
        Fundamental(F&& lambda) : type(FUNCTION){};



        operator double()const;
        operator int()const;
        operator bool()const;
        operator QChar()const;
        operator QString()const;


    public:
        QVariant getValue()const {return var;};
        int asInt()const;
        double asDouble()const;
        QChar asChar()const;
        bool asBool()const;


        unsigned int getType()const{return type;}
};







#endif // FUNDAMENTAL_H
