#include <iostream>
#include "list.hpp"
#include <list>

int main() {
    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    a[0] = 5;
    ft::list<int> lst(a, a + 10);
    ft::list<int> lst2;
    lst.front() = 123456;
    lst2.resize(15, 43);
    lst.swap(lst2);
    for (ft::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << std::endl;
}