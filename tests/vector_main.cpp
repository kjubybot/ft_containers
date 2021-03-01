#include <iostream>
#include <vector>
#include "vector.hpp"

using std::cout;
using std::endl;

template <class T>
void print_vector(const std::vector<T>& vec) {
    cout << "std::vector of size " << vec.size() << endl;
    for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

template <class T>
void print_vector(const ft::vector<T>& vec) {
    cout << "ft::vector of size " << vec.size() << endl;
    for (typename ft::vector<T>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    cout << "Testing constructors" << endl;
    cout << "Empty" << endl;
    std::vector<int> v1;
    ft::vector<int> fv1;
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "Fill (10, 404)" << endl;
    std::vector<int> v2(10, 404);
    ft::vector<int> fv2(10, 404);
    print_vector(v2);
    print_vector(fv2);
    cout << endl;

    cout << "Range (from array {0, 8, 9, 7})" << endl;
    int a1[4] = {0, 8, 9, 7};
    std::vector<int> v3(a1, a1 + 4);
    ft::vector<int> fv3(a1, a1 + 4);
    print_vector(v3);
    print_vector(fv3);
    cout << endl;

    cout << "Copy (from previous)" << endl;
    std::vector<int> v4(v3);
    ft::vector<int> fv4(fv3);
    print_vector(v4);
    print_vector(fv4);
    cout << endl;

    cout << "Testing assignment (to empty from second)" << endl;
    v1 = v2;
    fv1 = fv2;
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing empty" << endl;
    cout << "On empty" << endl;
    cout << "std::vector: " << std::vector<int>().empty() << "; ft::vector: " << ft::vector<int>().empty() << endl;
    cout << "On previous" << endl;
    cout << "std::vector: " << v1.empty() << "; ft::vector: " << fv1.empty() << endl << endl;

    cout << "Testing size" << endl;
    cout << "On empty" << endl;
    cout << "std::vector: " << std::vector<int>().size() << "; ft::vector: " << ft::vector<int>().size() << endl;
    cout << "On previous" << endl;
    cout << "std::vector: " << v1.size() << "; ft::vector: " << fv1.size() << endl << endl;

    cout << "Testing max_size" << endl;
    cout << "std::vector: " << v1.max_size() << "; ft::vector: " << fv1.max_size() << endl << endl;

    cout << "Testing reserve (on previous)" << endl;
    cout << "Before\nstd::vector: " << v1.capacity() << "; ft::vector: " << fv1.capacity() << endl;
    v1.reserve(50);
    fv1.reserve(50);
    cout << "After\nstd::vector: " << v1.capacity() << "; ft::vector: " << fv1.capacity() << endl << endl;

    cout << "========" << endl;
    cout << "Testing operator[] (on previous)" << endl;
    cout << "Read at 2" << endl;
    cout << "std::vector: " << v1[2] << "; ft::vector: " << fv1[2] << endl;
    cout << "Write at 1" << endl;
    v1[1] = 45;
    fv1[1] = 45;
    cout << "std::vector: " << v1[1] << "; ft::vector: " << fv1[1] << endl << endl;

    cout << "Testing at (on previous)" << endl;
    cout << "Existing (1)" << endl;
    cout << "std::vector: " << v1.at(1) << "; ft::vector: " << fv1.at(1) << endl;
    cout << "Nonexistent (40)" << endl;
    try {
        cout << "std::vector: ";
        v1.at(40);
    } catch (std::exception&) {
        cout << "exception caught" << endl;
    }
    try {
        cout << "ft::vector: ";
        fv1.at(40);
    } catch (std::exception&) {
        cout << "exception caught" << endl;
    }
    cout << endl;

    cout << "Testing front (on previous)" << endl;
    cout << "std::vector: " << v1.front() << "; ft::vector: " << fv1.front() << endl << endl;

    cout << "Testing back (on previous + 24)" << endl;
    v1.push_back(24);
    fv1.push_back(24);
    cout << "std::vector: " << v1.back() << "; ft::vector: " << fv1.back() << endl << endl;

    cout << "Testing assign (on previous)" << endl;
    cout << "Range (from array {1, 2, 3, 4, 5})" << endl;
    int a2[5] = {1, 2, 3, 4, 5};
    v1.assign(a2, a2 + 5);
    fv1.assign(a2, a2 + 5);
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "Fill (10, -5)" << endl;
    v1.assign(10, -5);
    fv1.assign(10, -5);
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "Testing push_back (-999 on previous)" << endl;
    v1.push_back(-999);
    fv1.push_back(-999);
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "Testing pop_back (on previous)" << endl;
    v1.pop_back();
    fv1.pop_back();
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing insert (on previous)" << endl;
    cout << "Single before fourth" << endl;
    std::vector<int>::iterator it1 = v1.begin();
    ft::vector<int>::iterator fit1 = fv1.begin();
    std::advance(it1, 3);
    std::advance(fit1, 3);
    v1.insert(it1, 90);
    fv1.insert(fit1, 90);
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "Fill (4, 88) before last (not end()!)" << endl;
    it1 = v1.end();
    --it1;
    fit1 = fv1.end();
    --fit1;
    v1.insert(it1, 4, 88);
    fv1.insert(fit1, 4, 88);
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "Range from array {4, 0, 1} before first" << endl;
    it1 = v1.begin();
    fit1 = fv1.begin();
    int a3[3] = {4, 0, 1};
    v1.insert(it1, a3, a3 + 3);
    fv1.insert(fit1, a3, a3 + 3);
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "Testing erase (on previous)" << endl;
    cout << "Single (fourth)" << endl;
    it1 = v1.begin();
    fit1 = fv1.begin();
    std::advance(it1, 3);
    std::advance(fit1, 3);
    v1.erase(it1);
    fv1.erase(fit1);
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "Range (last three)" << endl;
    it1 = v1.end();
    fit1 = fv1.end();
    std::advance(it1, -3);
    std::advance(fit1, -3);
    v1.erase(it1, v1.end());
    fv1.erase(fit1, fv1.end());
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing swap (previous with second)" << endl;
    cout << "Before" << endl;
    print_vector(v1);
    print_vector(fv1);
    v1.swap(v2);
    fv1.swap(fv2);
    cout << endl;
    cout << "After" << endl;
    print_vector(v1);
    print_vector(fv1);
    cout << endl;

    cout << "Testing resize (on previous swapped)" << endl;
    cout << "5" << endl;
    v2.resize(5);
    fv2.resize(5);
    print_vector(v2);
    print_vector(fv2);
    cout << "(10, 789)" << endl;
    v2.resize(10, 789);
    fv2.resize(10, 789);
    print_vector(v2);
    print_vector(fv2);
    cout << endl;

    cout << "Testing clear (on first)" << endl;
    v1.clear();
    fv1.clear();
    print_vector(v1);
    print_vector(fv1);
    cout << endl;
}