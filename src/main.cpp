
#include <iostream>
#include <cstdint>   /* uintXX_t */
#include <memory>    /* smart pointers */
#include <algorithm> /* std::moves */
#include "Container.hpp"

void play_with_containers()
{
    Container container1;
    // Container container2(); // Doesn't call constructor because "empty set of parenthesis is function declaration".
    Container container3 = Container();
}

void play_with_smart_pointers()
{

    /* scope */
    {
        std::shared_ptr<Shared> shared1; // Doesn't call constructor
    }

    {
        std::shared_ptr<Shared> shared1(); // Doesn't call constructor
    }

    {
        Shared shared1;
        std::shared_ptr<Shared> shared2 = std::make_shared<Shared>(shared1);
        shared1.SetData(13);
        shared2->SetData(31);
        std::cout << "Data shared1 : " << shared1.getData() << std::endl;
        std::cout << "Data shared2 : " << shared2->getData() << std::endl;


    }

    /* Works as expected */
    {
        std::shared_ptr<Shared> shared1 = std::make_shared<Shared>();
        std::shared_ptr<Shared> shared2 = std::make_shared<Shared>(24);
    }

    /* Do not do this with shared ptr */
    {
        std::shared_ptr<Shared> shared1(new Shared());
    }

    {
        std::shared_ptr<Shared> shared1 = std::make_shared<Shared>();
        std::shared_ptr<Shared> shared2 = std::move(shared1); // Moves the whole shared_ptr object

        if (0) // this wouldn't work
        {
            shared1->SetData(13);
            std::cout << "Data : " << shared1->getData() << std::endl;
        }
        else // this works
        {
            shared2->SetData(13);
            std::cout << "Data : " << shared2->getData() << std::endl;
        }
    }

    {
        std::shared_ptr<Shared> shared1 = std::make_shared<Shared>();
        std::shared_ptr<Shared> shared2 = shared1;
        shared1->SetData(13);
        shared2->SetData(31);
        std::cout << "Data : " << shared1->getData() << std::endl;
        std::cout << "Data : " << shared2->getData() << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::cout << "Program start ..." << std::endl;
    play_with_smart_pointers();
    // play_with_containers();
    std::cout << "Program end ..." << std::endl;
    return 0;
}
