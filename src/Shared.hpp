
#ifndef SHARED_H_
#define SHARED_H_

#include <cstdint> /* uintXX_t */

class Shared
{
private:
    uint32_t m_data;
public:
    Shared();
    Shared(uint32_t a_data);
    ~Shared();
    void SetData(uint32_t a_data);
    uint32_t getData();
};


#endif /*SHARED */