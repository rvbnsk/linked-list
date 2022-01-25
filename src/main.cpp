#include <iostream>
#include "../include/node.hpp"

int main()
{
    List<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    //list.insert(4);
    //list.insert(5);
    //list.insert(6);
    //list.insert(7);


    std::cout << list << std::endl;

    for(auto elem : list)
        std::cout << elem << std::endl;
    

    //list.pop();

    std::cout << std::endl << list;

    //list.pop();

    //std::cout << list;

    //list.pop();

    //std::cout << list;

    return 0;
}