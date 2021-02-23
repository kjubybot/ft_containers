#include <iostream>
#include "deque.hpp"
#include <deque>

int main() {
    ft::deque<int> dq;
    int ar[5] = {55,444,333,22,111};
    dq.push_back(1);
    dq.push_back(2);
    dq.push_front(60);
    dq.push_back(3);
    ft::deque<int>::iterator pos = dq.begin();
    pos += 2;
    std::cout << "Insert" << std::endl;
    dq.insert(pos, ar, ar + 4);
    for (ft::deque<int>::iterator it = dq.begin(); it != dq.end(); ++it)
        std::cout << *it << std::endl;
}