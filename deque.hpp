#ifndef FT_CONTAINERS_DEQUE_HPP
#define FT_CONTAINERS_DEQUE_HPP

#include <cstddef>
#include <memory>
#include "type_traits.hpp"

namespace ft {
    size_t buf_size(size_t size)
    { return size < 512 ? 512 / size : 1; }

    template <class T, class Ref, class Ptr>
    struct deque_iterator {
        typedef deque_iterator _Self;
        typedef T value_type;
        typedef Ref reference;
        typedef Ptr pointer;
        typedef ptrdiff_t diff_type;
        T* cur;
        T* first;
        T* last;
        T** node;

        deque_iterator() : cur(0), first(0), last(0), node(0) {}
        deque_iterator(const _Self& x) : cur(x.cur), first(x.first), last(x.last), node(x.node) {}

        bool operator==(const _Self& b) const
        { return cur == b.cur; }

        bool operator!=(const _Self& b) const
        { return cur != b.cur; }

        T& operator*() const
        { return *cur; }

        T* operator->() const
        { return cur; }

        void set_node(T** newnode) {
            node = newnode;
            first = *node;
            last = first + buf_size(sizeof(T));

        }

        _Self& operator++() {
            ++cur;
            if (cur == last) {
                set_node(node + 1);
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
                set_node(node - 1);
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

        _Self& operator+=(diff_type n) {
            diff_type offset = n + (cur - first);
            if (offset >= 0 && offset < buf_size(sizeof(T)))
                cur += offset;
            else {
                diff_type node_offset = offset > 0 ? offset / buf_size(sizeof(T)) : -((-offset - 1) / buf_size(sizeof(T))) - 1;
                set_node(node + node_offset);
                cur = first + (offset - node_offset * buf_size(sizeof(T)));
            }
            return *this;
        }

        _Self operator+(diff_type n) const {
            _Self tmp = *this;
            return tmp += n;
        }

        _Self& operator-=(diff_type n)
        { return *this += -n; }

        _Self operator-(diff_type n) const {
            _Self tmp = *this;
            return tmp -= n;
        }

        T& operator[](diff_type n) const
        { return *(*this + n); }
    };

    template <class T, class Ref, class Ptr>
    bool operator==(const deque_iterator<T, Ref, Ptr>& a, const deque_iterator<T, Ref, Ptr>& b)
    { return a.cur == b.cur; }

    template <class T, class RefL, class PtrL, class RefR, class PtrR>
    bool operator==(const deque_iterator<T, RefL, PtrL>& a, const deque_iterator<T, RefR, PtrR>& b)
    { return a.cur == b.cur; }

    template <class T, class Ref, class Ptr>
    bool operator!=(const deque_iterator<T, Ref, Ptr>& a, const deque_iterator<T, Ref, Ptr>& b)
    { return !(a == b); }

    template <class T, class RefL, class PtrL, class RefR, class PtrR>
    bool operator!=(const deque_iterator<T, RefL, PtrL>& a, const deque_iterator<T, RefR, PtrR>& b)
    { return !(a == b); }

    template <class T, class Ref, class Ptr>
    bool operator<(const deque_iterator<T, Ref, Ptr>& a, const deque_iterator<T, Ref, Ptr>& b)
    { return a.node == b.node ? a.cur < b.cur : a.node < b.node; }

    template <class T, class RefL, class PtrL, class RefR, class PtrR>
    bool operator<(const deque_iterator<T, RefL, PtrL>& a, const deque_iterator<T, RefR, PtrR>& b)
    { return a.node == b.node ? a.cur < b.cur : a.node < b.node; }

    template <class T, class Ref, class Ptr>
    bool operator>(const deque_iterator<T, Ref, Ptr>& a, const deque_iterator<T, Ref, Ptr>& b)
    { return b < a; }

    template <class T, class RefL, class PtrL, class RefR, class PtrR>
    bool operator>(const deque_iterator<T, RefL, PtrL>& a, const deque_iterator<T, RefR, PtrR>& b)
    { return b < a; }

    template <class T, class Ref, class Ptr>
    bool operator<=(const deque_iterator<T, Ref, Ptr>& a, const deque_iterator<T, Ref, Ptr>& b)
    { return !(b < a); }

    template <class T, class RefL, class PtrL, class RefR, class PtrR>
    bool operator<=(const deque_iterator<T, RefL, PtrL>& a, const deque_iterator<T, RefR, PtrR>& b)
    { return !(b < a); }

    template <class T, class Ref, class Ptr>
    bool operator>=(const deque_iterator<T, Ref, Ptr>& a, const deque_iterator<T, Ref, Ptr>& b)
    { return !(a < b); }

    template <class T, class RefL, class PtrL, class RefR, class PtrR>
    bool operator>=(const deque_iterator<T, RefL, PtrL>& a, const deque_iterator<T, RefR, PtrR>& b)
    { return !(a < b); }

    template <class T, class Ref, class Ptr>
    typename deque_iterator<T, Ref, Ptr>::diff_type operator-(const deque_iterator<T, Ref, Ptr>& a, const deque_iterator<T, Ref, Ptr>& b)
    { return buf_size(sizeof(T)) * (a.node - b.node) + (a.cur - a.first) - (b.cur - b.first); }

    template <class T, class RefL, class PtrL, class RefR, class PtrR>
    typename deque_iterator<T, RefL, PtrL>::diff_type operator-(const deque_iterator<T, RefL, PtrL>& a, const deque_iterator<T, RefR, PtrR>& b)
    { return buf_size(sizeof(T)) * (a.node - b.node) + (a.cur - a.first) - (b.cur - b.first); }

    template <class T, class Ref, class Ptr>
    deque_iterator<T, Ref, Ptr> operator+(ptrdiff_t n, const deque_iterator<T, Ref, Ptr>& x)
    { return x + n; }

    template <class T, class Alloc = std::allocator<T> >
    class deque {
    public:
        typedef ptrdiff_t diff_type;
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef deque_iterator<T, T&, T*> iterator;
        typedef deque_iterator<T, const T&, const T*> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef typename Alloc::template rebind<T*>::other map_alloc_type;
        typedef typename Alloc::template rebind<T>::other alloc_type;
    private:
        T** map;
        size_t map_size;
        iterator start;
        iterator finish;
        alloc_type allocator;

        map_alloc_type get_map_allocator() const
        { return map_alloc_type(allocator); }

        void map_init(size_t num_elems) {
            const size_t num_nodes = num_elems / buf_size(sizeof(T)) + 1;
            map_size = std::max((size_t)8, num_nodes + 2);
            map = get_map_allocator().allocate(map_size);// new T*[map_size];
            T** nstart = map + (map_size - num_nodes) / 2;
            T** nfinish = nstart + num_nodes;
            for (T** cur = nstart; cur != nfinish; ++cur)
                *cur = allocator.allocate(buf_size(sizeof(T))); //new T[buf_size(sizeof(T))];
            start.set_node(nstart);
            finish.set_node(nfinish - 1);
            start.cur = start.first;
            finish.cur = finish.first + num_elems % buf_size(sizeof(T));
        }

        void reallocate_map(size_t nodes_to_add, bool at_front) {
            size_t old_num_nodes = finish.node - start.node + 1;
            size_t new_num_nodes = old_num_nodes + nodes_to_add;
            T** new_start;
            if (map_size > new_num_nodes * 2) {
                new_start = map + (map_size - new_num_nodes) / 2 + (at_front ? nodes_to_add : 0);
                if (new_start < start.node)
                    std::copy(start.node, finish.node + 1, new_start);
                else
                    std::copy_backward(start.node, finish.node + 1, new_start);
            } else {
                size_t new_map_size = map_size + std::max(map_size, nodes_to_add) + 2;
                T** new_map = get_map_allocator().allocate(new_map_size); //new T*[new_map_size];
                new_start = new_map + (new_map_size - new_num_nodes) / 2 + (at_front ? nodes_to_add : 0);
                std::copy(start.node, finish.node + 1, new_start);
                get_map_allocator().deallocate(map, map_size); //delete[] map;
                map = new_map;
                map_size = new_map_size;
            }
            start.set_node(new_start);
            finish.set_node(new_start + old_num_nodes + 1);
        }

        void reserve_map_at_back(size_t nodes_to_add = 1) {
            if (nodes_to_add + 1 > map_size - (finish.node - map))
                reallocate_map(nodes_to_add, false);
        }

        void reserve_map_at_front(size_t nodes_to_add = 1) {
            if (nodes_to_add > start.node - map)
                reallocate_map(nodes_to_add, true);
        }

        void fill_initialize(const_reference val) {
            for (T** cur = start.nod; cur < finish.node; ++cur)
                std::fill(*cur, *cur + buf_size(sizeof(T)), val);
            std::fill(finish.first, finish.cur, val);
        }

        template <class Integer>
        void initialize_dispatch(Integer n, Integer x, true_type) {
            map_init(n);
            fill_initialize(x);
        }

        template <class InputIterator>
        void initialize_dispatch(InputIterator first, InputIterator last, false_type) {
            map_init(0);
            for (; first != last; ++first)
                push_back(*first);
        }

        template <class Integer>
        void assign_dispatch(Integer n, Integer x, true_type) {

        }

        template <class InputIterator>
        void assign_dispatch(InputIterator first, InputIterator last, false_type) {

        }

        void destroy_data(iterator first, iterator last) {
//            for (T** cur = first.node + 1; cur < last.node; ++cur) {
//                for (T* i = *cur; i - *cur < buf_size(sizeof(T)); ++i)
//                    allocator.destroy(i);
//            }
//            if (start.node != finish.node) {
//                for (T* i = start.cur; i != start.last; ++i)
//                    allocator.destroy(i);
//                for (T* i = finish.first; i != finish.cur; ++i)
//                    allocator.destroy(i);
//            } else {
//                for (T* i = start.cur; i != finish.cur; ++i)
//                    allocator.destroy(i);
//            }
            for (; first != last; ++first)
                allocator.destroy(first.cur);
        }

        void destroy_nodes(T** first, T** last) {
            for (; first < last; ++first)
                allocator.deallocate(*first, buf_size(sizeof(T)));
        }

        void erase_at_end(iterator pos) {
            destroy_data(pos, end());
            destroy_nodes(pos.node + 1, finish.node);
        }

    public:
        explicit deque(const alloc_type& allocator = alloc_type()) : map(0), map_size(0), start(), finish(), allocator(allocator) {
            map_init(0);
        }

        explicit deque(size_t n, const_reference val = value_type(), const alloc_type& allocator = alloc_type()) :
            map(0), map_size(0), start(), finish(), allocator(allocator) {
            map_init(n);
            fill_initialize(val);
        }

        template <class InputIterator>
        deque(InputIterator first, InputIterator last, const alloc_type& allocator = alloc_type()) :
            map(0), map_size(0), start(), finish(), allocator(allocator) {
            typedef typename ::is_integer<InputIterator>::type Integral;
            initialize_dispatch(first, last, Integral());
        }

        deque(const deque& x) : map(0), map_size(0), start(), finish(), allocator(x.allocator) {
            map_init(x.size());
            for (deque::iterator it = x.begin(); it != x.end(); ++it)
                push_back(*it);
        }

        ~deque() {
            destroy_data(begin(), end());
            destroy_nodes(start.node, finish.node + 1);
            get_map_allocator().deallocate(map, map_size);
        }

//        deque& operator=(const deque& x) {
//            size_t len = x.size();
//            if (len > size())
//        }

        alloc_type get_allocator() const
        { return allocator; }

        iterator begin()
        { return start; }

        const_iterator begin() const
        { return start; }

        iterator end()
        { return finish; }

        const_iterator end() const
        { return finish; }

        reverse_iterator rbegin()
        { return reverse_iterator(finish); }

        const_reverse_iterator rbegin() const
        { return const_reverse_iterator(finish); }

        reverse_iterator rend()
        { return reverse_iterator(start); }

        const_reverse_iterator rend() const
        { return const_reverse_iterator(start); }

        size_t size() const
        { return finish - start; }

        size_t max_size() const
        { return allocator.max_size(); }

        reference operator[](size_t n)
        { return start[n]; }

        const_reference operator[](size_t n) const
        { return start[n]; }

        reference at(size_t n) {
            if (n >= size())
                throw std::out_of_range("deque out of range");
            return (*this)[n];
        }

        const_reference at(size_t n) const {
            if (n >= size())
                throw std::out_of_range("deque out of range");
            return (*this)[n];
        }

        reference front()
        { return *begin(); }

        const_reference front() const
        { return *begin(); }

        reference back()
        { return *(--end()); }

        const_reference back() const
        { return *(--end()); }



        void push_back(const_reference val) {
            if (finish.cur != finish.last - 1) {
                allocator.construct(finish.cur, val);
                ++finish.cur;
            } else {
                reserve_map_at_back();
                *(finish.node + 1) = new T[buf_size(sizeof(T))];
                allocator.construct(finish.cur, val);
                finish.set_node(finish.node + 1);
                finish.cur = finish.first;
            }
        }

        void push_front(const_reference val) {
            if (start.cur != start.first) {
                --start.cur;
                allocator.construct(start.cur, val);
            } else {
                reserve_map_at_front();
                *(start.node - 1) = new T[buf_size(sizeof(T))];
                start.set_node(start.node - 1);
                start.cur = start.last - 1;
                allocator.construct(start.cur, val);
            }
        }

        void pop_back() {
            if (finish.cur != finish.first) {
                --finish.cur;
                allocator.destroy(finish.cur);
            } else {
                destroy_nodes(finish.node, finish.node + 1);
                finish.set_node(finish.node - 1);
                finish.cur = finish.last - 1;
                allocator.destroy(finish.cur);
            }
        }

        void pop_front() {
            if (start.cur != start.last - 1) {
                allocator.destroy(start.cur);
                ++start.cur;
            } else {
                allocator.destroy(start.cur);
                destroy_nodes(start.node, start.node + 1);
                start.set_node(start.node + 1);
                start.cur = start.first;
            }
        }

        iterator insert(iterator position, const_reference val) {

        }
    };
}

#endif
