#include <iostream>
#include "deque.hpp"
#include <deque>

using std::cout;
using std::endl;

template <class T, class Alloc>
void print_deque(const std::deque<T, Alloc>& dq) {
    cout << "std::deque of size " << dq.size() << endl;
    for (typename std::deque<T, Alloc>::const_iterator it = dq.begin(); it != dq.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

template <class T, class Alloc>
void print_deque(const ft::deque<T, Alloc>& dq) {
    cout << "ft::deque of size " << dq.size() << endl;
    for (typename ft::deque<T, Alloc>::const_iterator it = dq.begin(); it != dq.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    cout << "Testing constructors" << endl;
    cout << "Empty" << endl;
    std::deque<int> dq1;
    ft::deque<int> fdq1;
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Fill (10, 42)" << endl;
    std::deque<int> dq2(10, 42);
    ft::deque<int> fdq2(10, 42);
    print_deque(dq2);
    print_deque(fdq2);
    cout << endl;

    cout << "Range (from array {1,5,2,6,3})" << endl;
    int a[5] = {1, 5, 2, 6, 3};
    std::deque<int> dq3(a, a + 5);
    ft::deque<int>  fdq3(a, a + 5);
    print_deque(dq3);
    print_deque(fdq3);
    cout << endl;

    cout << "Copy (from previous deque)" << endl;
    std::deque<int> dq4(dq3);
    ft::deque<int> fdq4(fdq3);
    print_deque(dq4);
    print_deque(fdq4);
    cout << endl;

    cout << "Testing operator= (previous to first)" << endl;
    dq1 = dq3;
    fdq1 = fdq3;
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing max_size" << endl;
    cout << "std::deque: " << dq1.max_size() << "; ft::deque: " << fdq1.max_size() << endl;
    cout << endl;

    cout << "Testing resize (on previous deque)" << endl;
    cout << "resize(20, 3)" << endl;
    dq1.resize(20, 3);
    fdq1.resize(20, 3);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "resize(5)" << endl;
    dq1.resize(5);
    fdq1.resize(5);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Testing empty" << endl;
    cout << "On previous" << endl;
    cout << "std::deque: " << dq1.empty() << "; ft::deque: " << fdq1.empty() << endl;
    cout << endl;

    cout << "On empty" << endl;
    cout << "std::deque: " << std::deque<int>().empty() << "; ft::deque: " << ft::deque<int>().empty() << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing operator[] (on previous)" << endl;
    cout << "std::deque[2]: " << dq1[2] << "; ft::deque[2]: " << fdq1[2] << endl;
    cout << "std::deque[10]: " << dq1[10] << "; ft::deque[10]: " << fdq1[10] << endl;
    cout << endl;

    cout << "Testing at (on previous)" << endl;
    cout << "Valid" << endl;
    cout << "std::deque: " << dq1.at(3) << "; ft::deque: " << fdq1.at(3) << endl;
    cout << endl;
    cout << "Invalid" << endl;
    try {
        cout << "std::deque" << endl;
        dq1.at(10);
    } catch (std::exception&) {
        cout << "exception caught" << endl;
    }
    try {
        cout << "ft::deque" << endl;
        fdq1.at(10);
    } catch (std::exception&) {
        cout << "exception caught" << endl;
    }
    cout << endl;

    cout << "Testing front (on previous)" << endl;
    cout << "std::deque: " << dq1.front() << "; ft::deque: " << fdq1.front() << endl;
    cout << endl;

    cout << "Testing back (on previous)" << endl;
    cout << "std::deque: " << dq1.back() << "; ft::deque: " << fdq1.back() << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing assign (to previous)" << endl;
    cout << "Fill (20, 87)" << endl;
    dq1.assign(20, 87);
    fdq1.assign(20, 87);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Range (to previous from array {1,2,4,3,6,4,6,5,8})" << endl;
    int b[9] = {1,2,4,3,6,4,6,5,8};
    dq1.assign(b, b + 7);
    fdq1.assign(b, b + 7);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing push_back (99, on previous)" << endl;
    dq1.push_back(99);
    fdq1.push_back(99);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Testing push_front (-99, on previous)" << endl;
    dq1.push_front(-99);
    fdq1.push_front(-99);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Testing pop_back (on previous)" << endl;
    dq1.pop_back();
    fdq1.pop_back();
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Testing pop_front (on previous)" << endl;
    dq1.pop_front();
    fdq1.pop_front();
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing insert (on previous)" << endl;
    cout << "Single (102 before index 3)" << endl;
    dq1.insert(dq1.begin() + 3, 102);
    fdq1.insert(fdq1.begin() + 3, 102);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Fill (7 777 before index 5)" << endl;
    dq1.insert(dq1.begin() + 5, 7, 777);
    fdq1.insert(fdq1.begin() + 5, 7, 777);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Range (from array {101,909,404} before index 8)" << endl;
    int c[3] = {101, 909, 404};
    dq1.insert(dq1.begin() + 8, c, c + 3);
    fdq1.insert(fdq1.begin() + 8, c, c + 3);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Testing erase (on previous)" << endl;
    cout << "Single from index 3" << endl;
    dq1.erase(dq1.begin() + 3);
    fdq1.erase(fdq1.begin() + 3);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Range 4 to 6" << endl;
    dq1.erase(dq1.begin() + 4, dq1.begin() + 6);
    fdq1.erase(fdq1.begin() + 4, fdq1.begin() + 6);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Testing swap (previous with {0,1,2,3,4,5}" << endl;
    int d[6] = {0, 1, 2, 3, 4, 5};
    std::deque<int> dq5(d, d + 6);
    ft::deque<int> fdq5(d, d + 6);
    dq1.swap(dq5);
    fdq1.swap(fdq5);
    print_deque(dq1);
    print_deque(fdq1);
    cout << endl;

    cout << "Testing clear (on previous swapped)" << endl;
    dq5.clear();
    fdq5.clear();
    print_deque(dq5);
    print_deque(fdq5);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing relational operators" << endl;
    cout << "== with {0,1,2,3,4} and {0,1,2,3,5}" << endl;
    int rel1[5] = {0, 1, 2, 3, 4};
    int rel2[5] = {0, 1, 2, 3, 5};
    std::deque<int> reldq1(rel1, rel1 + 5);
    std::deque<int> reldq2(rel2, rel2 + 5);
    ft::deque<int> relfdq1(rel1, rel1 + 5);
    ft::deque<int> relfdq2(rel2, rel2 + 5);
    cout << "std::deque: " << (reldq1 == reldq2) << "; ft::deque: " << (relfdq1 == relfdq2) << endl;
    cout << endl;

    cout << "< with same" << endl;
    cout << "std::deque: " << (reldq1 < reldq2) << "; ft::deque: " << (relfdq1 < relfdq2) << endl;
    cout << endl;

    cout << "< with same switched places" << endl;
    cout << "std::deque: " << (reldq2 < reldq1) << "; ft::deque: " << (relfdq2 < relfdq1) << endl;
    cout << endl;
};