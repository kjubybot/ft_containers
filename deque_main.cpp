#include <iostream>
#include "deque.hpp"
#include <deque>

int main() {
    ft::deque<int> dq;
    dq.push_back(4);
    dq.push_back(8);
    dq.push_front(1);
    for (ft::deque<int>::iterator it = dq.begin(); it != dq.end(); ++it)
        std::cout << *it << std::endl;
}