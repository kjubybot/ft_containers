#ifndef FT_CONTAINERS_FUNCTIONAL_HPP
#define FT_CONTAINERS_FUNCTIONAL_HPP

#include <functional>

template <class Pair>
struct select1st : std::unary_function<Pair, typename Pair::first_type> {
    typename Pair::first_type& operator()(Pair& p)
    { return p.first; }
    const typename Pair::first_type& operator()(const Pair& p) const
    { return p.first; }
};

template <class T>
struct identity : std::unary_function<T, T> {
    T& operator()(T& t)
    { return t; }
    const T& operator()(const T& t) const
    { return t; }
};

#endif
