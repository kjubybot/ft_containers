#include <iostream>
#include <list>
#include "list.hpp"

using std::cout;
using std::endl;

bool iseven(int n) { return !(n & 1); }
bool b10(int n) { return n > 10; }
bool ab4(int a, int b) { return a + b == 4; }

template <class T>
void print_list(std::list<T> l) {
    cout << "std::list of size " << l.size() << endl;
    for (typename std::list<T>::iterator it = l.begin(); it != l.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

template <class T>
void print_list(ft::list<T> l) {
    cout << "std::list of size " << l.size() << endl;
    for (typename ft::list<T>::iterator it = l.begin(); it != l.end(); ++it)
        cout << *it << " ";
    cout << endl;
}


int main() {
    cout << "Testing constructors" << endl;
    cout << "Empty" << endl;
    std::list<int> l1;
    ft::list<int> fl1;
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Fill (10, 404)" << endl;
    std::list<int> l2(10, 404);
    ft::list<int> fl2(10, 404);
    print_list(l2);
    print_list(fl2);
    cout << endl;

    cout << "Range (from array {0, 8, 9, 7})" << endl;
    int a1[4] = {0, 8, 9, 7};
    std::list<int> l3(a1, a1 + 4);
    ft::list<int> fl3(a1, a1 + 4);
    print_list(l3);
    print_list(fl3);
    cout << endl;

    cout << "Copy (from previous)" << endl;
    std::list<int> l4(l3);
    ft::list<int> fl4(fl3);
    print_list(l4);
    print_list(fl4);
    cout << endl;

    cout << "Testing assignment (to empty from second)" << endl;
    l1 = l2;
    fl1 = fl2;
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing empty" << endl;
    cout << "On empty" << endl;
    cout << "std::list: " << std::list<int>().empty() << "; ft::list: " << ft::list<int>().empty() << endl;
    cout << "On previous" << endl;
    cout << "std::list: " << l1.empty() << "; ft::list: " << fl1.empty() << endl << endl;

    cout << "Testing size" << endl;
    cout << "On empty" << endl;
    cout << "std::list: " << std::list<int>().size() << "; ft::list: " << ft::list<int>().size() << endl;
    cout << "On previous" << endl;
    cout << "std::list: " << l1.size() << "; ft::list: " << fl1.size() << endl << endl;

    cout << "Testing max_size" << endl;
    cout << "std::list: " << l1.max_size() << "; ft::list: " << fl1.max_size() << endl << endl;

    cout << "========" << endl;
    cout << "Testing front (on previous)" << endl;
    cout << "std::list: " << l1.front() << "; ft::list: " << fl1.front() << endl << endl;

    cout << "Testing back (on previous + 24)" << endl;
    l1.push_back(24);
    fl1.push_back(24);
    cout << "std::list: " << l1.back() << "; ft::list: " << fl1.back() << endl << endl;

    cout << "Testing assign (on previous)" << endl;
    cout << "Range (from array {1, 2, 3, 4, 5})" << endl;
    int a2[5] = {1, 2, 3, 4, 5};
    l1.assign(a2, a2 + 5);
    fl1.assign(a2, a2 + 5);
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Fill (10, -5)" << endl;
    l1.assign(10, -5);
    fl1.assign(10, -5);
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Testing push_front (999 on previous)" << endl;
    l1.push_front(999);
    fl1.push_front(999);
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Testing push_back (-999 on previous)" << endl;
    l1.push_back(-999);
    fl1.push_back(-999);
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Testing pop_front (on previous)" << endl;
    l1.pop_front();
    fl1.pop_front();
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Testing pop_back (on previous)" << endl;
    l1.pop_back();
    fl1.pop_back();
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing insert (on previous)" << endl;
    cout << "Single before fourth" << endl;
    std::list<int>::iterator it1 = l1.begin();
    ft::list<int>::iterator fit1 = fl1.begin();
    std::advance(it1, 3);
    std::advance(fit1, 3);
    l1.insert(it1, 90);
    fl1.insert(fit1, 90);
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Fill (4, 88) before last (not end()!)" << endl;
    it1 = l1.end();
    --it1;
    fit1 = fl1.end();
    --fit1;
    l1.insert(it1, 4, 88);
    fl1.insert(fit1, 4, 88);
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Range from array {4, 0, 1} before first" << endl;
    it1 = l1.begin();
    fit1 = fl1.begin();
    int a3[3] = {4, 0, 1};
    l1.insert(it1, a3, a3 + 3);
    fl1.insert(fit1, a3, a3 + 3);
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Testing erase (on previous)" << endl;
    cout << "Single (fourth)" << endl;
    it1 = l1.begin();
    fit1 = fl1.begin();
    std::advance(it1, 3);
    std::advance(fit1, 3);
    l1.erase(it1);
    fl1.erase(fit1);
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Range (last three)" << endl;
    it1 = l1.end();
    fit1 = fl1.end();
    std::advance(it1, -3);
    std::advance(fit1, -3);
    l1.erase(it1, l1.end());
    fl1.erase(fit1, fl1.end());
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing swap (previous with second)" << endl;
    cout << "Before" << endl;
    print_list(l1);
    print_list(fl1);
    l1.swap(l2);
    fl1.swap(fl2);
    cout << endl;
    cout << "After" << endl;
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "Testing resize (on previous swapped)" << endl;
    cout << "5" << endl;
    l2.resize(5);
    fl2.resize(5);
    print_list(l2);
    print_list(fl2);
    cout << "(10, 789)" << endl;
    l2.resize(10, 789);
    fl2.resize(10, 789);
    print_list(l2);
    print_list(fl2);
    cout << endl;

    cout << "Testing clear (on first)" << endl;
    l1.clear();
    fl1.clear();
    print_list(l1);
    print_list(fl1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing splice (on previous)" << endl;
    cout << "Entire list from list {1, 2, 3, 4} before third" << endl;
    std::list<int> l5;
    ft::list<int> fl5;
    for (int i = 1; i <= 4; ++i) {
        l5.push_back(i);
        fl5.push_back(i);
    }
    it1 = l2.begin();
    fit1 = fl2.begin();
    std::advance(it1, 2);
    std::advance(fit1, 2);
    l2.splice(it1, l5);
    fl2.splice(fit1, fl5);
    print_list(l2);
    print_list(fl2);
    cout << "Spliced from" << endl;
    print_list(l5);
    print_list(fl5);
    cout << endl;

    cout << "Single (second) from list {9, 8, 9} before end" << endl;
    l5.push_back(9); l5.push_back(8); l5.push_back(9);
    fl5.push_back(9); fl5.push_back(8); fl5.push_back(9);
    it1 = l2.end();
    fit1 = fl2.end();
    std::list<int>::iterator it2 = l5.begin();
    ft::list<int>::iterator fit2 = fl5.begin();
    ++it2;
    ++fit2;
    l2.splice(it1, l5, it2);
    fl2.splice(fit1, fl5, fit2);
    print_list(l2);
    print_list(fl2);
    cout << "Spliced from" << endl;
    print_list(l5);
    print_list(fl5);
    cout << endl;

    cout << "Range (second to third) from list {9, 9, 1, 1} before first" << endl;
    l5.push_back(1); l5.push_back(1);
    fl5.push_back(1); fl5.push_back(1);
    it1 = l5.begin();
    fit1 = fl5.begin();
    ++it1;
    ++fit1;
    it2 = it1;
    fit2 = fit1;
    std::advance(it2, 2);
    std::advance(fit2, 2);
    l2.splice(l2.begin(), l5, it1, it2);
    fl2.splice(fl2.begin(), fl5, fit1, fit2);
    print_list(l2);
    print_list(fl2);
    cout << "Spliced from" << endl;
    print_list(l5);
    print_list(fl5);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing remove (on previous)" << endl;
    cout << "Nonexistent (999)" << endl;
    l2.remove(999);
    fl2.remove(999);
    print_list(l2);
    print_list(fl2);
    cout << endl;
    cout << "Existing (789)" << endl;
    l2.remove(789);
    fl2.remove(789);
    print_list(l2);
    print_list(fl2);
    cout << endl;

    cout << "Testing remove_if (on previous)" << endl;
    cout << "Removing even" << endl;
    l2.remove_if(iseven);
    fl2.remove_if(iseven);
    print_list(l2);
    print_list(fl2);
    cout << endl;

    cout << "Removing n > 10" << endl;
    l2.remove_if(b10);
    fl2.remove_if(b10);
    print_list(l2);
    print_list(fl2);
    cout << endl;

    cout << "Testing unique (on previous)" << endl;
    cout << "Without predicate" << endl;
    l2.unique();
    fl2.unique();
    print_list(l2);
    print_list(fl2);
    cout << endl;

    cout << "With predicate (a + b == 4)" << endl;
    l2.unique(ab4);
    fl2.unique(ab4);
    print_list(l2);
    print_list(fl2);
    cout << endl;

    cout << "Testing sort (on {0, 4, 7, 3, -5, 9, 83, -4, -5, 1}" << endl;
    int a4[10] = {4, 0, 7, 3, -5, 9, 83, -4, -5, 1};
    std::list<int> l6(a4, a4 + 10);
    ft::list<int> fl6(a4, a4 + 10);
    l6.sort();
    fl6.sort();
    print_list(l6);
    print_list(fl6);
    cout << endl;

    cout << "Testing merge (on previous with {-7, 4, 13, 65})" << endl;
    int a5[4] = {-7, 4, 13, 65};
    std::list<int> l7(a5, a5 + 4);
    ft::list<int> fl7(a5, a5 + 4);
    l6.merge(l7);
    fl6.merge(fl7);
    print_list(l6);
    print_list(fl6);
    cout << endl;

    cout << "Testing reverse (on previous)" << endl;
    l6.reverse();
    fl6.reverse();
    print_list(l6);
    print_list(fl6);
}
