#include "map.hpp"
#include <map>
#include <iostream>

using std::cout;
using std::endl;

template <class Key, class Val>
void print_map(ft::map<Key, Val>& m) {
    cout << "ft::map of size " << m.size() << endl;
    for (typename ft::map<Key, Val>::iterator it = m.begin(); it != m.end(); ++it)
        cout << it->first << " => " << it->second << " ";
    cout << endl;
}

template <class Key, class Val>
void print_map(std::map<Key, Val>& m) {
    cout << "std::map of size " << m.size() << endl;
    for (typename std::map<Key, Val>::iterator it = m.begin(); it != m.end(); ++it)
        cout << it->first << " => " << it->second << " ";
    cout << endl;
}

int main() {
    typedef std::pair<int, std::string> test_pair;

    cout << "Testing constructors" << endl;
    cout << "Empty" << endl;
    std::map<int, std::string> m1;
    ft::map<int, std::string> fm1;
    print_map(m1);
    print_map(fm1);
    cout << endl;

    cout << "Range (from array {(0, 'a'), (1, 'b'), (2, 'c'), (3, 'd')}" << endl;
    test_pair a1[4] = {test_pair(0, "a"),
                       test_pair(1, "b"),
                       test_pair(2, "c"),
                       test_pair(3, "d")};
    std::map<int, std::string> m2(a1, a1 + 4);
    ft::map<int, std::string> fm2(a1, a1 + 4);
    print_map(m2);
    print_map(fm2);
    cout << endl;

    cout << "Copy (from previous)" << endl;
    std::map<int, std::string> m3(m2);
    ft::map<int, std::string> fm3(fm2);
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
    cout << "std::map: " << std::map<int, std::string>().empty() << "; ft::map: " << ft::map<int, std::string>().empty() << endl;
    cout << endl << "On previous" << endl;
    cout << "std::map: " << m3.empty() << "; ft::map: " << fm3.empty() << endl;
    cout << endl;

    cout << "Testing size (on previous)" << endl;
    cout << "std::map: " << m3.size() << "; ft::map: " << fm3.size() << endl;
    cout << endl;

    cout << "Testing max_size (on previous)" << endl;
    cout << "std::map: " << m3.max_size() << "; ft::map: " << fm3.max_size() << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing operator[] (on previous)" << endl;
    cout << "Existing [2]" << endl;
    cout << "std::map: " << m3[2] << "; ft::map: " << fm3[2] << endl << endl;
    cout << "Not existing [-1]" << endl;
    cout << "std::map: " << m3[-1] << "; ft::map: " << fm3[-1] << endl << endl;
    cout << "Assigning 'qwer' to [4]" << endl;
    m3[4] = "qwer";
    fm3[4] = "qwer";
    cout << "std::map: " << m3[4] << "; ft::map: " << fm3[4] << endl << endl;
    cout << "Assigning 'asdf' to [0]" << endl;
    m3[0] = "asdf";
    fm3[0] = "asdf";
    cout << "std::map: " << m3[0] << "; ft::map: " << fm3[0] << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing insert (on previous)" << endl;
    cout << "Single (99, 'ff')" << endl;
    std::pair<std::map<int, std::string>::iterator, bool> mr3 = m3.insert(test_pair(99, "ff"));
    cout << "std::map: " << (*mr3.first).first << ", " << mr3.second << endl;
    std::pair<ft::map<int, std::string>::iterator, bool> fmr3 = fm3.insert(test_pair(99, "ff"));
    cout << "ft::map: " << (*fmr3.first).first << ", " << fmr3.second << endl;
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
    std::map<int, std::string>::iterator it1 = m3.begin();
    ++it1;
    std::map<int, std::string>::iterator it2 = it1;
    ++it2; ++it2;
    m3.erase(it1, it2);
    ft::map<int, std::string>::iterator fit1 = fm3.begin();
    ++fit1;
    ft::map<int, std::string>::iterator fit2 = fit1;
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
    cout << "std::map: " << m3.key_comp()(5, 5) << "; ft::map: " << fm3.key_comp()(5, 5) << endl;
    cout << "On 3 and 6" << endl;
    cout << "std::map: " << m3.key_comp()(3, 6) << "; ft::map: " << fm3.key_comp()(3, 6) << endl;
    cout << endl;

    cout << "Testing value_comp" << endl;
    cout << "On (5, 'a') and (5, 'b')" << endl;
    cout << "std::map: " << m3.value_comp()(test_pair(5, "a"), test_pair(5, "b")) <<
        "; ft::map: " << fm3.value_comp()(test_pair(5, "a"), test_pair(5, "b")) << endl;
    cout << "On (3, 'qw') and (7, 'qw')" << endl;
    cout << "std::map: " << m3.value_comp()(test_pair(3, "qw"), test_pair(7, "qw")) <<
        "; ft::map: " << fm3.value_comp()(test_pair(3, "qw"), test_pair(7, "qw)")) << endl;
    cout << endl;

    cout << "========" << endl;
    cout << "Testing find (on previous)" << endl;

};