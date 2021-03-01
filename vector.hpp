#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <iterator>
#include <memory>
#include <stdexcept>
#include "type_traits.hpp"

namespace ft {
    template <class T>
    struct vector_iterator {
        typedef vector_iterator<T> _Self;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        typedef std::random_access_iterator_tag iterator_category;

        T* cur;

        vector_iterator() : cur(0) {}
        vector_iterator(T* t) : cur(t) {}
        vector_iterator(const vector_iterator& v) : cur(v.cur) {}

        reference operator*() const
        { return *cur; }

        pointer operator->() const
        { return cur; }

        _Self& operator++() {
            ++cur;
            return *this;
        }

        _Self operator++(int) {
            _Self tmp = *this;
            ++cur;
            return tmp;
        }

        _Self& operator--() {
            --cur;
            return *this;
        }

        _Self operator--(int) {
            _Self tmp = *this;
            --cur;
            return tmp;
        }

        _Self& operator+=(difference_type n) {
            cur += n;
            return *this;
        }

        _Self& operator-=(difference_type n) {
            cur -= n;
            return *this;
        }

        _Self operator+(difference_type n) {
            _Self tmp = *this;
            return tmp += n;
        }

        _Self operator-(difference_type n) {
            _Self tmp = *this;
            return tmp -= n;
        }

        difference_type operator-(const vector_iterator& x)
        { return cur - x.cur; }

        reference operator[](difference_type n)
        { return *(cur + n); }

        bool operator==(const vector_iterator& x) const
        { return cur == x.cur; }

        bool operator!=(const vector_iterator& x) const
        { return cur != x.cur; }

        bool operator<(const vector_iterator& x) const
        { return cur < x.cur; }

        bool operator>(const vector_iterator& x) const
        { return cur > x.cur; }

        bool operator<=(const vector_iterator& x) const
        { return cur <= x.cur; }

        bool operator>=(const vector_iterator& x) const
        { return cur >= x.cur; }
    };

    template <class T>
    vector_iterator<T> operator+(ptrdiff_t n, const vector_iterator<T>& x)
    { return x + n; }

    template <class T>
    struct vector_const_iterator {
        typedef vector_const_iterator<T> _Self;
        typedef const T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef std::random_access_iterator_tag iterator_category;

        const T* cur;

        vector_const_iterator() : cur(0) {}
        vector_const_iterator(const T* t) : cur(t) {}
        vector_const_iterator(const vector_const_iterator& v) : cur(v.cur) {}

        reference operator*() const
        { return *cur; }

        pointer operator->() const
        { return cur; }

        _Self& operator++() {
            ++cur;
            return *this;
        }

        _Self operator++(int) {
            _Self tmp = *this;
            ++cur;
            return tmp;
        }

        _Self& operator--() {
            --cur;
            return *this;
        }

        _Self operator--(int) {
            _Self tmp = *this;
            --cur;
            return tmp;
        }

        _Self& operator+=(difference_type n) {
            cur += n;
            return *this;
        }

        _Self& operator-=(difference_type n) {
            cur -= n;
            return *this;
        }

        _Self operator+(difference_type n) {
            _Self tmp = *this;
            return tmp += n;
        }

        _Self operator-(difference_type n) {
            _Self tmp = *this;
            return tmp -= n;
        }

        difference_type operator-(const vector_const_iterator& x)
        { return cur - x.cur; }

        reference operator[](difference_type n)
        { return *(cur + n); }

        bool operator==(const vector_const_iterator& x) const
        { return cur == x.cur; }

        bool operator!=(const vector_const_iterator& x) const
        { return cur != x.cur; }

        bool operator<(const vector_const_iterator& x) const
        { return cur < x.cur; }

        bool operator>(const vector_const_iterator& x) const
        { return cur > x.cur; }

        bool operator<=(const vector_const_iterator& x) const
        { return cur <= x.cur; }

        bool operator>=(const vector_const_iterator& x) const
        { return cur >= x.cur; }
    };

    template <class T>
    vector_iterator<T> operator+(ptrdiff_t n, const vector_const_iterator<T>& x)
    { return x + n; }

    template <class T>
    typename vector_iterator<T>::difference_type operator-(const vector_iterator<T>& a, const vector_const_iterator<T>& b)
    { return a.cur - b.cur; }

    template <class T>
    bool operator==(const vector_iterator<T>& a, const vector_const_iterator<T>& b)
    { return a.cur == b.cur; }

    template <class T>
    bool operator!=(const vector_iterator<T>& a, const vector_const_iterator<T>& b)
    { return a.cur != b.cur; }

    template <class T>
    bool operator<(const vector_iterator<T>& a, const vector_const_iterator<T>& b)
    { return a.cur < b.cur; }

    template <class T>
    bool operator>(const vector_iterator<T>& a, const vector_const_iterator<T>& b)
    { return b < a; }

    template <class T>
    bool operator<=(const vector_iterator<T>& a, const vector_const_iterator<T>& b)
    { return !(b < a); }

    template <class T>
    bool operator>=(const vector_iterator<T>& a, const vector_const_iterator<T>& b)
    { return !(a < b); }

    template<class T, class Alloc = std::allocator<T> >
    class vector {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef vector_iterator<value_type> iterator;
        typedef vector_const_iterator<value_type> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
    private:
        T* start;
        T* finish;
        T* end_of_storage;
        allocator_type allocator;

        template <class Integer>
        void initialize_dispatch(Integer n, Integer x, true_type) {
            start = allocator.allocate(n);
            end_of_storage = start + n;
            finish = start;
            for (; finish != end_of_storage; ++finish)
                allocator.construct(finish, x);
        }

        template <class InputIterator>
        void initialize_dispatch(InputIterator first, InputIterator last, false_type) {
            size_type n = std::distance(first, last);
            start = allocator.allocate(n);
            end_of_storage = start + n;
            finish = start;
            for (; finish != end_of_storage && first != last; ++finish, ++first)
                allocator.construct(finish, *first);
        }

        void erase_at_end(iterator position) {
            if (finish != position.cur) {
                do {
                    --finish;
                    allocator.destroy(finish);
                } while (finish != position.cur);
            }
        }

        void fill_assign(size_type n, const value_type& val) {
            if (n > capacity()) {
                reserve(n);
                std::fill(start, finish, val);
                for (; finish != start + n; ++finish)
                    allocator.construct(finish, val);
            } else {
                if (n <= size()) {
                    std::fill(start, start + n, val);
                    erase_at_end(start + n);
                } else {
                    std::fill(start, finish, val);
                    fill_insert(end(), n - size(), val);
                }
            }
        }

        template <class Integer>
        void assign_dispatch(Integer n, Integer x, true_type)
        { fill_assign(n, x); }

        template <class InputIterator>
        void assign_dispatch(InputIterator first, InputIterator last, false_type) {
            size_type n = std::distance(first, last);
            if (n > capacity()) {
                reserve(n);
                for (size_type i = 0; start + i != finish; ++i, ++first)
                    *(start + i) = *first;
                for (; finish != start + n; ++finish, ++first)
                    allocator.construct(finish, *first);
            } else {
                if (n <= size()) {
                    for (size_type i = 0; i < n; ++i, ++first)
                        *(start + i) = *first;
                    erase_at_end(start + n);
                } else {
                    for (size_type i = 0; start + i != finish; ++i, ++first)
                        *(start + i) = *first;
                    insert_dispatch(end(), first, last, false_type());
                }
            }
        }

        void fill_insert(iterator position, size_type n, const value_type& val) {
            size_type space = capacity() - size();
            if (n <= space && position == end()) {
                for (; n > 0; --n, ++finish)
                    allocator.construct(finish, val);
            } else {
                size_type index = position.cur - start;
                if (n > space)
                    reserve(n + size());
                std::copy_backward(start + index, finish, finish + n);
                std::fill(start + index, start + index + n, val);
                finish += n;
            }
        }

        template <class Integer>
        void insert_dispatch(iterator position, Integer n, Integer x, true_type)
        { fill_insert(position, n, x); }

        template <class InputIterator>
        void insert_dispatch(iterator position, InputIterator first, InputIterator last, false_type) {
            size_type space = capacity() - size();
            size_type n = std::distance(first, last);
            if (n <= space && position == end()) {
                for (; first != last; ++first, ++finish)
                    allocator.construct(finish, *first);
            } else {
                size_type index = position.cur - start;
                if (n > space)
                    reserve(n + size());
                std::copy_backward(start + index, finish, finish + n);
                std::copy(first, last, start + index);
                finish += n;
            }
        }
    public:
        explicit vector(const allocator_type& alloc = allocator_type()) : start(0), finish(0), end_of_storage(0), allocator(alloc) {}

        explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
            start(0), finish(0), end_of_storage(0), allocator(alloc) {
            start = allocator.allocate(n);
            end_of_storage = start + n;
            finish = start;
            for (; finish != end_of_storage; ++finish)
                allocator.construct(finish, val);
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) :
            start(0), finish(0), end_of_storage(0), allocator(alloc) {
            typedef typename is_integer<InputIterator>::type Integral;
            initialize_dispatch(first, last, Integral());
        }

        vector(const vector& x) : start(0), finish(0), end_of_storage(0), allocator(x.allocator) {
            start = allocator.allocate(x.capacity());
            std::copy(x.start, x.finish, start);
            finish = start + x.size();
            end_of_storage = start + x.capacity();
        }

        ~vector()
        {
            erase_at_end(start);
            allocator.deallocate(start, end_of_storage - start);
        }

        vector& operator=(const vector& x) {
            if (this != &x) {
                size_type l = x.size();
                if (l > capacity()) {
                    while (finish != start) {
                        --finish;
                        allocator.destroy(finish);
                    }
                    allocator.deallocate(start, end_of_storage - start);
                    start = allocator.allocate(l);
                    end_of_storage = finish = start + l;
                    std::copy(x.start, x.finish, start);
                } else if (size() >= l) {
                    std::copy(x.start, x.finish, start);
                    erase_at_end(start + l);
                } else {
                    size_type s = size();
                    std::copy(x.start, x.start + s, start);
                    for (pointer i = x.start + s; i != x.finish; ++finish, ++i)
                        allocator.construct(finish, *i);
                }
            }
            return *this;
        }

        iterator begin()
        { return iterator(start); }

        const_iterator begin() const
        { return const_iterator(start); }

        iterator end()
        { return iterator(finish); }

        const_iterator end() const
        { return const_iterator(finish); }

        reverse_iterator rbegin()
        { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const
        { return const_reverse_iterator(end()); }

        reverse_iterator rend()
        { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const
        { return const_reverse_iterator(begin()); }

        size_type size() const
        { return finish - start; }

        size_type max_size() const
        { return allocator.max_size(); }

        void resize(size_type n, value_type val = value_type()) {
            if (n > capacity())
                reserve(n);
            if (n > size()) {
                std::fill(finish, start + n, val);
                finish = start + n;
            } else
                erase_at_end(start + n);
        }

        size_type capacity() const
        { return end_of_storage - start; }

        bool empty() const
        { return start == finish; }

        void reserve(size_type n) {
            if (n > capacity()) {
                pointer newp = allocator.allocate(n);
                size_type index = finish - start;
                std::copy(start, finish, newp);
                do {
                    --finish;
                    allocator.destroy(finish);
                } while (finish != start);
                allocator.deallocate(start, index);
                start = newp;
                finish = start + index;
                end_of_storage = start + n;
            }
        }

        reference operator[](size_type n)
        { return *(start + n); }

        const_reference operator[](size_type n) const
        { return *(start + n); }

        reference at(size_type n) {
            if (start + n >= finish)
                throw std::out_of_range("vector out of range");
            return *(start + n);
        }

        const_reference at(size_type n) const {
            if (start + n >= finish)
                throw std::out_of_range("vector out of range");
            return *(start + n);
        }

        reference front()
        { return *start; }

        const_reference front() const
        { return *start; }

        reference back()
        { return *(finish - 1); }

        const_reference back() const
        { return *(finish - 1); }

        void assign(size_type n, const value_type& val)
        { fill_assign(n, val); }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {
            typedef typename is_integer<InputIterator>::type Integral;
            assign_dispatch(first, last, Integral());
        }

        void push_back(const value_type& val)
        { insert(end(), val); }

        void pop_back() {
            --finish;
            allocator.destroy(finish);
        }

        iterator insert(iterator position, const value_type& val) {
            if (finish != end_of_storage && position == end()) {
                allocator.construct(finish, val);
                ++finish;
                return position;
            } else {
                size_type index = position.cur - start;
                if (finish == end_of_storage)
                    reserve(capacity() + 1);
                allocator.construct(finish, back());
                std::copy_backward(start + index, finish, finish + 1);
                *(start + index) = val;
                ++finish;
                return iterator(start + index);
            }
        }

        void insert(iterator position, size_type n, const value_type &val)
        { fill_insert(position, n, val); }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last) {
            typedef typename is_integer<InputIterator>::type Integral;
            insert_dispatch(position, first, last, Integral());
        }

        iterator erase(iterator position) {
            if (position != end() - 1)
                std::copy(position + 1, end(), position);
            pop_back();
            return position;
        }

        iterator erase(iterator first, iterator last) {
            if (last != end())
                std::copy(last, end(), first);
            erase_at_end(first + (end() - last));
            return first;
        }

        void swap(vector& x) {
            std::swap(start, x.start);
            std::swap(finish, x.finish);
            std::swap(end_of_storage, x.end_of_storage);
        }

        void clear()
        { erase_at_end(start); }

        allocator_type get_allocator() const
        { return allocator; }
    };

    template <class T, class Alloc>
    bool operator==(const vector<T, Alloc>& a, const vector<T, Alloc>& b)
    { return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin()); }

    template <class T, class Alloc>
    bool operator<(const vector<T, Alloc>& a, const vector<T, Alloc>& b)
    { return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()); }

    template <class T, class Alloc>
    bool operator!=(const vector<T, Alloc>& a, const vector<T, Alloc>& b)
    { return !(a == b); }

    template <class T, class Alloc>
    bool operator>(const vector<T, Alloc>& a, const vector<T, Alloc>& b)
    { return b < a; }

    template <class T, class Alloc>
    bool operator<=(const vector<T, Alloc>& a, const vector<T, Alloc>& b)
    { return !(b < a); }

    template <class T, class Alloc>
    bool operator>=(const vector<T, Alloc>& a, const vector<T, Alloc>& b)
    { return !(a < b); }

    template <class T, class Alloc>
    void swap(vector<T, Alloc>& a, vector<T, Alloc>& b)
    { a.swap(b); }
}

#endif
