#ifndef ID_H
#define ID_H
#include <QStack>

class IDManager
{
    private:
        unsigned long max;
        QStack<unsigned long> stack;
    public:
        IDManager();

        unsigned long ASSIGN();
        void FREE(unsigned long id);
        void RESET();
};

class Tracked
{
    private:
        static IDManager ID_MANAGER_;

    private:
        const unsigned long id;

    public:
        Tracked();
        ~Tracked();
        unsigned long getID()const{return id;}

};

#endif // ID_H
