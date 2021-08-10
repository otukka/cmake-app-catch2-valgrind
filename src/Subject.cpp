

#include "Subject.hpp"

#include <iostream>

Subject::Subject()
{
    std::cout << "Default Constructor: Subject" << std::endl;
}
Subject::Subject(uint32_t a_data): m_data(a_data)
{
    std::cout << "Constructor with parameter: Subject" << std::endl;
}

Subject::~Subject()
{
    std::cout << "Deconstructor: Subject" << std::endl;
}

void Subject::SetData(uint32_t a_data)
{
    m_data = a_data;
}
uint32_t Subject::getData()
{
    return m_data;
}