#include <iostream>
#include "../include/node.hpp"

int main()
{
    List<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    list.insert(6);
    list.insert(7);

    std::cout << list << std::endl;

    for(auto elem : list)
        std::cout << elem << std::endl;

    std::cout << std::endl;

    for(auto iter = list.begin(); iter != list.end(); iter++)
        std::cout << *iter << std::endl;

    std::cout << std::endl << list[2] << std::endl;
    
    try
    {
        std::cout << std::endl << list.at(7) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(char const * e)
    {
        std::cerr << e << '\n';
    }
    
    list.erase();
    std::cout << std::endl;

    list.pop();

    std::cout << list;

    return 0;
}