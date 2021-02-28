#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include <iterator>
#include <memory>
#include "type_traits.hpp"

namespace ft {
//    template <class T>
//    struct vector_iterator {
//        typedef vector_iterator<T> _Self;
//        typedef T value_type;
//        typedef ptrdiff_t difference_type;
//        typedef T* pointer;
//        typedef T& reference;
//        typedef std::random_access_iterator_tag iterator_category;
//
//        T* cur;
//
//        vector_iterator() : cur(0) {}
//        vector_iterator(const T* t) : cur(t) {}
//
//
//    };

    template<class T, class Alloc = std::allocator<T> >
    class vector {
    public:
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference cont_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef std::iterator<std::random_access_iterator_tag, value_type> iterator;
        typedef std::iterator<std::random_access_iterator_tag, const value_type> const_iterator;
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
            if (finish != position) {
                do {
                    --finish;
                    allocator.destroy(*finish);
                } while (finish != position);
            }
        }
    public:
        explicit vector(const allocator_type& alloc = allocator_type()) : start(0), finish(0), end_of_storage(0), allocator(0) {}

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
        }

        vector& operator=(const vector& x) {
            if (this != &x) {
                size_type l = x.size();
                if (l > capacity()) {
                    do {
                        --finish;
                        allocator.destroy(*finish);
                    } while (finish != start);
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
        { return iterator(start); }

        iterator end()
        { return iterator(finish); }

        const_iterator end() const
        { return iterator(finish); }

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

        void resize(size_type n, value_type val = value_type()) {}

        size_type capacity() const
        { return end_of_storage - start; }

        iterator insert(iterator position, const value_type& val) {

        }
    };
}

#endif
