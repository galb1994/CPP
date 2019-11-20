/**
* @file my_set.h
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 18 September 2018
*
* @brief  This file is the header file for the "my_set" data structure. It has all the required methods' declarations
* and all the classes' definitions.
* @section LICENSE
* This program is not a free software; bla bla bla...
*/
#ifndef EX3_MY_SET_H
#define EX3_MY_SET_H

// ----------- constructors ----------- //

#include <memory>

using std :: shared_ptr;
using std :: make_shared;
using std :: weak_ptr;
using std :: pair;

// ----------- my_set class ----------- //
/**
 * @brief This class is the definition of the "my_set" data structure. It has 3 nested classes: "Node", "const_iterator"
 * and "const_reversed_iterator" that help supporting the wanted operations, like iterating over the set.
 * This is a template class, and by that enables creating a "my_set" object for every type.
 * @tparam T The variable's type
 */
template <class T>
class my_set
{
public:
    // ----------- required previous class declarations ----------- //
    class const_iterator;
    class const_reverse_iterator;
    class Node;
    // ----------- constructors ----------- //
    /**
     * @brief A default constructor
     */
    my_set(): _root(), _size(0){};
    /**
     * @brief A copy constructor
     */
    my_set(const my_set& other);
    /**
     * @brief A move constructor
     * @param other The "my_set" object we'd like to copy
     */
    my_set(my_set && other) noexcept;
    /**
     * @brief A constructor that by getting an begin iterator and an end iterator, add all the elements that we'd like
     * to add.
     * @param first The begin iterator
     * @param last The end iterator
     */
    template <class InputIterator> my_set(InputIterator first, InputIterator last);


    // ----------- destructor ----------- //
    /**
     * A destructor
     */
    ~my_set() = default;

private:
    /**
     * @brief This method is used by the copy constructor to go recursively over the binary tree
     * @param thisCurNode The node in the tree that we are currently copying to
     * @param otherCurNode The node we are currently copying from
     */
    shared_ptr<typename my_set<T> :: Node> _copyHelper(shared_ptr<typename my_set<T>::Node> otherCurNode,
                                                       shared_ptr<typename my_set<T>::Node> thisCurParent);
    /**
     * @brief This method enables the assigning operation of the "my_set" class
     * @param other The "my_set" object we'd like to assign to "this" "my_Set" object
     * @return A reference to the new object that was just built
     */

public:
    my_set &operator=(const my_set& other);

    // ----------- inserts ----------- //
    /**
     * @brief This method inserts a given element into the set
     * @param val The element we'd like to put in the set
     * @return A "pair" object that in "first" holds a const_iterator to the inserted element with the same value, and
     * int "second" holds
     */
    pair<typename my_set<T> :: const_iterator, bool> insert(const T& val);

    /**
     * @brief This method inserts a given element into the set
     * @param val The element we'd like to put in the set
     * @return A "pair" object that in "first" holds a const_iterator to the inserted element with the same value, and
     * int "second" holds
     */
    pair<typename my_set<T> :: const_iterator, bool> insert(T && val);

    /**
     * @brief This method inserts a given element into the set
     * @param position a shared pointer that holds the address of "val"'s successor in the set
     * @param val The element we'd like to put in the set
     * @return A "pair" object that in "first" holds a const_iterator to the inserted element with the same value, and
     * int "second" holds
     */
    const_iterator insert(my_set<T> :: const_iterator position, const T& val);

    /**
     * @brief This method inserts a given element into the set
     * @param position a shared pointer that holds the address of "val"'s successor in the set
     * @param val The element we'd like to put in the set
     * @return A "pair" object that in "first" holds a const_iterator to the inserted element with the same value, and
     * int "second" holds
     */
    const_iterator insert(my_set<T> :: const_iterator position, T && val);

    /**
     * @brief This method inserts a given element into the set
     * @tparam InputIterator The type of the iterator that goes over the elements we'd like to add
     * @param first The first element we'd like to add
     * @param last The past-the-end element we'd like to add
     */
    template<class InputIterator> void insert(InputIterator first, InputIterator last);

private:
    /**
     * @brief This method inserts an element to a set, by getting the root of the tree that represents the set
     * @param curNode The current node we compare it's value to the given element (starts at the root)
     * @param val The element we'd like to add to the set
     * @return  A "pair" object that in "first" holds a const_iterator to the inserted element with the same value, and
     * int "second" holds
     */
    pair<typename my_set<T> :: const_iterator, bool> _insertHelper(shared_ptr<typename my_set<T>::Node> curNode,
                                                                   T val);

    // ----------- clear ----------- //
public:
    /**
     * @brief This method erases the whole set
     */
    void clear() noexcept;

    // ----------- swap ----------- //
    /**
     * @brief This method swaps two sets
     * @param other
     */
    void swap(my_set& other) noexcept;

    // ----------- erases ----------- //
    /**
     * @brief This method erases an element from the set
     * @param position The position of the element that we'd like to erase
     * @return A const_iterator object that points to the erased element's successor
     */
    const_iterator erase(const_iterator position);

private:
    /**
     * @brief THis method erases a leaf from a tree
     * @param curNode The node we'd like to erase
     * @return A const_iterator object that points to the erased element's successor
     */
    const_iterator _eraseLeaf(shared_ptr<typename my_set<T>::Node> curNode);

    /**
     * @brief This method sets the trees pointers as required in the case of wanting to erase the max/min element of
     * the set
     * @param toErase The element we'd like to erase
     * @return 1 iff the erased element was the last one on the set, 0 otherwise
     */
    int _eraseMinOrMax(shared_ptr<typename my_set<T>::Node> toErase);

    /**
     * @brief This method erases a node with one child from a tree
     * @param toErase The node we'd like to erase
     * @param toEraseIsALeftChild Tells us if wether "toErase" is a left child to it's parent, or a right one
     * @return A const_iterator object that points to the erased element's successor
     */
    const_iterator _eraseNodeWithOneChild(shared_ptr<typename my_set<T>::Node> toErase, bool toEraseIsALeftChild);

    /**
     * @brief This method erases a node with two children from a tree
     * @param toErase The node we'd like to erase
     * @return A const_iterator object that points to the erased element's successor
     */
    const_iterator _eraseNodeWithTwoChildren(shared_ptr<typename my_set<T>::Node> toErase);

    /**
     * @brief This method switches a node and its successor's positions in the tree
     * @param toErase The element that we'd like to erase
     * @param successor "toErase"'s successor
     */
    void _switchNodeAndItsSuccessor(shared_ptr<typename my_set<T>::Node> toErase,
                                    shared_ptr<typename my_set<T>::Node> successor);
public:
    /**
     * @brief This method erases an element from a set
     * @param val The element that we'd like to erase
     * @return 1 iff we erasure succeeded, 0 otherwise
     */
    size_t erase(const T& val);

    /**
     * @brief This method erases a number of elements from the set
     * @param first The first element we'd like to erase
     * @param last The past-by-end element that we'd like to erase
     * @return A const_iterator object that points to the erased element's successor
     */
    const_iterator erase(const_iterator first, const_iterator last);

    // ----------- c/cr begin/end ----------- //
    /**
     * @return A const_iterator object to the first element in the set
     */
    const_iterator cbegin() const;

    /**
     * @return A const_iterator object to the past-by-last element in the set
     */
    const_iterator cend() const;

    /**
     * @return A const_reverse_iterator object to the last element in the set
     */
    const_reverse_iterator crbegin() const;

    /**
     * @return A const_reverse_iterator object to the one-before-first element in the set
     */
    const_reverse_iterator crend() const;


    // ----------- finds ----------- //
private:
    /**
     * @brief This method searches for an element in a set
     * @param curNode The current node that we compare to the given element
     * @param val The element that we look for
     * @return A shared pointer that points to the element in the set if the element was found, shared pointer that
     * points to the element's successor otherwise
     */
    shared_ptr<typename my_set<T> :: Node> _findNumOrSuccessor(shared_ptr<typename my_set<T>::Node> curNode,
                                                               const T &val);
    /**
     * @brief This method searches for an element in a set
     * @param curNode The current node that we compare to the given element
     * @param val The element that we look for
     * @return A const_iterator object that points to the element if it was found, points to nullptr otherwise
     */
    const_iterator _findHelper(shared_ptr<typename my_set<T>::Node> curNode, const T &num) const;

public:
    /**
     * @brief This method searches for an element in a set
     * @param val The element that we look for
     * @return A const_iterator object that points to the element if it was found, points to nullptr otherwise
     */
    const_iterator find(const T& val) const;

    /**
     * @brief This method searches for an element in a set
     * @param val The element that we look for
     * @return A const_iterator object that points to the element if it was found, points to nullptr otherwise
     */
    const_iterator find(const T& val);

    // ----------- class Node ----------- //
    /**
     * @brief This class defines a single set element as a tree node
     */
    class Node
    {
    public:

        // ----------- Node constructors ----------- //
        /**
         * @brief A default constructor
         */
        Node(){};
        /**
         * A constructor
         * @param value The value of this node
         * @param left The left child of this node
         * @param right The right child of this node
         * @param par The parent of this node
         */
        Node(const T& value, shared_ptr<Node> left = nullptr, shared_ptr<Node> right = nullptr,
             weak_ptr<Node> par = weak_ptr<Node>()): val(value), _leftChild(left), _rightChild(right), _parent(par){}

        // ----------- Node fields ----------- //
        T val;
        shared_ptr<Node> _leftChild;
        shared_ptr<Node> _rightChild;
        weak_ptr<Node> _parent;
    };

    // ----------- getSuccessor/Predecessor ----------- //

private:
    /**
     * @return The tree's root
     */
    shared_ptr<Node> _getRoot();
    /**
     * @param curNode The current node
     * @return The minimum element of the set
     */
    static shared_ptr<Node> _getMin(shared_ptr<Node> curNode);

    /**
     *
     * @param curNode The current node
     * @return The maximum element of the set
     */
    static shared_ptr<Node> _getMax(shared_ptr<Node> curNode);

    /**
     * @param curNode The current node
     * @return The first parent in the given node's path to the root that is bigger than it's child
     */
    static shared_ptr<Node> _getFirstRightParent(shared_ptr<Node> curNode);

    /**
     * @param curNode The current node
     * @return The first parent in the given node's path to the root that is smaller than it's child
     */
    static shared_ptr<Node> _getFirstLeftParent(shared_ptr<Node> curNode);

    /**
     * @brief This method finds a given element's successor
     * @param node The node we'd like to find the successor of
     * @return A pointer to the successor
     */
    static shared_ptr<Node> _getSuccessor(shared_ptr<Node> node);

    /**
     * @brief This method finds a given element's predecessor
     * @param node The node we'd like to find the predecessor of
     * @return A pointer to the predecessor
     */
    static shared_ptr<Node> _getPredecessor(shared_ptr<Node> node);


    // ----------- class const_iterator ----------- //
public:
    /**
     * @brief This class represents a forward iterator for the "my_set" class
     */
    class const_iterator
    {
    public:

        // ----------- const_iterator constructor ----------- //
        /**
         * @brief A constructor
         * @param p
         */
        const_iterator(shared_ptr<Node> p = nullptr): _pointer(p){};

        // ----------- operators  ----------- //
        /**
         * @return The value of the element that is pointed by "this" iterator
         */
        const T& operator*() const;

        /**
         * @return The address of the element that is pointed by "this" iterator
         */
        const T* operator->() const;

        /**
         * @brief This method enables the operation of "++ iter" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
        virtual const_iterator& operator++();

        /**
         * @brief This method enables the operation of "iter ++" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
        virtual const_iterator operator++(int);

        /**
         * @brief This method enables the operation of "-- iter" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
        virtual const_iterator& operator--();

        /**
         * @brief This method enables the operation of "iter --" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
        virtual const_iterator operator--(int);

        /**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff equal, false otherwise
         */
        bool operator==(const_iterator const& other) const;

        /**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff different, false otherwise
         */
        bool operator!=(const_iterator const& other) const;

        /**
         * @return The pointer
         */
        shared_ptr<Node> getPointer() const{return _pointer; }

    protected:
        shared_ptr<Node> _pointer;
    };

    // ----------- class const_reverse_iterator ----------- //
    /**
     * @brief This class represents a backward iterator for the "my_set" class
     */
    class const_reverse_iterator: public const_iterator
    {
    public:

        // ----------- constructor ----------- //
        /**
         * A onstructor
         * @param p The poiner
         */
        const_reverse_iterator(shared_ptr<Node> p = nullptr): const_iterator(p){};

        // ----------- operators ----------- //
        /**
         * @brief This method enables the operation of "iter --" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
        const_iterator &operator--() override;

        /**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff equal, false otherwise
         */
        const_iterator operator--(int) override;

        /**
         * @brief This method enables the operation of "++ iter" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
        const_iterator& operator++() override;

        /**
         * @brief This method enables the operation of "iter ++" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
        const_iterator operator++(int) override;

        /**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff different, false otherwise
         */
        bool operator==(const_reverse_iterator const& other) const;

        /**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff different, false otherwise
         */
        bool operator!=(const_reverse_iterator const& other) const;

    };

    // ----------- support methods ----------- //
    /**
     * @return The set's currentsize
     */
    size_t size();

    /**
     * @return true for an empty set, false otherwise
     */
    bool empty();

private:
    // ----------- my_set fields ----------- //
    shared_ptr<Node> _root;
    size_t _size;
};

#include "my_set.hpp"
#endif //EX3_MY_SET_H


