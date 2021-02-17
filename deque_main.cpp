#include <iostream>
#include "deque.hpp"
#include <deque>

int main() {
    std::deque<int> deq;
    deq.push_back(1);
    deq.push_back(2);
    std::deque<int>::iterator it = deq.begin();
    std::cout << *it << std::endl;
}