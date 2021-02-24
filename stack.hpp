#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "deque.hpp"

namespace ft {
    template <class T, class Container = deque<T> >
    class stack {
    protected:
        Container c;
    public:
        typedef typename Container::value_type value_type;
        typedef Container container_type;
        typedef typename Container::size_type size_type;

        explicit stack(const container_type& cont = container_type()) : c(cont) {}

        bool empty() const
        { return c.empty(); }

        size_type size() const
        { return c.size(); }

        value_type& top()
        { return c.back(); }

        const value_type& top() const
        { return c.back(); }

        void push(const value_type& val)
        { c.push_back(val); }

        void pop()
        { c.pop_back(); }
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container>& a, const stack<T, Container>& b)
    { return a.c == b.c; }

    template <class T, class Container>
    bool operator<(const stack<T, Container>& a, const stack<T, Container>& b)
    { return a.c < b.c; }

    template <class T, class Container>
    bool operator!=(const stack<T, Container>& a, const stack<T, Container>& b)
    { return !(a == b); }

    template <class T, class Container>
    bool operator>(const stack<T, Container>& a, const stack<T, Container>& b)
    { return b < a; }

    template <class T, class Container>
    bool operator<=(const stack<T, Container>& a, const stack<T, Container>& b)
    { return !(b < a); }

    template <class T, class Container>
    bool operator>=(const stack<T, Container>& a, const stack<T, Container>& b)
    { return !(a < b); }
}

#endif
