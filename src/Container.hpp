#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Shared.hpp"

class Container
{
private:
    Shared m_subject;
public:
    Container();
    ~Container();
    void AddShared();
};



#endif /*CONTAINER */