
#include "TestClass.hpp"


TestClass::TestClass(/* args */)
{
    m_ptr = new int();
}

TestClass::~TestClass()
{
}

int TestClass::func()
{
    return 1;
}
