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
        typedef std::random_access_iterator_tag iterator_category;
        typedef deque_iterator _Self;
        typedef T value_type;
        typedef Ref reference;
        typedef Ptr pointer;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        T* cur;
        T* first;
        T* last;
        T** node;

        deque_iterator() : cur(0), first(0), last(0), node(0) {}
        deque_iterator(const deque_iterator<T, T&, T*>& x) : cur(x.cur), first(x.first), last(x.last), node(x.node) {}

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

        _Self& operator+=(difference_type n) {
            difference_type offset = n + (cur - first);
            if (offset >= 0 && offset < buf_size(sizeof(T)))
                cur += n;
            else {
                difference_type node_offset = offset > 0 ? offset / buf_size(sizeof(T)) : -((-offset - 1) / buf_size(sizeof(T))) - 1;
                set_node(node + node_offset);
                cur = first + (offset - node_offset * buf_size(sizeof(T)));
            }
            return *this;
        }

        _Self operator+(difference_type n) const {
            _Self tmp = *this;
            return tmp += n;
        }

        _Self& operator-=(difference_type n)
        { return *this += -n; }

        _Self operator-(difference_type n) const {
            _Self tmp = *this;
            return tmp -= n;
        }

        T& operator[](difference_type n) const
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
    typename deque_iterator<T, Ref, Ptr>::difference_type operator-(const deque_iterator<T, Ref, Ptr>& a, const deque_iterator<T, Ref, Ptr>& b)
    { return buf_size(sizeof(T)) * (a.node - b.node) + (a.cur - a.first) - (b.cur - b.first); }

    template <class T, class RefL, class PtrL, class RefR, class PtrR>
    typename deque_iterator<T, RefL, PtrL>::difference_type operator-(const deque_iterator<T, RefL, PtrL>& a, const deque_iterator<T, RefR, PtrR>& b)
    { return buf_size(sizeof(T)) * (a.node - b.node) + (a.cur - a.first) - (b.cur - b.first); }

    template <class T, class Ref, class Ptr>
    deque_iterator<T, Ref, Ptr> operator+(ptrdiff_t n, const deque_iterator<T, Ref, Ptr>& x)
    { return x + n; }

    template <class T, class Alloc = std::allocator<T> >
    class deque {
    public:
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
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
        size_type map_size;
        iterator start;
        iterator finish;
        alloc_type allocator;

        map_alloc_type get_map_allocator() const
        { return map_alloc_type(allocator); }

        void map_init(size_type num_elems) {
            const size_type num_nodes = num_elems / buf_size(sizeof(T)) + 1;
            map_size = std::max((size_type)8, num_nodes + 2);
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

        void reallocate_map(size_type nodes_to_add, bool at_front) {
            size_type old_num_nodes = finish.node - start.node + 1;
            size_type new_num_nodes = old_num_nodes + nodes_to_add;
            T** new_start;
            if (map_size > new_num_nodes * 2) {
                new_start = map + (map_size - new_num_nodes) / 2 + (at_front ? nodes_to_add : 0);
                if (new_start < start.node)
                    std::copy(start.node, finish.node + 1, new_start);
                else
                    std::copy_backward(start.node, finish.node + 1, new_start);
            } else {
                size_type new_map_size = map_size + std::max(map_size, nodes_to_add) + 2;
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

        void reserve_map_at_back(size_type nodes_to_add = 1) {
            if (nodes_to_add + 1 > map_size - (finish.node - map))
                reallocate_map(nodes_to_add, false);
        }

        void reserve_map_at_front(size_type nodes_to_add = 1) {
            if (nodes_to_add > start.node - map)
                reallocate_map(nodes_to_add, true);
        }

        void fill_initialize(const_reference val) {
            for (T** cur = start.node; cur < finish.node; ++cur)
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
        void assign_dispatch(Integer n, Integer x, true_type)
        { fill_assign(n, x); }

        template <class InputIterator>
        void assign_dispatch(InputIterator first, InputIterator last, false_type) {
            iterator cur = begin();
            for (; first != last && cur != end(); ++first, ++cur)
                *cur = *first;
            if (first == last)
                erase_at_end(cur);
            else
                insert(end(), first, last);
        }

        void fill_assign(size_type n, const_reference val) {
            if (n > size()) {
                std::fill(begin(), end(), val);
                insert(end(), n - size(), val);
            } else {
                erase_at_end(begin() + n);
                std::fill(begin(), end(), val);
            }
        }

        void destroy_data(iterator first, iterator last) {
            for (; first != last; ++first)
                allocator.destroy(first.cur);
        }

        void destroy_nodes(T** first, T** last) {
            for (; first < last; ++first)
                allocator.deallocate(*first, buf_size(sizeof(T)));
        }

        void erase_at_begin(iterator pos) {
            destroy_data(begin(), pos);
            destroy_nodes(start.node, pos.node);
            start = pos;
        }

        void erase_at_end(iterator pos) {
            destroy_data(pos, end());
            destroy_nodes(pos.node + 1, finish.node + 1);
            finish = pos;
        }

        iterator reserve_elements_at_front(size_type n) {
            size_type avail = start.cur - start.first;
            if (n > avail)
                new_elements_at_front(n - avail);
            return start - n;
        }

        void new_elements_at_front(size_type n) {
            size_type new_nodes = (n + buf_size(sizeof(T)) - 1) / buf_size(sizeof(T));
            reserve_map_at_front(new_nodes);
            for (size_type i = 1; i <= new_nodes; ++i)
                *(start.node - i) = allocator.allocate(buf_size(sizeof(T)));
        }

        iterator reserve_elements_at_back(size_type n) {
            size_type avail = (finish.last - finish.cur) - 1;
            if (n > avail)
                new_elements_at_back(n - avail);
            return finish + n;
        }

        void new_elements_at_back(size_type n) {
            size_type new_nodes = (n + buf_size(sizeof(T)) - 1) / buf_size(sizeof(T));
            reserve_map_at_back(new_nodes);
            for (size_type i = 1; i <= new_nodes; ++i)
                *(finish.node + i) = allocator.allocate(buf_size(sizeof(T)));
        }

        void fill_insert(iterator position, size_type n, const_reference val) {
            if (position.cur == start.cur) {
                iterator new_start = reserve_elements_at_front(n);
                std::fill(new_start, start, val);
                start = new_start;
            } else if (position.cur == finish.cur) {
                iterator new_finish = reserve_elements_at_back(n);
                std::fill(finish, new_finish, val);
                finish = new_finish;
            } else {
                size_type elems_before = position - start;
                if (elems_before < size() / 2) {
                    iterator new_start = reserve_elements_at_front(n);
                    std::copy(start, position, new_start);
                    std::fill(position - n, position, val);
                    start = new_start;
                } else {
                    iterator new_finish = reserve_elements_at_back(n);
                    size_type elems_after = size() - elems_before;
                    std::copy_backward(position, finish, new_finish);
                    std::fill(position, position + n, val);
                    finish = new_finish;
                }
            }
        }

        template <class Integer>
        void insert_dispatch(iterator position, Integer n, Integer val, true_type)
        { fill_insert(position, n, val); }

        template <class InputIterator>
        void insert_dispatch(iterator position, InputIterator fisrt, InputIterator last, false_type) {
            difference_type n = std::distance(fisrt, last);
            if (position.cur == start.cur) {
                iterator new_start = reserve_elements_at_front(n);
                std::copy(fisrt, last, new_start);
                start = new_start;
            } else if (position.cur == finish.cur) {
                iterator new_finish = reserve_elements_at_back(n);
                std::copy_backward(fisrt, last, new_finish);
                finish = new_finish;
            } else {
                size_type elems_before = position - start;
                if (elems_before < size() / 2) {
                    iterator new_start = reserve_elements_at_front(n);
                    std::copy(start, position, new_start);
                    std::copy_backward(fisrt, last, position);
                    start = new_start;
                } else {
                    iterator new_finish = reserve_elements_at_back(n);
                    size_type elems_after = size() - elems_before;
                    std::copy_backward(position, finish, new_finish);
                    std::copy(fisrt, last, position);
                    finish = new_finish;
                }
            }
        }

    public:
        explicit deque(const alloc_type& allocator = alloc_type()) : map(0), map_size(0), start(), finish(), allocator(allocator) {
            map_init(0);
        }

        explicit deque(size_type n, const_reference val = value_type(), const alloc_type& allocator = alloc_type()) :
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
            std::copy(x.begin(), x.end(), start);
        }

        ~deque() {
            destroy_data(begin(), end());
            destroy_nodes(start.node, finish.node + 1);
            get_map_allocator().deallocate(map, map_size);
        }

        deque& operator=(const deque& x) {
            if (&x != this) {
                if (size() >= x.size())
                    erase_at_end(std::copy(x.begin(), x.end(), start));
                else {
                    const_iterator mid = x.begin() + size();
                    std::copy(x.begin(), mid, start);
                    insert(end(), mid, x.end());
                }
            }
            return *this;
        }

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

        size_type size() const
        { return finish - start; }

        size_type max_size() const
        { return allocator.max_size(); }

        void resize(size_type n, value_type val = value_type()) {
            if (n < size())
                erase_at_end(begin() + n);
            else
                insert(end(), n - size(), val);
        }

        bool empty() const
        { return start == finish; }

        reference operator[](size_type n)
        { return start[n]; }

        const_reference operator[](size_type n) const
        { return start[n]; }

        reference at(size_type n) {
            if (n >= size())
                throw std::out_of_range("deque out of range");
            return (*this)[n];
        }

        const_reference at(size_type n) const {
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

        void assign(size_type n, const_reference val)
        { fill_assign(n, val); }

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last) {
            typedef typename ::is_integer<InputIterator>::type Integral;
            assign_dispatch(first, last, Integral());
        }

        void push_back(const_reference val) {
            if (finish.cur != finish.last - 1) {
                allocator.construct(finish.cur, val);
                ++finish.cur;
            } else {
                reserve_map_at_back();
                *(finish.node + 1) = allocator.allocate(buf_size(sizeof(T)));
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
                *(start.node - 1) = allocator.allocate(buf_size(sizeof(T)));
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
           if (position == start) {
               push_front(val);
               return start;
           } else if (position == finish) {
               push_back(val);
               return --end();
           } else {
               difference_type index = position - start;
               if (index < size() / 2) {
                   push_front(front());
                   iterator front1 = begin();
                   ++front1;
                   iterator pos = front1 + index;
                   std::copy(front1, pos, begin());
                   *pos = val;
                   return pos;
               } else {
                   push_back(back());
                   iterator back1 = end();
                   --back1;
                   iterator pos = begin() + index;
                   std::copy_backward(pos, back1, end());
                   *pos = val;
                   return pos;
               }
           }
        }

        void insert(iterator position, size_type n, const_reference val)
        { fill_insert(position, n, val); }

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last) {
            typedef typename ::is_integer<InputIterator>::type Integral;
            insert_dispatch(position, first, last, Integral());
        }

        iterator erase(iterator position) {
            iterator next = begin();
            ++next;
            difference_type index = position - start;
            if (index < size() / 2) {
                if (next != begin())
                    std::copy_backward(begin(), position, next);
                pop_front();
            } else {
                if (next != end())
                    std::copy(next, end(), position);
                pop_back();
            }
            return begin() + index;
        }

        iterator erase(iterator first, iterator last) {
            if (first == begin() && last == end()) {
                clear();
                return end();
            }
            difference_type n = last - first;
            difference_type elems_before = first - begin();
            if (elems_before < (size() - n) / 2) {
                if (first != begin())
                    std::copy_backward(begin(), first, last);
                erase_at_begin(begin() + n);
            } else {
                if (last != end())
                    std::copy(last, end(), first);
                erase_at_end(end() - n);
            }
            return begin() + elems_before;
        }

        void swap(deque& x) {
            std::swap(map, x.map);
            std::swap(start, x.start);
            std::swap(finish, x.finish);
            std::swap(map_size, x.map_size);
            std::swap(allocator, x.allocator);
        }

        void clear()
        { erase_at_end(begin()); }

        alloc_type get_allocator() const
        { return allocator; }
    };

    template <class T, class Alloc>
    bool operator==(const deque<T, Alloc>& a, const deque<T, Alloc>& b)
    { return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin()); }

    template <class T, class Alloc>
    bool operator<(const deque<T, Alloc>& a, const deque<T, Alloc>& b)
    { return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()); }

    template <class T, class Alloc>
    bool operator!=(const deque<T, Alloc>& a, const deque<T, Alloc>& b)
    { return !(a == b); }

    template <class T, class Alloc>
    bool operator>(const deque<T, Alloc>& a, const deque<T, Alloc>& b)
    { return b < a; }

    template <class T, class Alloc>
    bool operator<=(const deque<T, Alloc>& a, const deque<T, Alloc>& b)
    { return !(b < a); }

    template <class T, class Alloc>
    bool operator>=(const deque<T, Alloc>& a, const deque<T, Alloc>& b)
    { return !(a < b); }

    template <class T, class Alloc>
    void swap(deque<T, Alloc>& a, deque<T, Alloc>& b)
    { a.swap(b); }
}

#endif
