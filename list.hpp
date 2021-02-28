#ifndef FT_CONTAINERS_LIST_H
#define FT_CONTAINERS_LIST_H

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include "type_traits.hpp"

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

        void transfer(ListNode<T>* first, ListNode<T>* last) {
            if (this != last) {
                last->prev->next = this;
                first->prev->next = last;
                this->prev->next = first;

                ListNode<T>* tmp = this->prev;
                this->prev = last->prev;
                last->prev = first->prev;
                first->prev = tmp;
            }
        }
    };

    template <class T>
    struct list_iterator {
        typedef list_iterator<T> _Self;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
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
        typedef const T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::bidirectional_iterator_tag iterator_category;
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
    bool operator==(const list_iterator<T>& a, const list_const_iterator<T>& b)
    { return a.node == b.node; }

    template <class T>
    bool operator!=(const list_iterator<T>& a, const list_const_iterator<T>& b)
    { return a.node != b.node; }

    template <class T, class Alloc = std::allocator<T> >
    class list {
        typedef ListNode<T> node_type;
        typedef typename Alloc::template rebind<node_type>::other node_alloc_type;
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef list_iterator<T> iterator;
        typedef list_const_iterator<T> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef size_t size_type;
        typedef Alloc allocator_type;
    private:
        ListNode<T> header;
        size_type _size;
        node_alloc_type node_allocator;

        size_type distance(const ListNode<T>* first, const ListNode<T>* last) {
            size_type n = 0;
            while (first != last) {
                ++n;
                first = first->next;
            }
            return n;
        }

        template <class Integer>
        void initialize_dispatch(Integer n, Integer x, true_type) {
            for (size_type i = 0; i < n; ++i)
                push_back(x);
        }

        template<class InputIterator>
        void initialize_dispatch(InputIterator first, InputIterator last, false_type) {
            while (first != last)
                push_back(*first++);
        }

        template <class Integer>
        void insert_dispatch(iterator position, Integer n, Integer x, true_type) {
            for (size_type i = 0; i < n; i++)
                insert(position, x);
        }

        template <class InputIterator>
        void insert_dispatch(iterator position, InputIterator first, InputIterator last, false_type) {
            while (first != last)
                insert(position, value_type(*first++));
        }

        template <class Integer>
        void assign_dispatch(Integer n, Integer x, true_type) {
            for (size_type i = 0; i < n; ++i)
                push_back(x);
        }

        template <class InputIterator>
        void assign_dispatch(InputIterator first, InputIterator last, false_type)
        { insert(end(), first, last); }
    public:
        explicit list(const allocator_type& alloc = allocator_type()): header(), _size(0), node_allocator(alloc) {
            header.next = &header;
            header.prev = &header;
        }

        explicit list(size_type n, const_reference val = value_type(), const allocator_type& alloc = allocator_type()) :
            header(), _size(0), node_allocator(alloc) {
            header.next = &header;
            header.prev = &header;
            for (size_type i = 0; i < n; ++i)
                push_back(val);
        }

        template <class InputIterator>
        list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
            header(), _size(0), node_allocator(alloc) {
            header.next = &header;
            header.prev = &header;
            typedef typename is_integer<InputIterator>::type Integral;
            initialize_dispatch(first, last, Integral());
        }

        list(const list& x) : header(), _size(0), node_allocator(x.node_allocator) {
            header.next = &header;
            header.prev = &header;
            insert(end(), x.begin(), x.end());
        }

        ~list() { clear(); }

        list& operator=(const list& x) {
            iterator first1 = begin();
            const_iterator first2 = x.begin();
            for (; first1 != end() && first2 != x.end(); ++first1, ++first2)
                *first1 = *first2;
            if (first2 == x.end())
                erase(first1, end());
            else
                insert(end(), first2, x.end());
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
        size_type size() const { return _size; }
        size_type max_size() const { return node_allocator.max_size(); }

        reference front() { return *begin(); }
        const_reference front() const { return *begin(); }
        reference back() { iterator tmp = end(); return *(--tmp); }
        const_reference back() const { iterator tmp = end(); return *(--tmp); }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {
            clear();
            typedef typename is_integer<InputIterator>::type Integral;
            assign_dispatch(first, last, Integral());
        }

        void assign(size_type n, const_reference val) {
            clear();
            for (size_type i = 0; i < n; ++i)
                push_back(val);
        }

        iterator insert(iterator position, const value_type& val) {
            node_type* node = node_allocator.allocate(1);
            allocator_type(node_allocator).construct(&node->data, val);
            node->prev = position.node->prev;
            node->next = position.node;
            node->prev->next = node;
            node->next->prev = node;
            ++_size;
            return iterator(node);
        }

        void insert(iterator position, size_type n, const value_type& val) {
            for (size_type i = 0; i < n; i++)
                insert(position, val);
        }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last) {
            typedef typename is_integer<InputIterator>::type Integral;
            insert_dispatch(position, first, last, Integral());
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
            allocator_type(node_allocator).destroy(&tmp.node->data);
            node_allocator.deallocate(tmp.node, 1);
            --_size;
            return position;
        }

        iterator erase(iterator first, iterator last) {
            while (first != last)
                first = erase(first);
            return first;
        }

        void swap(list& x) {
            ListNode<T>::swap(header, x.header);
            std::swap(_size, x._size);
        }

        void resize(size_type n, value_type val = value_type()) {
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
            position.node->transfer(x.begin().node, x.end().node);
            _size += x.size();
            x._size = 0;
        }

        void splice(iterator position, list& x, iterator i) {
            iterator j = i;
            ++j;
            if (position == i || position == j)
                return;
            position.node->transfer(i.node, j.node);
            _size++;
            x._size--;
        }

        void splice(iterator position, list& x, iterator first, iterator last) {
            size_type dist = distance(first.node, last.node);
            position.node->transfer(first.node, last.node);
            _size += dist;
            x._size -= dist;
        }

        void remove(const_reference val) {
            iterator it = begin();
            while (it != end()) {
                iterator next = it;
                ++next;
                if (*it == val)
                    erase(it);
                it = next;
            }
        }

        template <class Predicate>
        void remove_if(Predicate pred) {
            iterator it = begin();
            while (it != end()) {
                iterator next = it;
                ++next;
                if (pred(*it))
                    erase(it);
                it = next;
            }
        }

        void unique() {
            iterator it = begin();
            if (it == end())
                return;
            iterator next = it;
            while (++next != end()) {
                if (*next == *it)
                    erase(next);
                else
                    it = next;
                next = it;
            }
        }

        template <class BinaryPredicate>
        void unique(BinaryPredicate pred) {
            iterator it = begin();
            if (it == end())
                return;
            iterator next = it;
            while (++next != end()) {
                if (pred(*next, *it))
                    erase(next);
                else
                    it = next;
                next = it;
            }
        }

        void merge(list& x) {
            if (this != &x) {
                iterator it1 = begin();
                iterator it2 = x.begin();
                while (it1 != end() && it2 != x.end()) {
                    if (*it2 < *it1) {
                        iterator next = it2;
                        ++next;
                        it1.node->transfer(it2.node, next.node);
                        it2 = next;
                    } else
                        ++it1;
                }
                if (it2 != x.end())
                    it1.node->transfer(it2.node, x.end().node);
                _size += x.size();
                x._size = 0;
            }
        }

        template <class Compare>
        void merge(list& x, Compare comp) {
            if (this != &x) {
                iterator it1 = begin();
                iterator it2 = x.begin();
                while (it1 != end() && it2 != x.end()) {
                    if (comp(*it2, *it1)) {
                        iterator next = it2;
                        ++next;
                        it1.node->transfer(it2.node, next.node);
                        it2 = next;
                    } else
                        ++it1;
                }
                if (it2 != x.end())
                    it1.node->transfer(it2.node, x.end().node);
                _size += x.size();
                x._size = 0;
            }
        }

        void sort() {
            list tmp1, tmp2;
            do {
                tmp1.splice(tmp1.begin(), *this, begin());
                tmp2.merge(tmp1);
            } while (!empty());
            swap(tmp2);
        }

        template <class Compare>
        void sort(Compare comp) {
            list tmp1, tmp2;
            do {
                tmp1.splice(tmp1.begin(), *this, begin());
                tmp2.merge(tmp1);
            } while (!empty());
            swap(tmp2);
        }

        void reverse() {
           iterator it = end();
           do {
               std::swap(it.node->prev, it.node->next);
               --it;
           } while (it != end());
        }

        allocator_type get_allocator() const
        { return allocator_type(node_allocator); }
    };

    template <class T>
    bool operator==(const list<T>& a, const list<T>& b) {
        if (a.size() != b.size())
            return false;
        typename list<T>::const_iterator it1 = a.begin();
        typename list<T>::const_iterator it2 = b.begin();
        while (it1 != a.end() && it2 != b.end() && *it1 == *it2) {
            ++it1;
            ++it2;
        }
        return it1 == a.end() && it2 == b.end();
    }

    template <class T>
    bool operator!=(const list<T>& a, const list<T>& b)
    { return !(a == b); }

    template <class T>
    bool operator<(const list<T>& a, const list<T>& b)
    { return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()); }

    template <class T>
    bool operator>(const list<T>& a, const list<T>& b)
    { return b < a; }

    template <class T>
    bool operator<=(const list<T>& a, const list<T>& b)
    { return !(b < a); }

    template <class T>
    bool operator>=(const list<T>& a, const list<T>& b)
    { return !(a < b); }

    template <class T>
    void swap(list<T>& a, list<T>& b)
    { a.swap(b); }
}

#endif
