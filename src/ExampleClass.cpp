
#include "ExampleClass.hpp"


ExampleClass::ExampleClass()
{
    m_ptr = new int;
}

ExampleClass::~ExampleClass()
{
}

int ExampleClass::func()
{
    return 1;
}
