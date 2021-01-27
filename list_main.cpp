#include <iostream>
#include "list.hpp"
#include <list>

int main() {
    ft::list<int> lst;
    for (int i = 0; i < 5; ++i)
        lst.push_back(i);
    for (ft::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    ft::list<int> lst2;
    for (int i = 1; i < 4; ++i)
        lst2.push_back(i * 10);
    ft::list<int>::iterator it = lst.begin();
    std::cout << "lst size = " << lst.size() << " lst2 size = " << lst2.size() << std::endl;
    lst.splice(it, lst2, ++lst2.begin());
    for (ft::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (ft::list<int>::iterator it = lst2.begin(); it != lst2.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "lst size = " << lst.size() << " lst2 size = " << lst2.size() << std::endl;
}