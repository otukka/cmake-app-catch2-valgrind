
#include <iostream>
#include <cstdint>   /* uintXX_t */
#include <memory>    /* smart pointers */
#include <algorithm> /* std::move */
#include "Container.hpp"

void play_with_containers()
{

    // Doesn't call constructor because "empty set of parenthesis is function declaration".
    {
        Container container2();
    }

    // Normal construction
    {
        Container container1;
        Container container3 = Container();
    }

    // Use count calculation
    {
        std::shared_ptr<Subject> shared1 = std::make_shared<Subject>();
        std::cout << "Sharer_ptr use count : " << shared1.use_count() << std::endl;
        Container container1;
        Container container2;
        container1.SetSubject(shared1);
        std::cout << "Sharer_ptr use count : " << shared1.use_count() << std::endl;
        std::cout << "Sharer_ptr use count : " << container1.GetSubject().use_count() << std::endl; // extra count in return pointer
        container2.SetSubject(shared1);
        std::cout << "Sharer_ptr use count : " << container1.GetSubject().use_count() << std::endl;
    }
}

void play_with_smart_pointers()
{

    // Doesn't call constructor
    {
        std::shared_ptr<Subject> shared1;
    }

    // Doesn't call constructor
    {
        std::shared_ptr<Subject> shared1();
    }

    // Works as expected
    {
        std::shared_ptr<Subject> shared1 = std::make_shared<Subject>();
        std::shared_ptr<Subject> shared2 = std::make_shared<Subject>(24);
    }

    // DO NOT DO THIS WITH a shared_ptr
    {
        std::shared_ptr<Subject> shared1(new Subject());
    }

    // Copies existing to shared_ptr
    {
        Subject shared1;
        std::shared_ptr<Subject> shared2 = std::make_shared<Subject>(shared1);
        shared1.SetData(13);
        shared2->SetData(31);
        std::cout << "Data shared1 : " << shared1.getData() << std::endl;
        std::cout << "Data shared2 : " << shared2->getData() << std::endl;
    }

    // Move a shared_ptr object to another Subject ptr
    {
        std::shared_ptr<Subject> shared1 = std::make_shared<Subject>();
        std::shared_ptr<Subject> shared2 = std::move(shared1);

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
        std::shared_ptr<Subject> shared1 = std::make_shared<Subject>();
        std::shared_ptr<Subject> shared2 = shared1;
        shared1->SetData(13);
        shared2->SetData(31);
        std::cout << "Data : " << shared1->getData() << std::endl;
        std::cout << "Data : " << shared2->getData() << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::cout << "Program start ..." << std::endl;
    // play_with_smart_pointers();
    play_with_containers();
    std::cout << "Program end ..." << std::endl;
    return 0;
}
