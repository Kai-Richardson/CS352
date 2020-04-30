#include <cassert>
#include <iostream>
#include <memory>  // for std::unique_ptr<T>
#include <utility> // for std::move()
#include <vector>

/// A node of a binary search tree with element type T
template <typename T>
class bst
{
    T value;                    ///< the value in this node
    std::unique_ptr<bst> left;  ///< The left (less-than) subtree
    std::unique_ptr<bst> right; ///< The right (greater-than) subtree

    /// Returns either a deep clone of o, or nullptr if o is null
    static std::unique_ptr<bst> clone(const std::unique_ptr<bst> &o)
    {
        if (!o)
            return nullptr;

        bst<T> *ourClone = nullptr;      //Create our new bst
        ourClone = new bst<T>(o->value); //Copy the previous values
        ourClone->left = clone(o->left);
        ourClone->right = clone(o->right);
        return std::unique_ptr<bst>{ourClone}; //Returns unique pointer to clone
    }

public:
    /// Value constructor; constructs a node by copying the given value, with
    /// empty left and right subtrees
    bst(const T &v) : value(v), left(), right() {}

    /// Use default destructor implementation (unique_ptr destructor will free subtrees)
    ~bst() = default;

    /// Copy constructor. Should perform a deep copy of o.
    bst(const bst &o)
        : value(o.value), left(clone(o.left)), right(clone(o.right)) {}

    /// Move constructor. Steals o's subtrees without any new memory allocations.
    /// (already correct)
    bst(bst &&o) = default;

    /// Copy-assignment operator. Should perform a deep copy of o.
    bst &operator=(const bst &o)
    {
        return clone(o);
    }

    /// Move-assignment operator. Steals o's subtrees without any new memory allocation.
    /// (already correct)
    bst &operator=(bst &&o) = default;

    /// Tree iterator. Acts like a pointer to the tree values, can be advanced to the
    /// next node using pointer arithmetic. An in-order traversal (left subtree, self,
    /// right subtree).
    /// Design based on https://medium.com/algorithm-problems/binary-search-tree-iterator-19615ec585a
    class const_iterator
    {
        // allow BST class private access to implementation details
        friend bst;

        /// Stack of tree nodes that have the current node in their left subtree.
        /// Equivalently, the path from the root to the current node, skipping nodes
        /// that have already been seen. Current node is the top of the stack.
        std::vector<const bst *> nodes;

        /// Inserts this node into the iterator stack.
        /// Stores this node and its (recursive) left children on the stack.
        void fill_left(const bst *node)
        {
            if (node == nullptr) //Early return if passed junk
                return;

            nodes.push_back(node); //Push to top of stack

            if (node->left)
                fill_left(node->left.get()); //Recursively store while there's a spot
        }

        /// Builds a const_iterator for the subtree rooted at node.
        /// Initializes the stack to the path to the leftmost child
        /// of node.
        const_iterator(const bst &node) : nodes()
        {
            fill_left(&node);
        }

    public:
        /// Constructs an end iterator (empty list of nodes)
        const_iterator() = default;

        /// True if iterator is non-empty (has any nodes left).
        explicit operator bool() const
        {
            return !nodes.empty();
        }

        /// Go to next node. The current node is removed from the
        /// node stack, the next node is either the leftmost child
        /// of the current node's right child, or, if no right child
        /// exists, the previous node in the stack. This method may
        /// assume the iterator is non-empty.
        const_iterator &operator++()
        {
            const bst *old_back = nodes.back(); //Get a ref to what we pop later
            nodes.pop_back();

            if (old_back->right)
                fill_left(old_back->right.get()); //Fill starting from the old right
        }

        /// Post-increment operator
        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            operator++();
            return tmp;
        }

        /// Dereference operator; returns value of current node.
        /// May assume iterator is non-empty.
        const T &operator*() const
        {
            return nodes.back()->value;
        }

        /// Pointer-indirection operator.
        /// May assume iterator is non-empty.
        const T *operator->() const
        {
            return &operator*();
        }

        /// Checks equality of two iterators based on both empty or
        /// both have the same current node
        bool operator==(const const_iterator &o) const
        {
            if (nodes.empty() != o.nodes.empty())
                return false;
            return nodes.empty() || nodes.back() == o.nodes.back();
        }

        /// Checks inequality of two iterators.
        bool operator!=(const const_iterator &o) const
        {
            return !operator==(o);
        }
    };

    /// Get an iterator to the first node in the tree
    const_iterator begin() const { return const_iterator{*this}; }
    /// Get an iterator just after the last node in the tree
    const_iterator end() const { return const_iterator{}; }

    /// Add a new node to the tree. The node should be placed in its sorted
    /// position according to the usual BST rules. Returns true if the node
    /// was actually added, or false if it was already present.
    //  Modified from Demo 9
    bool insert(const T &passed)
    {
        if (passed < value) //left
        {
            if (left)
                return left->insert(passed);
            left = std::make_unique<bst>(passed);
            return true;
        }
        else if (value < passed) //right
        {
            if (right)
                return right->insert(passed);
            right = std::make_unique<bst>(passed);
            return true;
        }
        else
            return false; //alredy present
    }
};

/// Prints space-separated in-order traversal of t
template <typename E>
std::ostream &operator<<(std::ostream &out, const bst<E> &t)
{
    auto it = t.begin();
    out << *it; // always at least includes root node
    for (++it; it; ++it)
    {
        out << " " << *it;
    }
    return out;
}
