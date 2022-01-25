#include <iostream>
#include "../include/node.hpp"

int main(int argc, char *argv[])
{
    List<std::string> list;
    list.insert("Arek");
    list.insert("Maciek");

    std::cout << list;

    list.pop();

    std::cout << list;

    return 0;
}