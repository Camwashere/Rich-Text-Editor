#include "id.h"

IDManager::IDManager() : max(0)
{

}

unsigned long IDManager::ASSIGN()
{

    if (stack.isEmpty())
    {

        return max++;
    }
    else
    {
        unsigned int popped = stack.pop();

        return popped;
    }
}

void IDManager::FREE(unsigned long id)
{
    stack.push(id);
    if (stack.length() == max-1)
    {
        RESET();
    }

}
void IDManager::RESET()
{
    max = 0;
    stack.clear();
}

IDManager Tracked::ID_MANAGER_;

Tracked::Tracked() : id(ID_MANAGER_.ASSIGN())
{

}
Tracked::~Tracked()
{
    ID_MANAGER_.FREE(id);
}
