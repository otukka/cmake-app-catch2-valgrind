
#include <catch2/catch.hpp>

#include "ringbuffer.h"

TEST_CASE("Size never too large")
{
    ringbufferInit();
    for (size_t i = 0; i < 1239; i++)
    {

        addValue(i);
        if (i > 10)
        {
            CHECK(getSize() == 10);
        }
    }
}

TEST_CASE("Basic fill ringbuffer")
{
    ringbufferInit();
    for (size_t i = 0; i < 9; i++)
    {

        addValue(i);

        CHECK(getTail() == 0);
        CHECK(getHead() == (i + 1));
        CHECK(getSize() == (i + 1));
    }

    addValue(9);

    CHECK(getTail() == 0);
    CHECK(getHead() == 0);
    CHECK(getSize() == 10);

    uint32_t* buffer = getValues(10);
    for (size_t i = 0; i < 10; i++)
    {
        CHECK(buffer[i] == i);
    }
}

TEST_CASE("More complex fill ringbuffer")
{
    ringbufferInit();
    for (size_t i = 0; i < 10; i++)
    {
        addValue(i);
    }

    uint32_t* buffer = getValues(5);
    for (size_t i = 0; i < 5; i++)
    {
        CHECK(buffer[i] == i);
    }

    CHECK(getTail() == 5);
    CHECK(getHead() == 0);

    for (size_t i = 0; i < 5; i++)
    {
        addValue(i);
    }

    CHECK(getTail() == 5);
    CHECK(getHead() == 5);
    CHECK(getSize() == 10);


    for (size_t i = 0; i < 5; i++)
    {
        addValue(i);
    }

    CHECK(getTail() == 0);
    CHECK(getHead() == 0);
    CHECK(getSize() == 10);


    buffer = getValues(1);
    CHECK(getTail() == 1);
    CHECK(getHead() == 0);
    CHECK(getSize() == 9);
}