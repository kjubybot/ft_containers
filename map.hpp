#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "rb_tree.hpp"

namespace ft {
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
    class map {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const Key, T> value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
    private:
        typedef typename Alloc::template rebind<value_type>::other pair_alloc_type;
        typedef typename ft::rb_tree<Key, value_type, key_compare, pair_alloc_type> tree_type;
        tree_type tree;
    public:
        typedef typename pair_alloc_type::reference reference;
        typedef typename pair_alloc_type::const_reference const_reference;
        typedef typename pair_alloc_type::pointer pointer;
        typedef typename pair_alloc_type::const_pointer const_pointer;
        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;
        typedef typename tree_type::reverse_iterator reverse_iterator;
        typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            tree(comp, alloc) {}

        template <class InputIterator>
        map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            tree(comp, alloc) {
            tree.insert_unique(first, last);
        }

        map(const map& x) : tree(x.tree) {}

        iterator begin()
        { return tree.begin(); }

        const_iterator begin() const
        { return tree.begin(); }

        iterator end()
        { return tree.end(); }

        const_iterator end() const
        { return tree.end(); }

        reverse_iterator rbegin()
        { return tree.rbegin(); }

        const_reverse_iterator rbegin() const
        { return tree.rbegin(); }

        reverse_iterator rend()
        { return tree.rend(); }

        const_reverse_iterator rend() const
        { return tree.rend(); }

        std::pair<iterator, bool> insert(const value_type& val)
        { return tree.insert_unique(val); }

        iterator insert(iterator position, const value_type& val)
        { return tree.insert_unique(position, val); }
    };
}

#endif
