#include <iostream>
#include "../include/node.hpp"

int main(int argc, char *argv[])
{
    List<int> list;
    list.insert(1);
    list.insert(2);

    std::cout << list;

    for(int i = 0; i < 3; ++i)
        list.pop();

    list.insert(3);
    list.insert(4);

    std::cout << list;

    list.erase();

    std::cout << list;

    return 0;
}