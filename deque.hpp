#ifndef FT_CONTAINERS_DEQUE_HPP
#define FT_CONTAINERS_DEQUE_HPP

#include <cstddef>

namespace ft {
    size_t buf_size(size_t size)
    { return size < 512 ? 512 / size : 1; }

    template <class T>
    struct deque_iterator {
        typedef deque_iterator<T> _Self;
        T* cur;
        T* first;
        T* last;
        T** map;

        deque_iterator() : cur(0), first(0), last(0), map(0) {}
        deque_iterator(const _Self& x) : cur(x.cur), first(x.first), last(x.last), map(x.map) {}
        deque_iterator& operator=(const _Self& x) {
            cur = x.cur;
            first = x.first;
            last = x.last;
            map = x.map;
            *this;
        }

        bool operator==(const _Self& b) const
        { return cur == b.cur; }

        bool operator!=(const _Self& b) const
        { return cur != b.cur; }

        T& operator*() const
        { return *cur; }

        T* operator->() const
        { return cur; }

        void set_map(T** newmap) {
            map = newmap;
            first = *map;
            last = first + buf_size(sizeof(T));

        }

        _Self& operator++() {
            ++cur;
            if (cur == last) {
                set_map(map + 1);
                cur = first;
            }
            return *this;
        }

        _Self operator++(int) {
            _Self tmp = *this;
            ++*this;
            return tmp;
        }

        _Self& operator--() {
            if (cur == first) {
                set_map(map - 1);
                cur = last;
            }
            --cur;
            return *this;
        }

        _Self operator--(int) {
            _Self tmp = *this;
            --*this;
            return tmp;
        }
    };

    template <class T>
    struct deque_const_iterator {
        typedef deque_const_iterator<T> _Self;
        T* cur;
        T* first;
        T* last;
        T** map;

        deque_const_iterator() : cur(0), first(0), last(0), map(0) {}
    };

    template <class T>
    class deque {
    public:
        typedef ptrdiff_t diff_type;
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef deque_iterator<T> iterator;
        typedef deque_const_iterator<T> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    private:
        T** map;
        size_t map_size;
        iterator start;
        iterator finish;

        deque() : map(0), map_size(0), start(), finish() {
            map_init(0);
        }

        void map_init(size_t num_elems) {
            const size_t num_nodes = num_elems / buf_size(sizeof(T)) + 1;
            map_size = std::max((size_t)8, num_nodes + 2);
            map = new T*[map_size];
            T** nstart = map + (map_size - num_nodes) / 2;
            T** nfinish = nstart + num_nodes;
            for (T** cur = nstart; cur != nfinish; ++cur)
                *cur = new T[buf_size(sizeof(T))];
            start.set_map(nstart);
            finish.set_map(nfinish - 1);
            start.cur = start.first;
            finish.cur = finish.first + num_elems % buf_size(sizeof(T));
        }
    };
}

#endif
