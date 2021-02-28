#include <iostream>
#include <set>
#include "set.hpp"

using std::cout;
using std::endl;

template <class T>
void print_set(ft::set<T>& s) {
    cout << "ft::set of size " << s.size() << endl;
    for (typename ft::set<T>::iterator it = s.begin(); it != s.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

template <class T>
void print_set(std::set<T>& s) {
    cout << "std::set of size " << s.size() << endl;
    for (typename std::set<T>::iterator it = s.begin(); it != s.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int main() {
    cout << "Testing constructors" << endl;
    cout << "Empty" << endl;
    std::set<int> s1;
    ft::set<int> fs1;
    print_set(s1);
    print_set(fs1);
    cout << endl;

    cout << "Range (from array {0, -4, 5, 7, 2}" << endl;
    int a1[5] = {0, -4, 5, 7, 2};
    std::set<int> s2(a1, a1 + 5);
    ft::set<int> fs2(a1, a1 + 5);
    print_set(s2);
    print_set(fs2);
    cout << endl;

    cout << "Copy (from previous)" << endl;
    std::set<int> s3(s2);
    ft::set<int> fs3(fs2);
    print_set(s3);
    print_set(fs3);
    cout << endl;

    cout << "Testing assignment (to first from previous)" << endl;
    s1 = s3;
    fs1 = fs3;
    print_set(s1);
    print_set(fs1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing empty" << endl << "On empty" << endl;
    cout << "std::set: " << std::set<int>().empty() << "; ft::set: " << ft::set<int>().empty() << endl;
    cout << endl << "On previous" << endl;
    cout << "std::set: " << s3.empty() << "; ft::set: " << fs3.empty() << endl;
    cout << endl;

    cout << "Testing size (on previous)" << endl;
    cout << "std::set: " << s3.size() << "; ft::set: " << fs3.size() << endl;
    cout << endl;

    cout << "Testing max_size (on previous)" << endl;
    cout << "std::set: " << s3.max_size() << "; ft::set: " << fs3.max_size() << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing insert (on previous)" << endl;
    cout << "Single 99" << endl;
    std::pair<std::set<int>::iterator, bool> mr3 = s3.insert(99);
    cout << "std::set: " << *mr3.first << ", " << mr3.second << endl;
    std::pair<ft::set<int>::iterator, bool> fmr3 = fs3.insert(99);
    cout << "ft::set: " << *fmr3.first << ", " << fmr3.second << endl;
    print_set(s3);
    print_set(fs3);
    cout << endl;

    cout << "Range (from array {7, 7, 8})" << endl;
    int a2[3] = {7, 7, 8};
    s3.insert(a2, a2 + 3);
    fs3.insert(a2, a2 + 3);
    print_set(s3);
    print_set(fs3);
    cout << endl;

    cout << "Testing erase (on previous)" << endl;
    cout << "With iterator begin()" << endl;
    s3.erase(s3.begin());
    fs3.erase(fs3.begin());
    print_set(s3);
    print_set(fs3);
    cout << endl;

    cout << "With key 7" << endl;
    s3.erase(7);
    fs3.erase(7);
    print_set(s3);
    print_set(fs3);
    cout << endl;

    cout << "Range (second to fourth)" << endl;
    std::set<int>::iterator it1 = s3.begin();
    ++it1;
    std::set<int>::iterator it2 = it1;
    ++it2; ++it2;
    s3.erase(it1, it2);
    ft::set<int>::iterator fit1 = fs3.begin();
    ++fit1;
    ft::set<int>::iterator fit2 = fit1;
    ++fit2; ++fit2;
    fs3.erase(fit1, fit2);
    print_set(s3);
    print_set(fs3);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing swap (previous with second)" << endl;
    cout << "Before" << endl;
    print_set(s3);
    print_set(fs3);
    s3.swap(s2);
    fs3.swap(fs2);
    cout << "After" << endl;
    print_set(s3);
    print_set(fs3);
    cout << endl;

    cout << "Testing clear (on second swapped)" << endl;
    cout << "Before" << endl;
    print_set(s2);
    print_set(fs2);
    s2.clear();
    fs2.clear();
    cout << "After" << endl;
    print_set(s2);
    print_set(fs2);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing key_comp" << endl;
    cout << "On 5 and 5" << endl;
    cout << "std::set: " << s3.key_comp()(5, 5) << "; ft::set: " << fs3.key_comp()(5, 5) << endl;
    cout << "On 3 and 6" << endl;
    cout << "std::set: " << s3.key_comp()(3, 6) << "; ft::set: " << fs3.key_comp()(3, 6) << endl;
    cout << endl;

    cout << "Testing value_comp" << endl;
    cout << "On 5 and 5" << endl;
    cout << "std::set: " << s3.value_comp()(5, 5) <<
         "; ft::set: " << fs3.value_comp()(5, 5) << endl;
    cout << "On 3 and 7" << endl;
    cout << "std::set: " << s3.value_comp()(3, 7) <<
         "; ft::set: " << fs3.value_comp()(3, 7) << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing find (on previous)" << endl;
    print_set(s3);
    print_set(fs3);
    cout << "Existing (2)" << endl;
    cout << "std::set: " << *s3.find(2) << "; ft::set: " << *fs3.find(2) << endl;
    cout << "Nonexistent (iter == end())" << endl;
    cout << "std::set: " << (s3.find(7) == s3.end()) << "; ft::set: " << (fs3.find(7) == fs3.end()) << endl;
    cout << endl;

    cout << "Testing count (on previous)" << endl;
    cout << "Existing (2)" << endl;
    cout << "std::set: " << s3.count(2) << "; ft::set: " << fs3.count(2) << endl;
    cout << "Nonexstent (9)" << endl;
    cout << "std::set: " << s3.count(9) << "; ft::set: " << fs3.count(9) << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing lower_bound (on previous)" << endl;
    cout << "Using 2" << endl;
    cout << "std::set: " << *s3.lower_bound(2) << "; ft::set: " << *fs3.lower_bound(2) << endl;
    cout << endl;

    cout << "Testing upper_bound (on previous)" << endl;
    cout << "Using 2" << endl;
    cout << "std::set: " << *s3.upper_bound(2) << "; ft::set: " << *fs3.upper_bound(2) << endl;
    cout << endl;

    cout << "Testing equal_range (on previous)" << endl;
    cout << "Existent 2" << endl;
    cout << "std::set: " << *s3.equal_range(2).first << " to " << *s3.equal_range(2).second <<
         "; ft::set: " << *fs3.equal_range(2).first << " to " << *fs3.equal_range(2).second << endl;
    cout << "Nonexistent (first == second == end())" << endl;
    cout << "std::set: " << (s3.equal_range(9).first == s3.equal_range(9).second && s3.equal_range(9).second == s3.end()) <<
         "; ft::set: " << (fs3.equal_range(9).first == fs3.equal_range(9).second && fs3.equal_range(9).second == fs3.end()) << endl;

};