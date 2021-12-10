#define CATCH_CONFIG_MAIN   

#include <catch2/catch.hpp>

/*
 * Bit operations
 * a=target variable
 * b=bit number to act upon 0-n
 * (!(!(a))) <= boolean
 * Modified from https://stackoverflow.com/questions/47981
 */
#define BIT_SET(a, b)              ((a) |= ((uint64_t)0x1 << (b)))
#define BIT_CLEAR(a, b)            ((a) &= ~((uint64_t)0x1 << (b)))
#define BIT_FLIP(a, b)             ((a) ^= ((uint64_t)0x1 << (b)))
#define BIT_CHECK(a, b)            (!(!((a) & ((uint64_t)0x1 << (b)))))
/*
 * Bitmask operations
 * Is there sizeof(x) >= sizeof(mask) constraint?
 */
#define BITMASK_SET(x, mask)       ((x) |= (mask))
#define BITMASK_CLEAR(x, mask)     ((x) &= (~(mask)))
#define BITMASK_FLIP(x, mask)      ((x) ^= (mask))
#define BITMASK_CHECK_ALL(x, mask) (!(~(x) & (mask)))
#define BITMASK_CHECK_ANY(x, mask) (!(!((x) & (mask))))


TEST_CASE( "Testing macro: bit operations", "[bitoper]" ) {
    
    uint8_t test;

    for (size_t i = 0; i < 7; i++)
    {
        for (uint8_t j = 0x00; j < 0xFF; j++)
        {
            uint8_t tmp = j; /* copy value because modification are inplace and loop might stuck */
            BIT_SET(tmp, i);
            REQUIRE(BIT_CHECK(tmp, i));
            BIT_CLEAR(tmp, i);
            REQUIRE_FALSE(BIT_CHECK(tmp, i));
            BIT_FLIP(tmp, i);
            REQUIRE(BIT_CHECK(tmp, i));
            BIT_FLIP(tmp, i);
            REQUIRE_FALSE(BIT_CHECK(tmp, i));
        }
    }

    /* All same */
    for (uint8_t i = 0x01; i < 0xFF; i++)
    {
        uint8_t tmp = i;
        
        BITMASK_SET(tmp, i);
        REQUIRE(BITMASK_CHECK_ANY(tmp, i));
        REQUIRE(BITMASK_CHECK_ALL(tmp, i));

        BITMASK_CLEAR(tmp, i);
        REQUIRE(tmp ==  0x00);

        BITMASK_SET(tmp, i);
        BITMASK_FLIP(tmp, i);
        REQUIRE(tmp ==  0x00);

        BITMASK_FLIP(tmp, i);
        REQUIRE(BITMASK_CHECK_ANY(tmp, i));
        REQUIRE(BITMASK_CHECK_ALL(tmp, i));
    }

    /* All same */
    for (uint8_t i = 0x01; i < 0xFF; i++)
    {
        REQUIRE(BITMASK_CHECK_ANY(i, i));
        REQUIRE(BITMASK_CHECK_ALL(i, i));
        uint8_t copy = i;
        REQUIRE_FALSE(BITMASK_CHECK_ANY((~copy), copy));
        REQUIRE_FALSE(BITMASK_CHECK_ALL((~copy), copy));
    }

    /* All zeros */
    test = 0x00;
    for (uint8_t i = 0x01; i < 0xFF; i++)
    {
        REQUIRE_FALSE(BITMASK_CHECK_ANY(test, i));
        REQUIRE_FALSE(BITMASK_CHECK_ALL(test, i));
    }

    /* All ones*/
    test = 0xFF;
    for (uint8_t i = 0x01; i < 0xFF; i++)
    {
        REQUIRE(BITMASK_CHECK_ANY(test, i));
        REQUIRE(BITMASK_CHECK_ALL(test, i));
    }

    /* First byte ones*/
    test = 0xF0;
    for (uint8_t i = 0xF1; i < 0xFF; i++)
    {
        REQUIRE_FALSE(BITMASK_CHECK_ALL(test, i));
        REQUIRE(BITMASK_CHECK_ANY(test, i));
    }

    /* Second byte ones*/
    test = 0x0F;
    for (uint8_t i = 0xF1; i < 0xFF; i++)
    {
        REQUIRE_FALSE(BITMASK_CHECK_ALL(test, i));
        REQUIRE(BITMASK_CHECK_ANY(test, i));
    }
}