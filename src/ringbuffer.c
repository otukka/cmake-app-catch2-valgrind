

#include "ringbuffer.h"

static ringbuffer_t m_ringbuffer;

void ringbufferInit(void)
{
    memset(&m_ringbuffer, 0x00, sizeof(ringbuffer_t));
}

void addValue(uint32_t a_value)
{
    m_ringbuffer.buffer[m_ringbuffer.head % RINGBUFFER_LENGTH] = a_value;
    if (getSize() % (RINGBUFFER_LENGTH + 1) == RINGBUFFER_LENGTH)
    {
        m_ringbuffer.tail++;
    }
    m_ringbuffer.head++;
}

uint32_t* getValues(uint32_t a_length)
{
    uint32_t* ptr = &m_ringbuffer.buffer[m_ringbuffer.tail % RINGBUFFER_LENGTH];
    m_ringbuffer.tail += a_length;
    return ptr;
}

uint32_t getHead(void)
{
    return m_ringbuffer.head % RINGBUFFER_LENGTH;
}

uint32_t getTail(void)
{
    return m_ringbuffer.tail % RINGBUFFER_LENGTH;
}

uint32_t getHeadRaw(void)
{
    return m_ringbuffer.head;
}

uint32_t getTailRaw(void)
{
    return m_ringbuffer.tail;
}

uint32_t getSize(void)
{
    return (m_ringbuffer.head - m_ringbuffer.tail);
}
