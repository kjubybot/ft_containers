#include "map.hpp"
#include <map>
#include <iostream>

using std::cout;
using std::endl;

template <class Key, class Val>
void print_map(ft::map<Key, Val>& m) {
    for (typename ft::map<Key, Val>::iterator it = m.begin(); it != m.end(); ++it)
        cout << it->first << " => " << it->second << " ";
    cout << endl;
}

int main() {
    ft::map<int, char> m;
    m.insert(std::pair<int, char>(43, 'b'));
    m.insert(std::pair<int, char>(48, 'c'));
    m.insert(std::pair<int, char>(3, 'd'));
    print_map(m);
}