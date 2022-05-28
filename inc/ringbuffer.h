#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#ifndef RINGBUFFER_LENGTH
#define RINGBUFFER_LENGTH 1024U
#endif
typedef struct ringbuffer_s
{
    uint32_t buffer[RINGBUFFER_LENGTH];
    uint32_t head;
    uint32_t tail;

} ringbuffer_t;


void ringbufferInit(void);

void addValue(uint32_t a_value);
uint32_t* getValues(uint32_t a_length);

uint32_t getHead(void);
uint32_t getTail(void);
uint32_t getSize(void);

uint32_t getHeadRaw(void);
uint32_t getTailRaw(void);


#ifdef __cplusplus
}
#endif

#endif // !RINGBUFFER_H_