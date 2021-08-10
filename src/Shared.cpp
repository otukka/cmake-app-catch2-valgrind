

#include "Shared.hpp"

#include <iostream>

Shared::Shared()
{
    std::cout << "Default Constructor: Shared" << std::endl;
}
Shared::Shared(uint32_t a_data): m_data(a_data)
{
    std::cout << "Constructor with parameter: Shared" << std::endl;
}

Shared::~Shared()
{
    std::cout << "Deconstructor: Shared" << std::endl;
}

void Shared::SetData(uint32_t a_data)
{
    m_data = a_data;
}
uint32_t Shared::getData()
{
    return m_data;
}