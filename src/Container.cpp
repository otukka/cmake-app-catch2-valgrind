
#include "Container.hpp"

#include <iostream>

Container::Container()
{
    std::cout << "Default Constructor: Container" << std::endl;
}

Container::~Container()
{
    std::cout << "Deconstructor: Container" << std::endl;
}

void Container::SetSubject(std::shared_ptr<Subject> a_subject)
{
    m_shared = a_subject;
}
void Container::SetSubject(Subject a_subject)
{
    m_shared = std::make_shared<Subject>(a_subject);
}
std::shared_ptr<Subject> Container::GetSubject()
{
    return m_shared;
}