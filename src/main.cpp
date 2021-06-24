
#include <iostream>
#include <iomanip> /* std::setw */
#include <cassert> /* std::setw */

#define FORGOTTEN_NUMBER -1

enum Constructor
{
    Default = 0,
    rvalueParam,
    lvalueParam,
    Copy,
    CopyAssign, // is this a thing?
    Move,
    MoveAssign,
    Forgotten,

};

struct State
{
    int m_order;
    int m_data;
    int value;
    int m_constructor;
};

class MyClass
{
private:
    int m_order;
    int m_data;
    int *m_ptr;
    Constructor m_constructor;

public:
    // Default constructor
    MyClass() : m_order(0), m_data(0),
                m_constructor(Constructor::Default)
    {
        m_ptr = new int();
        *m_ptr = 0;
    }
    // Default destructor
    ~MyClass()
    {
        delete m_ptr;
    }

    // lvalue constructor
    MyClass(const int &a_order, const int &a_data) : m_order(a_order), m_data(a_data), m_constructor(Constructor::lvalueParam)
    {
        m_ptr = new int();
        *m_ptr = 0;
    }

    // rvalue constructor
    MyClass(const int &&a_order, const int &&a_data) : m_order(a_order), m_data(a_data), m_constructor(Constructor::rvalueParam)
    {
        m_ptr = new int();
        *m_ptr = 0;
    }

    // Copy constructor (lvalue)
    MyClass(const MyClass &other) : m_order(other.m_order), m_data(other.m_data), m_constructor(Constructor::Copy)
    {
        m_ptr = new int();
        *m_ptr = *other.m_ptr;
    }

    // Move constructor (rvalue)
    MyClass(MyClass &&other) noexcept : m_order(other.m_order), m_data(other.m_data), m_constructor(Constructor::Move)
    {
        m_ptr = other.m_ptr;
        other.m_data = FORGOTTEN_NUMBER;
        other.m_order = FORGOTTEN_NUMBER;
        other.m_ptr = nullptr;
        other.m_constructor = Constructor::Forgotten;
    }

    // Copy operator (lvalue)
    MyClass &operator=(const MyClass &other)
    {
        if (this != &other)
        {
            // We replace existing object. Have to remove existing data.
            delete m_ptr;
            m_ptr = new int();
            *m_ptr = *other.m_ptr;
            m_order = other.m_order;
            m_data = other.m_data;
            m_constructor = Constructor::CopyAssign;
        }
        return *this;
    }

    // Move operator (lvalue)
    MyClass &operator=(MyClass &&other)
    {
        if (this != &other)
        {
            // We replace existing object. Have to remove existing data.
            delete m_ptr;
            m_ptr = new int();

            // Move data
            *m_ptr = std::move(*other.m_ptr);
            m_order = std::move(other.m_order);
            m_data = std::move(other.m_data);
            m_constructor = Constructor::MoveAssign;

            // Cleanup
            other.m_data = FORGOTTEN_NUMBER;
            other.m_order = FORGOTTEN_NUMBER;
            delete other.m_ptr;
            other.m_ptr = nullptr;
            other.m_constructor = Constructor::Forgotten;
        }
        return *this;
    }

    MyClass operator+(const int &data)
    {
        return MyClass(this->m_order, this->m_data + data);
    }

    MyClass operator-(const int &data)
    {
        return MyClass(this->m_order, this->m_data - data);
    }

    MyClass operator+(const int &&data)
    {
        return MyClass(this->m_order, this->m_data + data);
    }

    MyClass operator-(const int &&data)
    {
        return MyClass(this->m_order, this->m_data - data);
    }

    bool checkState(State a_state)
    {

        if (this->m_data == a_state.m_data && this->m_order == a_state.m_order && *this->m_ptr == a_state.value && this->m_constructor == a_state.m_constructor)
        {
            return true;
        }
        return false;
    }

    bool isFrogotten()
    {
        assert(("m_order is not forgotten", this->m_order == FORGOTTEN_NUMBER));
        assert(("m_data is not forgotten", this->m_data == FORGOTTEN_NUMBER));
        assert(("m_ptr is not nullptr", this->m_ptr == nullptr));
        return m_constructor == Constructor::Forgotten;
    }

    bool _checkState(State a_state)
    {
        std::cout << *this << std::endl;
        return checkState(a_state);
    }

    int getOrder()
    {
        return this->m_order;
    }
    int getData()
    {
        return this->m_data;
    }
    void setOrder(const int &a_order)
    {
        m_order = a_order;
    }
    void setData(const int &a_data)
    {
        m_data = a_data;
    }
    void setOrder(const int &&a_order)
    {
        m_order = a_order;
    }
    void setData(const int &&a_data)
    {
        m_data = a_data;
    }
    friend auto operator<<(std::ostream &os, MyClass const &m) -> std::ostream &
    {
        if (m.m_ptr == nullptr)
        {
            return os << "Order: " << std::setw(3) << m.m_order << " Data: " << std::right << std::setw(3) << m.m_data << " ptr == nullptr"
                      << " Constructor: " << m.m_constructor;
        }
        return os << "Order: " << std::setw(3) << m.m_order << " Data: " << std::right << std::setw(3) << m.m_data << " ptr address : " << m.m_ptr << " ptr value : " << std::setw(3) << *m.m_ptr << " Constructor: " << m.m_constructor;
    }
};

std::string value(MyClass &mc)
{
    return "lvalue";
}

std::string value(MyClass &&mc)
{
    return "rvalue";
}
std::string value(const MyClass &mc)
{
    return "lvalue";
}

std::string value(const MyClass &&mc)
{
    return "rvalue";
}

/* Tests */
void testValue()
{
    MyClass tmp1 = MyClass();
    assert(value(tmp1) == "lvalue");
    assert(value((MyClass &)tmp1) == "lvalue");

    assert(value((MyClass &&) tmp1) == "rvalue");
    assert(value(std::move(tmp1)) == "rvalue");
    assert(value(tmp1 + 10) == "rvalue");
    assert(value(tmp1 - 10) == "rvalue");
    int tmp_value = 10;
    assert(value(tmp1 + tmp_value) == "rvalue");
    assert(value(tmp1 - tmp_value) == "rvalue");

    MyClass tmp2 = MyClass();
    MyClass tmp3 = tmp2;
    assert(value(tmp3) == "lvalue");
    assert(value((MyClass &)tmp3) == "lvalue");

    MyClass tmp4 = MyClass();
    MyClass tmp5 = tmp4 + 10;
    assert(value(tmp4) == "lvalue");
    assert(value((MyClass &)tmp4) == "lvalue");
}

void testDefaultConstructor()
{
    MyClass tmp1 = MyClass();
    assert(("Default true failed", tmp1.checkState({0, 0, 0, Constructor::Default})));
    assert(("Default false failed", !tmp1.checkState({1, 0, 0, Constructor::Default})));
    assert(("Default false failed", !tmp1.checkState({0, 1, 0, Constructor::Default})));
    assert(("Default false failed", !tmp1.checkState({0, 0, 1, Constructor::Default})));
    assert(("Default false failed", !tmp1.checkState({1, 1, 1, Constructor::Default})));
    assert(("Default false failed", !tmp1.checkState({0, 0, 0, Constructor::Copy})));
}

void testRvalueConsturctor()
{
    MyClass tmp1 = MyClass(1, 1);
    assert(("Default true failed", tmp1.checkState({1, 1, 0, Constructor::rvalueParam})));
    assert(("Default false failed", !tmp1.checkState({1, 1, 0, Constructor::lvalueParam})));
}

void testLvalueConsturctor()
{
    int order = 1;
    int data = 1;
    MyClass tmp1 = MyClass(order, data);
    assert(("Default true failed", tmp1.checkState({order, data, 0, Constructor::lvalueParam})));
    assert(("Default false failed", !tmp1.checkState({order, data, 0, Constructor::rvalueParam})));
}

// Move tests
void testMoveConstructor1()
{
    MyClass tmp1 = MyClass(1, 10);
    assert(("Default true failed", tmp1.checkState({1, 10, 0, Constructor::rvalueParam})));
    MyClass tmp2 = std::move(tmp1);
    assert(("Move true failed", tmp2.checkState({1, 10, 0, Constructor::Move})));
    assert(tmp1.isFrogotten());
}

void testMoveConstructor2()
{
    MyClass tmp1 = MyClass();
    assert(("Default true failed", tmp1.checkState({0, 0, 0, Constructor::Default})));
    MyClass tmp2 = (MyClass &&) tmp1;
    assert(("Move true failed", tmp2.checkState({0, 0, 0, Constructor::Move})));
    assert(tmp1.isFrogotten());
}

void testMoveConstructor3()
{
    MyClass tmp1 = MyClass();
    assert(("Default true failed", tmp1.checkState({0, 0, 0, Constructor::Default})));
    MyClass tmp2 = std::move(tmp1 + 1);
    assert(("Move true failed", tmp2.checkState({0, 1, 0, Constructor::Move})));
    // assert(tmp1.isFrogotten()); // rvalue move i.e. not forgotten
}

void testMoveAssingConstructor()
{
    MyClass tmp0 = MyClass();
    MyClass tmp1 = MyClass();
    tmp0 = (MyClass &&) tmp1;
    assert(("Default true failed", tmp0.checkState({0, 0, 0, Constructor::MoveAssign})));
    assert(tmp1.isFrogotten());
}

// Copy tests
void testCopyConstructor1()
{
    MyClass tmp1 = MyClass();
    MyClass tmp2 = tmp1;
    assert(("Default true failed", tmp1.checkState({0, 0, 0, Constructor::Default})));
    assert(("Copy true failed", tmp2.checkState({0, 0, 0, Constructor::Copy})));
}

void testCopyConstructor2()
{
    MyClass tmp1 = MyClass();
    MyClass tmp2 = MyClass(tmp1);
    assert(("Default true failed", tmp1.checkState({0, 0, 0, Constructor::Default})));
    assert(("Copy true failed", tmp2.checkState({0, 0, 0, Constructor::Copy})));
}

void testCopyConstructor3()
{
    MyClass tmp1 = MyClass();
    MyClass tmp2 = MyClass(tmp1);
    tmp1.setOrder(10);
    assert(("Default true failed", tmp1.checkState({10, 0, 0, Constructor::Default})));
    assert(("Copy true failed", tmp2.checkState({0, 0, 0, Constructor::Copy})));
}

void testCopyAssingConstructor()
{
    MyClass tmp0 = MyClass();
    MyClass tmp1 = MyClass();
    tmp0 = MyClass(tmp1);
    assert(("Default true failed", tmp0.checkState({0, 0, 0, Constructor::CopyAssign})));
    assert(tmp1.isFrogotten());
}

void testCopyConstructor4()
{
    MyClass tmp1 = MyClass();
    MyClass tmp2(tmp1);

    assert(("Default true failed", tmp1.checkState({0, 0, 0, Constructor::Default})));
    assert(("Copy true failed", tmp2.checkState({0, 0, 0, Constructor::Copy})));
}

void testOperators()
{
    MyClass tmp1 = MyClass();
    tmp1 = tmp1 + 10;
    assert(("CopyAssign true failed", tmp1.checkState({0, 10, 0, Constructor::MoveAssign})));

    MyClass tmp2 = MyClass();
    tmp2 = tmp2 - 10;
    assert(("CopyAssign true failed", tmp2.checkState({0, -10, 0, Constructor::MoveAssign})));

    MyClass tmp3 = MyClass();
    int plus = 10;
    tmp3 = tmp3 + plus;
    assert(("CopyAssign true failed", tmp3.checkState({0, plus, 0, Constructor::MoveAssign})));

    MyClass tmp4 = MyClass();
    int minus = 10;
    tmp4 = tmp4 - minus;
    assert(("CopyAssign true failed", tmp4.checkState({0, -1 * minus, 0, Constructor::MoveAssign})));
}

int main(int argc, char const *argv[])
{
    std::cout << "\033[31m"
              << "Program start"
              << "\033[0m" << std::endl;

    testValue();
    testDefaultConstructor();
    testRvalueConsturctor();
    testLvalueConsturctor();

    testMoveConstructor1();
    testMoveConstructor2();
    testMoveConstructor3();
    testMoveAssingConstructor();

    testCopyConstructor1();
    testCopyConstructor2();
    testCopyConstructor3();
    testCopyConstructor4();

    testOperators();

    std::cout << "\033[31m"
              << "\nProgram end"
              << "\033[0m" << std::endl;

    return 0;
}
