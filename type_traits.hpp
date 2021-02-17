#ifndef FT_CONTAINERS_TYPE_TRAITS_HPP
#define FT_CONTAINERS_TYPE_TRAITS_HPP

struct true_type {};
struct false_type {};

template<bool>
struct truth_type
{ typedef false_type type; };

template<>
struct truth_type<true>
{ typedef true_type type; };

template<class _Sp, class _Tp>
struct traitor {
  enum { value = bool(_Sp::value) || bool(_Tp::value) };
  typedef typename truth_type<value>::type type;
};

template<typename, typename>
struct are_same {
  enum { value = 0 };
  typedef false_type type;
};

template<typename _Tp>
struct are_same<_Tp, _Tp> {
  enum { value = 1 };
  typedef true_type type;
};

template<typename _Tp>
struct is_void {
  enum { value = 0 };
  typedef false_type type;
};

template<>
struct is_void<void> {
    enum { value = 1 };
    typedef true_type type;
};

template<typename _Tp>
struct is_integer {
    enum { value = 0 };
    typedef false_type type;
};

template<>
struct is_integer<bool> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<char> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<signed char> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<unsigned char> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<short> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<unsigned short> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<int> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<unsigned int> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<long> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<unsigned long> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<long long> {
    enum { value = 1 };
    typedef true_type type;
};

template<>
struct is_integer<unsigned long long> {
    enum { value = 1 };
    typedef true_type type;
};

#endif
