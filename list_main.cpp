#include <iostream>
#include "list.hpp"

int main() {
    ft::list<int> lst;
    lst.insert(lst.end(), 14);
    lst.insert(lst.end(), 42);
    std::cout << lst.back() << std::endl;
    std::cout << lst.front() << std::endl;
}