#include "multimap.hpp"
#include <map>
#include <iostream>

using std::cout;
using std::endl;

template <class Key, class Val>
void print_map(ft::multimap<Key, Val>& m) {
    cout << "ft::multimap of size " << m.size() << endl;
    for (typename ft::multimap<Key, Val>::iterator it = m.begin(); it != m.end(); ++it)
        cout << it->first << " => " << it->second << " ";
    cout << endl;
}

template <class Key, class Val>
void print_map(std::multimap<Key, Val>& m) {
    cout << "std::multimap of size " << m.size() << endl;
    for (typename std::multimap<Key, Val>::iterator it = m.begin(); it != m.end(); ++it)
        cout << it->first << " => " << it->second << " ";
    cout << endl;
}

int main() {
    typedef std::pair<int, std::string> test_pair;

    cout << "Testing constructors" << endl;
    cout << "Empty" << endl;
    std::multimap<int, std::string> m1;
    ft::multimap<int, std::string> fm1;
    print_map(m1);
    print_map(fm1);
    cout << endl;

    cout << "Range (from array {(0, 'a'), (1, 'b'), (2, 'c'), (3, 'd')}" << endl;
    test_pair a1[4] = {test_pair(0, "a"),
                       test_pair(1, "b"),
                       test_pair(2, "c"),
                       test_pair(3, "d")};
    std::multimap<int, std::string> m2(a1, a1 + 4);
    ft::multimap<int, std::string> fm2(a1, a1 + 4);
    print_map(m2);
    print_map(fm2);
    cout << endl;

    cout << "Copy (from previous)" << endl;
    std::multimap<int, std::string> m3(m2);
    ft::multimap<int, std::string> fm3(fm2);
    print_map(m3);
    print_map(fm3);
    cout << endl;

    cout << "Testing assignment (to first from previous)" << endl;
    m1 = m3;
    fm1 = fm3;
    print_map(m1);
    print_map(fm1);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing empty" << endl << "On empty" << endl;
    cout << "std::multimap: " << std::multimap<int, std::string>().empty() << "; ft::multimap: " << ft::multimap<int, std::string>().empty() << endl;
    cout << endl << "On previous" << endl;
    cout << "std::multimap: " << m3.empty() << "; ft::multimap: " << fm3.empty() << endl;
    cout << endl;

    cout << "Testing size (on previous)" << endl;
    cout << "std::multimap: " << m3.size() << "; ft::multimap: " << fm3.size() << endl;
    cout << endl;

    cout << "Testing max_size (on previous)" << endl;
    cout << "std::multimap: " << m3.max_size() << "; ft::multimap: " << fm3.max_size() << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing insert (on previous)" << endl;
    cout << "Single (99, 'ff')" << endl;
    std::multimap<int, std::string>::iterator mr3 = m3.insert(test_pair(99, "ff"));
    cout << "std::multimap: " << mr3->second << endl;
    ft::multimap<int, std::string>::iterator fmr3 = fm3.insert(test_pair(99, "ff"));
    cout << "ft::multimap: " << fmr3->second << endl;
    print_map(m3);
    print_map(fm3);
    cout << endl;

    cout << "Range (from array {(7, 'q'), (7, 'w'), (8, 'e')}" << endl;
    test_pair a2[3] = {test_pair(7, "q"), test_pair(7, "w"), test_pair(8, "e")};
    m3.insert(a2, a2 + 3);
    fm3.insert(a2, a2 + 3);
    print_map(m3);
    print_map(fm3);
    cout << endl;

    cout << "Testing erase (on previous)" << endl;
    cout << "With iterator begin()" << endl;
    m3.erase(m3.begin());
    fm3.erase(fm3.begin());
    print_map(m3);
    print_map(fm3);
    cout << endl;

    cout << "With key 7" << endl;
    m3.erase(7);
    fm3.erase(7);
    print_map(m3);
    print_map(fm3);
    cout << endl;

    cout << "Range (second to fourth)" << endl;
    std::multimap<int, std::string>::iterator it1 = m3.begin();
    ++it1;
    std::multimap<int, std::string>::iterator it2 = it1;
    ++it2; ++it2;
    m3.erase(it1, it2);
    ft::multimap<int, std::string>::iterator fit1 = fm3.begin();
    ++fit1;
    ft::multimap<int, std::string>::iterator fit2 = fit1;
    ++fit2; ++fit2;
    fm3.erase(fit1, fit2);
    print_map(m3);
    print_map(fm3);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing swap (previous with second)" << endl;
    cout << "Before" << endl;
    print_map(m3);
    print_map(fm3);
    m3.swap(m2);
    fm3.swap(fm2);
    cout << "After" << endl;
    print_map(m3);
    print_map(fm3);
    cout << endl;

    cout << "Testing clear (on second swapped)" << endl;
    cout << "Before" << endl;
    print_map(m2);
    print_map(fm2);
    m2.clear();
    fm2.clear();
    cout << "After" << endl;
    print_map(m2);
    print_map(fm2);
    cout << endl;

    cout << "========" << endl;
    cout << "Testing key_comp" << endl;
    cout << "On 5 and 5" << endl;
    cout << "std::multimap: " << m3.key_comp()(5, 5) << "; ft::multimap: " << fm3.key_comp()(5, 5) << endl;
    cout << "On 3 and 6" << endl;
    cout << "std::multimap: " << m3.key_comp()(3, 6) << "; ft::multimap: " << fm3.key_comp()(3, 6) << endl;
    cout << endl;

    cout << "Testing value_comp" << endl;
    cout << "On (5, 'a') and (5, 'b')" << endl;
    cout << "std::multimap: " << m3.value_comp()(test_pair(5, "a"), test_pair(5, "b")) <<
         "; ft::multimap: " << fm3.value_comp()(test_pair(5, "a"), test_pair(5, "b")) << endl;
    cout << "On (3, 'qw') and (7, 'qw')" << endl;
    cout << "std::multimap: " << m3.value_comp()(test_pair(3, "qw"), test_pair(7, "qw")) <<
         "; ft::multimap: " << fm3.value_comp()(test_pair(3, "qw"), test_pair(7, "qw)")) << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing find (on previous)" << endl;
    print_map(m3);
    print_map(fm3);
    cout << "Existing (2)" << endl;
    cout << "std::multimap: " << (*m3.find(2)).second << "; ft::multimap: " << (*fm3.find(2)).second << endl;
    cout << "Nonexistent (iter == end())" << endl;
    cout << "std::multimap: " << (m3.find(7) == m3.end()) << "; ft::multimap: " << (fm3.find(7) == fm3.end()) << endl;
    cout << endl;

    cout << "Testing count (on previous + (3, 'another'))" << endl;
    m3.insert(std::pair<int, std::string>(3, "another"));
    fm3.insert(std::pair<int, std::string>(3, "another"));
    cout << "Existing (3)" << endl;
    cout << "std::multimap: " << m3.count(3) << "; ft::multimap: " << fm3.count(3) << endl;
    cout << "Nonexstent (9)" << endl;
    cout << "std::multimap: " << m3.count(9) << "; ft::multimap: " << fm3.count(9) << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing lower_bound (on previous)" << endl;
    cout << "Using 2" << endl;
    cout << "std::multimap: " << m3.lower_bound(2)->second << "; ft::multimap: " << fm3.lower_bound(2)->second << endl;
    cout << endl;

    cout << "Testing upper_bound (on previous)" << endl;
    cout << "Using 2" << endl;
    cout << "std::multimap: " << m3.upper_bound(2)->second << "; ft::multimap: " << fm3.upper_bound(2)->second << endl;
    cout << endl;

    cout << "Testing equal_range (on previous)" << endl;
    cout << "Existent 2" << endl;
    cout << "std::multimap: " << m3.equal_range(2).first->second << " to " << m3.equal_range(2).second->second <<
         "; ft::multimap: " << fm3.equal_range(2).first->second << " to " << fm3.equal_range(2).second->second << endl;
    cout << "Nonexistent (first == second == end())" << endl;
    cout << "std::multimap: " << (m3.equal_range(9).first == m3.equal_range(9).second && m3.equal_range(9).second == m3.end()) <<
         "; ft::multimap: " << (fm3.equal_range(9).first == fm3.equal_range(9).second && fm3.equal_range(9).second == fm3.end()) << endl;

};
