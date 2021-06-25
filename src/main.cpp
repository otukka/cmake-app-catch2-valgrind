
#include <iostream> /* cout, hex*/
#include <iomanip>  /* setw, setfill*/
#include <cmath>    /* round */
#include <cassert>
#include <bitset>   /* bitset */
#include <typeinfo> /* bitset */

typedef uint32_t u32;
typedef int32_t i32;

typedef uint8_t u8;
typedef int8_t i8;

template <class T>
T getBitMask(T bits)
{
    auto mask = std::pow(2, bits) - 1;
    return mask;
}

template <class T1, class T2>
T2 floatingconversion(T1 f, T2 scale = 1)
{
    return (T2)std::round(f * scale);
}

template <class T1, class T2>
T2 floatingbitrange(T1 f, T2 bits, T2 scale = 1)
{
    return floatingconversion(f, scale) & getBitMask(bits);
}

template <class T1>
bool negative(T1 number, T1 bits)
{
    return (number & (0x1 << (bits - 1))) > 0;
}

template <class T1, class T2>
T1 bitrangefloating(T2 number, T2 bits, T1 scale)
{
    if (negative(number, bits))
    {
        return (T1) -1 * ((number ^ getBitMask(bits)) + 1) / scale;
    }
    else
    {
        return (T1)number / scale;
    }
}

void test()
{

    // These work because bit width is the same
    assert(static_cast<i8>(0x80) == -128);
    assert(static_cast<i8>(0x81) == -127);
    assert(static_cast<i8>(0xFE) == -2);
    assert(static_cast<i8>(0xFF) == -1);
    assert(static_cast<i8>(0x00) == 0);
    assert(static_cast<i8>(0x7F) == 127);

    // If bit width is different static_cast won't work 
    assert(static_cast<i32>(0x80) != -128);
    assert(static_cast<i32>(0x81) != -127);
    assert(static_cast<i32>(0xFE) != -2);
    assert(static_cast<i32>(0xFF) != -1);

    // Positive side don't care
    assert(static_cast<i32>(0x00) == 0);
    assert(static_cast<i32>(0x7F) == 127);

    assert(-1 * ((0x7 ^ 0x7 ) + 1) == -1);
    assert(-1 * ((0x6 ^ 0x7 ) + 1) == -2);
    assert(-1 * ((0x5 ^ 0x7 ) + 1) == -3);
    assert(-1 * ((0x4 ^ 0x7 ) + 1) == -4);


    assert((0x1) << 0 == 1);
    assert((0x1) << 1 == 2);
    assert((0x1) << 2 == 4);
    assert((0x1) << 3 == 8);

    assert((0x1) << 0 > 0);
    assert((0x1) << 1 > 0);
    assert((0x1) << 2 > 0);
    assert((0x1) << 3 > 0);

    assert(getBitMask(0) == 0x00);
    assert(getBitMask(1) == 0x01);
    assert(getBitMask(2) == 0x03);
    assert(getBitMask(3) == 0x07);
    assert(getBitMask(4) == 0x0F);
    assert(getBitMask(11) == 0x7FF);

    assert(floatingconversion(1.0, (u32)1) == 1);
    assert(floatingconversion(1.0, (u32)1) == 1);
    assert(floatingconversion(1.0, (u32)2) == 2);

    assert(typeid(floatingconversion(1.0, (u32)3)) == typeid(u32));
    assert(typeid(floatingconversion(1.0, (double)3)) == typeid(double));

    assert(floatingconversion(1.0, (double)1) == 1);
    assert(floatingconversion(1.0, (double)2) == 2);
    assert(floatingconversion(1.0, (double)3) == 3);

    assert(floatingbitrange(0.0, (u32)3) == 0);
    assert(floatingbitrange(1.0, (u32)3) == 1);

    assert(floatingbitrange(0.0, (u32)1, (u32)1) == 0);
    assert(floatingbitrange(1.0, (u32)1, (u32)1) == 1);

    assert(floatingbitrange(-1.0, (u32)3, (u32)1) == 7);
    assert(floatingbitrange(-1.0, (u32)3, (u32)2) == 6);

    assert(floatingbitrange(3.0, (u32)3) == 3);
    assert(floatingbitrange(2.0, (u32)3) == 2);
    assert(floatingbitrange(1.0, (u32)3) == 1);
    assert(floatingbitrange(0.0, (u32)3) == 0);
    assert(floatingbitrange(-1.0, (u32)3) == 7);
    assert(floatingbitrange(-2.0, (u32)3) == 6);
    assert(floatingbitrange(-3.0, (u32)3) == 5);
    assert(floatingbitrange(-4.0, (u32)3) == 4);

    assert(negative((u32)0, (u32)3) == false);
    assert(negative((u32)1, (u32)3) == false);
    assert(negative((u32)2, (u32)3) == false);
    assert(negative((u32)3, (u32)3) == false);
    assert(negative((u32)7, (u32)3) == true);
    assert(negative((u32)6, (u32)3) == true);
    assert(negative((u32)5, (u32)3) == true);
    assert(negative((u32)4, (u32)3) == true);

    assert(bitrangefloating((u32)0, (u32)3, (float)1.0) == 0.0);
    assert(bitrangefloating((u32)1, (u32)3, (float)1.0) == 1.0);
    assert(bitrangefloating((u32)2, (u32)3, (float)1.0) == 2.0);
    assert(bitrangefloating((u32)3, (u32)3, (float)1.0) == 3.0);
    assert(bitrangefloating((u32)4, (u32)3, (float)1.0) == -4.0);
    assert(bitrangefloating((u32)5, (u32)3, (float)1.0) == -3.0);
    assert(bitrangefloating((u32)6, (u32)3, (float)1.0) == -2.0);
    assert(bitrangefloating((u32)7, (u32)3, (float)1.0) == -1.0);


    assert(bitrangefloating((u32)0, (u32)3, (float)2.0) == 0.5 * 0.0);
    assert(bitrangefloating((u32)1, (u32)3, (float)2.0) == 0.5 * 1.0);
    assert(bitrangefloating((u32)2, (u32)3, (float)2.0) == 0.5 * 2.0);
    assert(bitrangefloating((u32)3, (u32)3, (float)2.0) == 0.5 * 3.0);
    assert(bitrangefloating((u32)4, (u32)3, (float)2.0) == 0.5 * -4.0);
    assert(bitrangefloating((u32)5, (u32)3, (float)2.0) == 0.5 * -3.0);
    assert(bitrangefloating((u32)6, (u32)3, (float)2.0) == 0.5 * -2.0);
    assert(bitrangefloating((u32)7, (u32)3, (float)2.0) == 0.5 * -1.0);

}

int main(int argc, char const *argv[])
{


    test();

    return 0;
}
