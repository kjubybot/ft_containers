#ifndef FT_CONTAINERS_LIST_H
#define FT_CONTAINERS_LIST_H

#include <algorithm>
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

        static void swap(ListNode<T>& a, ListNode<T>& b) {
            if (a.next != &a) {
                if (b.next != &b) {
                    std::swap(a.next, b.next);
                    std::swap(a.prev, b.prev);
                    a.next->prev = a.prev->next = &a;
                    b.next->prev = b.prev->next = &b;
                } else {
                    b.next = a.next;
                    b.prev = a.prev;
                    b.next->prev = b.prev->next = &b;
                    a.next = a.prev = &a;
                }
            } else if (b.next != &b) {
                a.next = b.next;
                a.prev = b.prev;
                a.prev->next = a.next->prev = &a;
                b.next = b.prev = &b;
            }
        }
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
        _Self operator++(int) { _Self tmp = *this; node = node->next; return tmp; }
        _Self& operator--() { node = node->prev; return *this; }
        _Self operator--(int) { _Self tmp = *this; node = node->prev; return tmp; }
    };

    template <class T>
    struct list_const_iterator {
        typedef list_const_iterator<T> _Self;
        const ListNode<T>* node;

        list_const_iterator() : node() {}
        list_const_iterator(const ListNode<T>* node) : node(node) {}
        list_const_iterator(const _Self& x) : node(x.node) {}
        list_const_iterator& operator=(const _Self& x) { node = x.node; return *this; }

        bool operator==(const _Self& x) const { return node == x.node; }
        bool operator!=(const _Self& x) const { return node != x.node; }
        const T& operator*() const { return node->data; }
        const T* operator->() const { return &node->data; }
        _Self& operator++() { node = node->next; return *this; }
        _Self operator++(int) { _Self tmp = *this; node = node->next; return tmp; }
        _Self& operator--() { node = node->prev; return *this; }
        _Self operator--(int) { _Self tmp = *this; node = node->prev; return tmp; }
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

        list() : header(), _size(0) {
            header.next = &header;
            header.prev = &header;
        }

        list(size_t n, const_reference val = value_type()) : header(), _size(0) {
            header.next = &header;
            header.prev = &header;
            for (size_t i = 0; i < n; ++i)
                push_back(val);
        }

        template <class InputIterator>
        list(InputIterator first, InputIterator last) : header(), _size(0) {
            header.next = &header;
            header.prev = &header;
            while (first != last)
                push_back(*first++);
        }

        list(const list& x) : header(), _size(0) {
            header.next = &header;
            header.prev = &header;
            insert(end(), x.begin(), x.end());
        }

        ~list() { clear(); }

        list& operator=(const list& x) {
            clear();
            insert(end(), x.begin(), x.end());
            return *this;
        }

        iterator begin() { return iterator(header.next); }
        const_iterator begin() const { return const_iterator(header.next); }
        iterator end() { return iterator(&header); }
        const_iterator end() const { return const_iterator(&header); }
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

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {
            clear();
            insert(end(), first, last);
        }

        void assign(size_t n, const_reference val) {
            clear();
            for (size_t i = 0; i < n; ++i)
                push_back(val);
        }

        iterator insert(iterator position, const value_type& val) {
            node_type* node = new node_type(val);
            node->prev = position.node->prev;
            node->next = position.node;
            node->prev->next = node;
            node->next->prev = node;
            ++_size;
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

        void push_front(const_reference val) {
            insert(begin(), val);
        }

        void pop_front() {
            erase(begin());
        }

        void push_back(const_reference val) {
            insert(end(), val);
        }

        void pop_back() {
            erase(--end());
        }

        iterator erase(iterator position) {
            iterator tmp = position;
            ++position;
            tmp.node->prev->next = position.node;
            position.node->prev = tmp.node->prev;
            delete tmp.node;
            --_size;
            return position;
        }

        iterator erase(iterator first, iterator last) {
            while (first != last)
                first = erase(first);
        }

        void swap(list& x) {
            ListNode<T>::swap(header, x.header);
            std::swap(_size, x._size);
        }

        void resize(size_t n, value_type val = value_type()) {
            while (_size != n)
                n > _size ? push_back(val) : pop_back();
        }

        void clear() {
            iterator it = begin();
            iterator tmp = it;
            while (it != end()) {
                tmp = it;
                ++it;
                erase(tmp);
            }
        }

        void splice(iterator position, list& x) {

        }
        void splice(iterator position, list& x, iterator i);
        void splice(iterator position, list& x, iterator first, iterator last);
    };
}

#endif
