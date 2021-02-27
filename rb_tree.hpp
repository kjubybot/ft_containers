#ifndef FT_CONTAINERS_RB_TREE_HPP
#define FT_CONTAINERS_RB_TREE_HPP

#include <memory>
#include <cstddef>

namespace ft {
    enum rb_tree_color { RED = false, BLACK = true };

    template <class T>
    struct rb_tree_node {
        rb_tree_color color;
        rb_tree_node* parent;
        rb_tree_node* left;
        rb_tree_node* right;
        T val;

        static rb_tree_node* minimum(rb_tree_node* node) {
            while (node->left) node = node->left;
            return node;
        }

        static rb_tree_node* maximum(rb_tree_node* node) {
            while (node->right) node = node->right;
            return node;
        }
    };

    template <class T>
    rb_tree_node<T>* rb_tree_increment(rb_tree_node<T>* node) {
        if (node->right) {
            node = node->right;
            while (node->left)
                node = node->left;
        } else {
            rb_tree_node<T>* p = node->parent;
            while (node == p->right) {
                node = p;
                p = p->parent;
            }
            if (node->right != p)
                node = p;
        }
        return node;
    }

    template <class T>
    rb_tree_node<T>* rb_tree_decrement(rb_tree_node<T>* node) {
        if (node->color == RED && node->parent->parent == node)
            node = node->right;
        else if (node->left) {
            rb_tree_node<T>* p = node->left;
            while (p->right)
                p = p->right;
            node = p;
        } else {
            rb_tree_node<T>* p = node->parent;
            while (node == p->left) {
                node = p;
                p = p->parent;
            }
            node = p;
        }
        return node;
    }

    template <class T>
    struct rb_tree_iterator {
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef rb_tree_iterator<T> _Self;

        rb_tree_node<T>* node;

        rb_tree_iterator() : node() {}
        rb_tree_iterator(rb_tree_node<T>* node) : node(node) {}

        reference operator*() const
        { return node->val; }

        pointer operator->() const
        { return &node->val; }

        _Self& operator++() {
            node = rb_tree_increment(node);
            return *this;
        }

        _Self operator++(int) {
            _Self tmp = *this;
            node = rb_tree_increment(node);
            return tmp;
        }

        _Self& operator--() {
            node = rb_tree_decrement(node);
            return *this;
        }

        _Self operator--(int) {
            _Self tmp = *this;
            node = rb_tree_decrement(node);
            return tmp;
        }

        bool operator==(const _Self& other)
        { return node == other.node; }

        bool operator!=(const _Self& other)
        { return node != other.node; }
    };

    template <class T>
    struct rb_tree_const_iterator {
        typedef const T value_type;
        typedef const T& reference;
        typedef const T* pointer;
        typedef ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;
        typedef rb_tree_const_iterator<T> _Self;

        const rb_tree_node<T>* node;

        rb_tree_const_iterator() : node() {}
        rb_tree_const_iterator(const rb_tree_node<T>* node) : node(node) {}

        reference operator*() const
        { return node->val; }

        pointer operator->() const
        { return &node->val; }

        _Self& operator++() {
            node = rb_tree_increment(const_cast<rb_tree_node<T>*>(node));
            return *this;
        }

        _Self operator++(int) {
            _Self tmp = *this;
            node = rb_tree_increment(const_cast<rb_tree_node<T>*>(node));
            return tmp;
        }

        _Self& operator--() {
            node = rb_tree_decrement(const_cast<rb_tree_node<T>*>(node));
            return *this;
        }

        _Self operator--(int) {
            _Self tmp = *this;
            node = rb_tree_decrement(const_cast<rb_tree_node<T>*>(node));
            return tmp;
        }

        bool operator==(const _Self& other)
        { return node == other.node; }

        bool operator!=(const _Self& other)
        { return node != other.node; }
    };

    template <class Key, class Val, class Compare, class Alloc = std::allocator<Val> >
    class rb_tree {
        typedef typename Alloc::template rebind<rb_tree_node<Val> >::other node_alloc_type;
    public:
        typedef Key key_type;
        typedef Val value_type;
        typedef value_type* pointer;
        typedef const value_type* const_pointer;
        typedef value_type& reference;
        typedef const value_type& const_reference;
        typedef rb_tree_node<Val>* node_type;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef Alloc allocator_type;
        typedef rb_tree_iterator<value_type> iterator;
        typedef rb_tree_const_iterator<value_type> const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef Compare key_compare;

    private:
        rb_tree_node<value_type> header;
        size_type node_count;
        node_alloc_type node_allocator;
        Compare _comp;

        void initialize() {
            header.color = RED;
            header.parent = 0;
            header.right = &header;
            header.left = &header;
            node_count = 0;
        }

        void rotate_left(const node_type x) {
            const node_type y = x->right;
            x->right = y->left;
            if (y->left)
                y->left->parent = x;
            y->parent = x->parent;
            if (x == header.parent)
                header.parent = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;
        }

        void rotate_right(const node_type x) {
            const node_type y = x->left;
            x->left = y->right;
            if (y->right)
                y->right->parent = x;
            y->parent = x->parent;
            if (x == header.parent)
                header.parent = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->right = x;
            x->parent = y;
        }

        void insert_and_rebalance(const bool insert_left, node_type x, node_type p) {
            x->color = RED;
            x->parent = p;
            x->right = 0;
            x->left = 0;

            if (insert_left) {
                p->left = x;
                if (p == &header) {
                    header.parent = x;
                    header.right = x;
                } else if (p == header.left)
                    header.left = x;
            } else {
                p->right = x;
                if (p == header.right)
                    header.right = x;
            }

            while (x != header.parent && x->parent->color == RED) {
                node_type gp = x->parent->parent;
                if (x->parent == gp->left) {
                    node_type uncle = gp->right;
                    if (uncle && uncle->color == RED) {
                        x->parent->color = BLACK;
                        uncle->color = BLACK;
                        gp->color = RED;
                        x = gp;
                    } else {
                        if (x == x->parent->right) {
                            x = x->parent;
                            rotate_left(x);
                        }
                        x->parent->color = BLACK;
                        gp->color = RED;
                        rotate_right(gp);
                    }
                } else {
                    node_type uncle = gp->left;
                    if (uncle && uncle->color == RED) {
                        x->parent->color = BLACK;
                        uncle->color = BLACK;
                        gp->color = RED;
                        x = gp;
                    } else {
                        if (x == x->parent->left) {
                            x = x->parent;
                            rotate_right(x);
                        }
                        x->parent->color = BLACK;
                        gp->color = RED;
                        rotate_left(gp);
                    }
                }
            }
            header.parent->color = BLACK;
        }

        node_type rebalance_for_erase(const node_type z) {
            node_type x = 0;
            node_type y = z;
            node_type xp = 0;

            if (y->left == 0)
                x = y->right;
            else {
                if (y->right == 0)
                    x = y->left;
                else {
                    y = y->right;
                    while (y->left)
                        y = y->left;
                    x = y->right;
                }
            }
            if (y != z) {
                z->left->parent = y;
                y->left = z->left;
                if (y != z->right) {
                    xp = y->parent;
                    if (x) x->parent = y->parent;
                    y->parent->left = x;
                    y->right = z->right;
                    y->right->parent = y;
                }
                else
                    xp = y;
                if (z == header.parent)
                    header.parent = y;
                else if (z == z->parent->left)
                    z->parent->left = y;
                else
                    z->parent->right = y;
                y->parent = z->parent;
                std::swap(y->color, z->color);
                y = z;
            } else {
                xp = y->parent;
                if (x) x->parent = y->parent;
                if (z == header.parent)
                    header.parent = x;
                else if (z == z->parent->left)
                    z->parent->left = x;
                else
                    z->parent->right = x;
                if (header.left == z) {
                    if (z->right == 0)
                        header.left = z->parent;
                    else
                        header.left = rb_tree_node<Val>::minimum(x);
                }
                if (header.right == z) {
                    if (z->left == 0)
                        header.right = z->parent;
                    else
                        header.right = rb_tree_node<Val>::maximum(x);
                }
            }
            if (y->color == BLACK) {
                while (x != header.parent && (!x || x->color == BLACK)) {
                    if (x == xp->left) {
                        node_type sb = xp->right;
                        if (sb->color == RED) {
                            sb->color = BLACK;
                            xp->color = RED;
                            rotate_left(xp);
                            sb = xp->right;
                        }
                        if ((!sb->left || sb->left->color == BLACK) && (!sb->right || sb->right->color == BLACK)) {
                            sb->color = RED;
                            x = xp;
                            xp = xp->parent;
                        } else {
                            if (!sb->right || sb->right->color == BLACK) {
                                sb->left->color = BLACK;
                                sb->color = RED;
                                rotate_right(sb);
                                sb = xp->right;
                            }
                            sb->color = xp->color;
                            xp->color = BLACK;
                            if (sb->right)
                                sb->right->color = BLACK;
                            rotate_left(xp);
                            break;
                        }
                    } else {
                        node_type sb = xp->left;
                        if (sb->color == RED) {
                            sb->color = BLACK;
                            xp->color = RED;
                            rotate_right(xp);
                            sb = xp->left;
                        }
                        if ((!sb->left || sb->left->color == BLACK) && (!sb->right || sb->right->color == BLACK)) {
                            sb->color = RED;
                            x = xp;
                            xp = xp->parent;
                        } else {
                            if (!sb->left || sb->left->color == BLACK) {
                                sb->left->color = BLACK;
                                sb->color = RED;
                                rotate_left(sb);
                                sb = xp->left;
                            }
                            sb->color = xp->color;
                            xp->color = BLACK;
                            if (sb->left)
                                sb->left->color = BLACK;
                            rotate_right(xp);
                            break;
                        }
                    }
                }
                if (x) x->color = BLACK;
            }
            return y;
        }

        iterator insert(node_type x, node_type p, const value_type& val) {
            bool insert_left = (x != 0 || p == &header || _comp(val.first, p->val.first));
            node_type n = node_allocator.allocate(1);
            allocator_type(node_allocator).construct(&n->val, val);
            insert_and_rebalance(insert_left, n, p);
            ++node_count;
            return iterator(n);
        }

        iterator _lower_bound(node_type x, node_type y, const Key& key) {
            while (x != 0)
                if (!_comp(x->val.first, key))
                    y = x, x = x->left;
                else
                    x = x->right;
            return iterator(y);
        }

        const_iterator _lower_bound(node_type x, node_type y, const Key& key) const {
            while (x != 0)
                if (!_comp(x->val.first, key))
                    y = x, x = x->left;
                else
                    x = x->right;
            return const_iterator(y);
        }

        iterator _upper_bound(node_type x, node_type y, const Key& key) {
            while (x != 0)
                if (_comp(key, x->val.first))
                    y = x, x = x->left;
                else
                    x = x->right;
            return iterator(y);
        }

        const_iterator _upper_bound(node_type x, node_type y, const Key& key) const {
            while (x != 0)
                if (_comp(key, x->val.first))
                    y = x, x = x->left;
                else
                    x = x->right;
            return const_iterator(y);
        }

        node_type _clone_node(const node_type x) {
            node_type n = node_allocator.allocate(1);
            get_allocator().construct(&n->val, x->val);
            n->color = x->color;
            n->right = 0;
            n->left = 0;
            return n;
        }

        node_type _copy(node_type x, node_type p) {
            node_type top = _clone_node(x);
            top->parent = p;

            if (x->right)
                top->right = _copy(x->right, top);
            p = top;
            x = x->left;

            while (x) {
                node_type y = _clone_node(x);
                p->left = y;
                y->parent = p;
                if (x->right)
                    y->right = _copy(x->right, y);
                p = y;
                x = x->left;
            }
            return top;
        }

        void _erase(node_type x) {
            while (x) {
                _erase(x->right);
                node_type y = x->left;
                get_allocator().destroy(&x->val);
                node_allocator.deallocate(x, 1);
                x = y;
            }
        }
    public:
        rb_tree() : header(), node_count(0), node_allocator(), _comp()
        { initialize(); }

        rb_tree(const Compare& comp, const allocator_type& alloc = allocator_type()) : header(), node_count(0), node_allocator(alloc), _comp(comp)
        { initialize(); }

        rb_tree(const rb_tree& x) {
            if (x.header.parent) {
                header.parent = _copy(x.header.parent, &header);
                header.left = rb_tree_node<Val>::minimum(header.parent);
                header.right = rb_tree_node<Val>::maximum(header.parent);
                node_count = x.node_count;
            }
        }

        ~rb_tree()
        { _erase(header.parent); }

        rb_tree& operator=(const rb_tree& x) {
            if (this != &x) {
                clear();
                _comp = x._comp;
                if (x.header.parent) {
                    header.parent = _copy(x.header.parent, &header);
                    header.left = rb_tree_node<Val>::minimum(header.parent);
                    header.right = rb_tree_node<Val>::maximum(header.parent);
                    node_count = x.node_count;
                }
            }
            return *this;
        }

        iterator begin()
        { return iterator(header.left); }

        const_iterator begin() const
        { return const_iterator(header.left); }

        iterator end()
        { return iterator(&header); }

        const_iterator end() const
        { return const_iterator(&header); }

        reverse_iterator rbegin()
        { return reverse_iterator(end()); }

        const_reverse_iterator rbegin() const
        { return const_reverse_iterator(end()); }

        reverse_iterator rend()
        { return reverse_iterator(begin()); }

        const_reverse_iterator rend() const
        { return const_reverse_iterator(begin()); }

        bool empty() const
        { return node_count == 0; }

        size_type size() const
        { return node_count; }

        size_type max_size() const
        { return node_allocator.max_size(); }

        std::pair<iterator, bool> insert_unique(const value_type& val) {
           node_type x = header.parent;
           node_type y = &header;
           bool comp = true;

           while (x) {
               y = x;
               comp = _comp(val.first, x->val.first);
               x = comp ? x->left : x->right;
           }
           iterator j = iterator(y);
           if (comp) {
               if (j == begin())
                   return std::pair<iterator, bool>(insert(x, y, val), true);
               else
                   --j;
           }
           if (_comp(j.node->val.first, val.first))
               return std::pair<iterator, bool>(insert(x, y, val), true);
           return std::pair<iterator, bool>(j, false);
        }

        iterator insert_equal(const value_type& val) {
            node_type x = header.parent;
            node_type y = &header;

            while (x) {
                y = x;
                x = _comp(val.first, x->val.first) ? x->left : x->right;
            }
            return insert(x, y, val);
        }

        iterator insert_unique(iterator position, const value_type& val) {
            if (position.node == &header) {
                if (size() > 0 && _comp(header.right->val.first, val.first))
                    return insert(0, header.right, val);
                else
                    return insert_unique(val).first;
            } else if (_comp(val.first, position->first)) {
                iterator before = position;
                --before;
                if (position.node == header.left)
                    return insert(position.node, position.node, val);
                else if (_comp(before->first, val.first)) {
                    if (before.node->right == 0)
                        return insert(0, before.node, val);
                    else
                        return insert(position.node, position.node, val);
                } else
                    return insert_unique(val).first;
            } else if (_comp(position->first, val.first)) {
                iterator after = position;
                ++after;
                if (position.node == header.right)
                    return insert(0, position.node, val);
                else if (_comp(val.first, after->first)) {
                    if (position.node->right == 0)
                        return insert(0, position.node, val);
                    else
                        return insert(after.node, after.node, val);
                } else
                    return insert_unique(val).first;
            }
            return iterator(position.node);
        }

        iterator insert_equal(iterator position, const value_type& val) {
            if (position.node == &header) {
                if (size() > 0 && !_comp(val.first, header.right.first))
                    return insert(0, header.right, val);
                else
                    return insert_equal(val);
            } else if (!_comp(position->first, val.first)) {
                iterator before = position;
                --before;
                if (position.node == header.left)
                    return insert(position.node, position.node, val);
                else if (!_comp(val.first, before->first)) {
                    if (before.node->right == 0)
                        return insert(0, before.node, val);
                    else
                        return insert(position.node, position.node, val);
                } else
                    return insert_equal(val);
            } else {
                iterator after = position;
                ++after;
                if (position.node == header.right)
                    return insert(0, position.node, val);
                else if (!_comp(after->first, val.first)) {
                    if (position.node->right == 0)
                        return insert(0, position.node, val);
                    else
                        return insert(position.node, position.node, val);
                } else
                    return insert_equal(val);
            }
        }

        template <class InputIterator>
        void insert_unique(InputIterator first, InputIterator last) {
            for (; first != last; ++first)
                insert_unique(*first);
        }

        template <class InputIterator>
        void insert_equal(InputIterator first, InputIterator last) {
            for (; first != last; ++first)
                insert_equal(*first);
        }

        void erase(iterator position) {
            node_type y = rebalance_for_erase(position.node);
            get_allocator().destroy(&y->val);
            node_allocator.deallocate(y, 1);
            --node_count;
        }

        size_type erase(const Key& key) {
            std::pair<iterator, iterator> r = equal_range(key);
            size_type old_size = size();
            erase(r.first, r.second);
            return old_size - size();
        }

        void erase(iterator first, iterator last) {
            while (first != last)
                erase(first++);
        }

        void swap(rb_tree& x) {
            if (header.parent == 0) {
                if (x.header.parent) {
                    header.parent = x.header.parent;
                    header.right = x.header.right;
                    header.left = x.header.left;
                    header.parent->parent = &header;

                    x.header.parent = 0;
                    x.header.left = 0;
                    x.header.right = 0;
                }
            } else if (x.header.parent == 0) {
                x.header.parent = header.parent;
                x.header.right = header.right;
                x.header.left = header.left;
                x.header.parent->parent = &x.header;

                header.parent = 0;
                header.left = 0;
                header.right = 0;
            } else {
                std::swap(header.parent, x.header.parent);
                std::swap(header.left, x.header.left);
                std::swap(header.right, x.header.right);

                header.parent->parent = &header;
                x.header.parent->parent = &x.header;
            }
            std::swap(node_count, x.node_count);
            std::swap(_comp, x._comp);
        }

        void clear()
        { erase(begin(), end()); }

        key_compare key_comp() const
        { return _comp; }

        iterator find(const Key& key) {
            iterator x = _lower_bound(header.parent, &header, key);
            return (x == end() || _comp(key, x->first)) ? end() : x;
        }

        const_iterator find(const Key& key) const {
            const_iterator x = _lower_bound(header.parent, &header, key);
            return (x == end() || _comp(key, x->first)) ? end() : x;
        }

        size_type count(const Key& key) const {
            std::pair<const_iterator, const_iterator> r = equal_range(key);
            return std::distance(r.first, r.second);
        }

        iterator lower_bound(const Key& key)
        { return _lower_bound(header.parent, &header, key); }

        const_iterator lower_bound(const Key& key) const
        { return _lower_bound(header.parent, &header, key); }

        iterator upper_bound(const Key& key)
        { return _upper_bound(header.parent, &header, key); }

        const_iterator upper_bound(const Key& key) const
        { return _upper_bound(header.parent, &header, key); }

        std::pair<iterator, iterator> equal_range(const Key& key) {
            node_type x = header.parent;
            node_type y = &header;

            while (x) {
                if (_comp(x->val.first, key))
                    x = x->right;
                else if (_comp(key, x->val.first))
                    y = x, x = x->left;
                else {
                    node_type xx(x), yy(y);
                    y = x, x = x->left;
                    xx = xx->right;
                    return std::pair<iterator, iterator>(_lower_bound(x, y, key), _upper_bound(xx, yy, key));
                }
            }
            return std::pair<iterator, iterator>(iterator(y), iterator(y));
        }

        std::pair<const_iterator, const_iterator> equal_range(const Key& key) const {
            node_type x = header.parent;
            node_type y = const_cast<node_type>(&header);

            while (x) {
                if (_comp(x->val.first, key))
                    x = x->right;
                else if (_comp(key, x->val.first))
                    y = x, x = x->left;
                else {
                    node_type xx(x), yy(y);
                    y = x, x = x->left;
                    xx = xx->right;
                    return std::pair<const_iterator, const_iterator>(_lower_bound(x, y, key), _upper_bound(xx, yy, key));
                }
            }
            return std::pair<const_iterator, const_iterator>(const_iterator(y), const_iterator(y));
        }

        allocator_type get_allocator() const
        { return allocator_type(node_allocator); }
    };
}

#endif
