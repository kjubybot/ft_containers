#ifndef FT_CONTAINERS_LIST_H
#define FT_CONTAINERS_LIST_H

#include <cstddef>
#include <iterator>
#include <limits>

namespace ft {
    template <class T>
    struct ListNode {
        T data;
        ListNode<T>* next;
        ListNode<T>* prev;

        ListNode() : data(), next(0), prev(0) {}
        ListNode(const T& val) : data(val), next(0), prev(0) {}
    };

    template <class T>
    struct list_iterator {
        typedef list_iterator<T> _Self;
        ListNode<T>* node;

        list_iterator() : node() {}
        list_iterator(ListNode<T>* node) : node(node) {}
        list_iterator(const _Self& x) : node(x.node) {}
        list_iterator& operator=(const _Self& x) { node = x.node; return *this; }

        bool operator==(const _Self& x) const { return node == x.node; }
        bool operator!=(const _Self& x) const { return node != x.node; }
        T& operator*() const { return node->data; }
        T* operator->() const { return &node->data; }
        _Self& operator++() { node = node->next; return *this; }
        _Self& operator++(int) { _Self tmp = *this; node = node->next; return tmp; }
        _Self& operator--() { node = node->prev; return *this; }
        _Self& operator--(int) { _Self tmp = *this; node = node->prev; return tmp; }
    };

    template <class T>
    struct list_const_iterator {
        typedef list_const_iterator<T> _Self;
        const ListNode<T>* node;

        list_const_iterator() : node() {}
        list_const_iterator(ListNode<T>* node) : node(node) {}
        list_const_iterator(const _Self& x) : node(x.node) {}
        list_const_iterator& operator=(const _Self& x) { node = x.node; return *this; }

        bool operator==(const _Self& x) const { return node == x.node; }
        bool operator!=(const _Self& x) const { return node != x.node; }
        T& operator*() const { return node->data; }
        T* operator->() const { return &node->data; }
        _Self& operator++() { node = node->next; return *this; }
        _Self& operator++(int) { _Self tmp = *this; node = node->next; return *this; }
        _Self& operator--() { node = node->prev; return *this; }
        _Self& operator--(int) { _Self tmp = *this; node = node->prev; return *this; }
    };

    template <class T>
    class list {
        ListNode<T> header;
        size_t _size;
    public:
        typedef ListNode<T> node_type;
        typedef ptrdiff_t diff_type;
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef list_iterator<T> iterator;
        typedef list_const_iterator<T> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        list() : header() {
            header.next = &header;
            header.prev = &header;
        }
        list(size_t n, const_reference val = value_type());
        template <class InputIterator>
        list(InputIterator first, InputIterator last);
        list(const list& x);
        ~list() {}
        list& operator=(const list& x);

        iterator begin() { return iterator(header.next); }
        const_iterator begin() const { return const_iterator(header.next); }
        iterator end() { return iterator(&header); }
        const_iterator end() const { return const_iterator(&header.next); }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        bool empty() const { return _size == 0; }
        size_t size() const { return _size; }
        size_t max_size() const { return std::numeric_limits<diff_type>::max() / sizeof(node_type); }

        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }
        reference back() { iterator tmp = end(); return *(--tmp); }
        const_reference back() const { iterator tmp = end(); return *(--tmp); }

        iterator insert(iterator position, const value_type& val) {
            node_type* node = new node_type(val);
            node->prev = position.node->prev;
            node->next = position.node;
            node->prev->next = node;
            node->next->prev = node;
            return iterator(node);
        }

        void insert(iterator position, size_t n, const value_type& val) {
            for (size_t i = 0; i < n; i++)
                insert(position, val);
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last) {
            while (first != last)
                insert(position, value_type(*first++));
        }

        void push_back(const_reference val);
    };
}

#endif
