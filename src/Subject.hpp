
#ifndef SHARED_H_
#define SHARED_H_

#include <cstdint> /* uintXX_t */

class Subject
{
private:
    uint32_t m_data;
public:
    Subject();
    Subject(uint32_t a_data);
    ~Subject();
    void SetData(uint32_t a_data);
    uint32_t getData();
};


#endif /*Subject */