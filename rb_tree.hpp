#ifndef FT_CONTAINERS_RB_TREE_HPP
#define FT_CONTAINERS_RB_TREE_HPP

#include <memory>

namespace ft {
    enum rb_tree_color { RED = false, BLACK = true };

    template <class T>
    struct rb_tree_node {
        rb_tree_color color;
        rb_tree_node* parent;
        rb_tree_node* left;
        rb_tree_node* right;
        T val;

        static rb_tree_node* minimum(const rb_tree_node* node) {
            while (node->left) node = node->left;
            return node;
        }

        static rb_tree_node* maximum(const rb_tree_node* node) {
            while (node->right) node = node->right;
            return node;
        }
    };

    template <class T>
    rb_tree_increment(const rb_tree_node<T>* node) {
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
            if (node->right == p)
                node = p;
        }
        return node;
    }

    template <class T>
    rb_tree_decrement(const rb_tree_node<T>* node) {
        if (node->color == RED && node->parent->parent == node)
            node = node->right;
        else if (node->left) {
            node = node->left;
            while (node->right)
                node = node->right;
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

    template <class Key, class Val, class Compare, class Alloc = allocator<Val> >
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
        // const_iterator
        typedef std::reverse_iterator<iterator> reverse_iterator;
        // const reverse iterator

    private:
        rb_tree_node<value_type> header;
        size_type node_count;

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

        iterator insert_and_rebalance(const bool insert_left, node_type x, node_type p) {
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
                    if (uncle->color == RED) {
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
                    if (uncle->color == RED) {
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
            header.parent->color = BLACK;
            }
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
                if (z == header.parent)
                    header.parent = y;
                else if (z == z->parent->left)
                    z->parent->left = y;
                else
                    z->parent->right = y;
                y->parent = z->parent;
                y->color = z->color;
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
                        header.left = rb_tree_node<T>::minimum(x);
                }
                if (header.right == z) {
                    if (z->left == 0)
                        header.right = z->parent;
                    else
                        header.right = rb_tree_node<T>::maximum(x);
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
    public:
        rb_tree()
        { initialize(); }

        iterator begin()
        { return iterator(header.left); }

        iterator end()
        { return iterator(&header); }
    };

}

#endif
