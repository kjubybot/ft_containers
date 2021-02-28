#ifndef FT_CONTAINERS_MULTISET_HPP
#define FT_CONTAINERS_MULTISET_HPP

#include <functional>
#include "rb_tree.hpp"
#include "functional.hpp"

namespace ft {
    template <class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
    class multiset {
    public:
        typedef T key_type;
        typedef T value_type;
        typedef Compare key_compare;
        typedef Compare value_compare;
        typedef Alloc allocator_type;
    private:
        typedef typename ft::rb_tree<key_type, value_type, identity<value_type>, key_compare, allocator_type> tree_type;
        tree_type tree;
    public:
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename tree_type::iterator iterator;
        typedef typename tree_type::const_iterator const_iterator;
        typedef typename tree_type::reverse_iterator reverse_iterator;
        typedef typename tree_type::const_reverse_iterator const_reverse_iterator;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

        explicit multiset(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
                tree(comp, alloc) {}

        template <class InputIterator>
        multiset(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
                tree(comp, alloc) {
            tree.insert_equal(first, last);
        }

        multiset(const multiset& x) : tree(x.tree) {}

        multiset& operator=(const multiset& x) {
            tree = x.tree;
            return *this;
        }

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

        bool empty() const
        { return tree.empty(); }

        size_type size() const
        { return tree.size(); }

        size_type max_size() const
        { return tree.max_size(); }

        iterator insert(const value_type& val)
        { return tree.insert_equal(val); }

        iterator insert(iterator position, const value_type& val)
        { return tree.insert_equal(position, val); }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        { tree.insert_equal(first, last); }

        void erase(iterator position)
        { tree.erase(position); }

        size_type erase(const key_type& key)
        { return tree.erase(key); }

        void erase(iterator first, iterator last)
        { tree.erase(first, last); }

        void swap(multiset& x)
        { tree.swap(x.tree); }

        void clear()
        { tree.clear(); }

        key_compare key_comp() const
        { return tree.key_comp(); }

        value_compare value_comp() const
        { return value_compare(tree.key_comp()); }

        iterator find(const key_type& key)
        { return tree.find(key); }

        const_iterator find(const key_type& key) const
        { return tree.find(key); }

        size_type count(const key_type& key) const
        { return tree.count(key); }

        iterator lower_bound(const key_type& key)
        { return tree.lower_bound(key); }

        const_iterator lower_bound(const key_type& key) const
        { return tree.lower_bound(key); }

        iterator upper_bound(const key_type& key)
        { return tree.upper_bound(key); }

        const_iterator upper_bound(const key_type& key) const
        { return tree.upper_bound(key); }

        std::pair<iterator, iterator> equal_range(const key_type& key)
        { return tree.equal_range(key); }

        std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
        { return tree.equal_range(key); }

        allocator_type get_allocator() const
        { return tree.get_allocator(); }
    };
}


#endif
