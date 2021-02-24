#ifndef FT_CONTAINERS_QUEUE_HPP
#define FT_CONTAINERS_QUEUE_HPP

#include "deque.hpp"

namespace ft {
    template<class T, class Container = deque<T> >
    class queue {
    protected:
        Container c;
    public:
        typedef typename Container::value_type value_type;
        typedef Container container_type;
        typedef typename Container::size_type size_type;

        explicit queue(const container_type& cont = container_type()) : c(cont) {}

        bool empty() const
        { return c.empty(); }

        size_type size() const
        { return c.size(); }

        value_type& front()
        { return c.front(); }

        const value_type& front() const
        { return c.front(); }

        value_type& back()
        { return c.back(); }

        const value_type& back() const
        { return c.back(); }

        void push(const value_type& val)
        { c.push_back(val); }

        void pop()
        { c.pop_front(); }
    };

    template <class T, class Container>
    bool operator==(const queue<T, Container>& a, const queue<T, Container>& b)
    { return a.c == b.c; }

    template<class T, class Container>
    bool operator<(const queue<T, Container>& a, const queue<T, Container>& b)
    { return a.c < b.c; }

    template<class T, class Container>
    bool operator!=(const queue<T, Container>& a, const queue<T, Container>& b)
    { return !(a == b); }

    template<class T, class Container>
    bool operator>(const queue<T, Container>& a, const queue<T, Container>& b)
    { return b < a; }

    template<class T, class Container>
    bool operator<=(const queue<T, Container>& a, const queue<T, Container>& b)
    { return !(b < a); }

    template<class T, class Container>
    bool operator>=(const queue<T, Container>& a, const queue<T, Container>& b)
    { return !(a < b); }
}

#endif
