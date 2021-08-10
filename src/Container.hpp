#ifndef CONTAINER_H_
#define CONTAINER_H_

#include "Subject.hpp"
#include <memory>    /* smart pointers */

class Container
{
private:
    // Subject m_normal; // Creates allways instance when parent is created
    std::shared_ptr<Subject> m_shared;

public:
    Container();
    ~Container();
    void SetSubject(std::shared_ptr<Subject> a_subject);
    void SetSubject(Subject a_subject);
    std::shared_ptr<Subject> GetSubject();
};



#endif /*CONTAINER */