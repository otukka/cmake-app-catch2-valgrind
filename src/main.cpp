
#include <iostream>
#include <iomanip>
#include <bitset>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;


template<class A, class B>
void twosCompelement(const A &from, B &to, u32 toBits)
{
    u32 shifter = sizeof(B) * 8 - toBits;
    to = static_cast<B>(from << shifter) / (1 << shifter);
}



void test1()
{
    
    std::cout << "signed to unsigned\n";
    for (i16 a = -4; a < 4; a++)
    {
        u16 b;
        twosCompelement(a, b, 3);
        std::cout << "from: " << std::setfill(' ')<< std::setw(2) << a << " to: 0x" << std::hex  << b << std::setw(2) << std::dec << " bits: " << std::bitset<8>{b} <<  "\n";
    }
    
}

void test2()
{
    
    std::cout << "Unsigned to signed\n";
    for (u16 a = 0; a < 8; a++)
    {
        i16 b;
        twosCompelement(a, b, 3);
        std::cout << "from: "  << a << " to: " << std::setfill(' ')<< std::setw(2) << b << " bits: " << std::bitset<8>{b} <<  "\n";
    }
    
}

void test3()
{
    std::cout << "u16 -> i16 -> i16\n";
    for (u16 a = 0; a < 8; a++)
    {
        i16 b;
        twosCompelement(a, b, 3);
        u16 c;
        twosCompelement(b, c, 3);
        std::cout << "from: "  << a << " to: " << std::setfill(' ')<< std::setw(2) << c << " bits: " << std::bitset<8>{c} <<  "\n";
    }
    
}

void test4()
{
    std::cout << "i16 -> u16 -> u16\n";
    for (i16 a = -4; a < 4; a++)
    {
        u16 b;
        twosCompelement(a, b, 3);
        i16 c;
        twosCompelement(b, c, 3);
        std::cout << "from: "  << a << " to: " << std::setfill(' ')<< std::setw(2) << c << " bits: " << std::bitset<8>{c} <<  "\n";
    }
    
}


void play_with_casting()
{
    {
        u8 a = 255;
        u16 b = static_cast<u16>(a);
        std::cout << "a: " << unsigned(a) << " b: " << unsigned(b) << "\n";
    }

    {
        u16 a = 256;
        u8 b = static_cast<u8>(a);
        std::cout << "a: " << unsigned(a) << " b: " << unsigned(b) << "\n";
    }

    {
        u16 a = 430;
        u8 b = static_cast<u8>(a);
        std::cout << "a: " << unsigned(a) << " b: " << unsigned(b) << "\n";
    }

    {
        i8 a = 10;
        u8 b = static_cast<u8>(a);
        std::cout << "a: " << signed(a) << " b: " << unsigned(b) << "\n";
    }

    {
        i8 a = -10;
        u8 b = static_cast<u8>(a);
        std::cout << "a: " << signed(a) << " b: " << unsigned(b) << "\n";
    }

    {
        // 9-bit two's comlement = -1 
        u16 a = 0x1ff;
        i16 b = static_cast<i16>(a << 7) / (1 << 7);
        std::cout << std::hex << "a: 0x" << a << " b: 0x" << b << "\n";
    }
    {
        i16 a = -1;
        u16 b = static_cast<u16>(a << 7) / (1 << 7);
        std::cout << "a: 0x" << a << " b: 0x" << b << "\n";
    }


}

int main(int argc, char const *argv[])
{

    test1();
    test2();
    test3();
    test4();
    // play_with_casting();
    return 0;
}
