
#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "Hello world!" << std::endl;
    
    // while (1) { } // Problematic with valgrind etc
    return 0;
}
