#include <iostream>
#include "list.hpp"
#include <list>

bool eq3(int n) { return n == 3; }

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
    lst.merge(lst2);
//    lst.splice(it, lst2, ++lst2.begin());
    for (ft::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (ft::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    for (ft::list<int>::iterator it = lst2.begin(); it != lst2.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::cout << "lst size = " << lst.size() << " lst2 size = " << lst2.size() << std::endl;

    ft::list<int> lst3;
    lst3.push_back(3);
    lst3.push_back(5);
    lst3.push_back(1);
    lst3.push_back(6);
    lst3.push_back(-4);
    lst3.push_back(0);
    for (ft::list<int>::iterator it = lst3.begin(); it != lst3.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    lst3.sort();
    for (ft::list<int>::iterator it = lst3.begin(); it != lst3.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
    lst3.reverse();
    for (ft::list<int>::iterator it = lst3.begin(); it != lst3.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;

    lst.clear();
    lst2.clear();
    lst3.clear();

    for (int i = 0; i < 5; ++i) {
        lst.push_back(i);
        lst2.push_back(i);
    }
    for (int i = 2; i < 6; ++i)
        lst3.push_back(i);
    std::cout << "lst == lst2? -> " << (lst == lst2) << std::endl;
    std::cout << "lst == lst3? -> " << (lst == lst3) << std::endl;
}