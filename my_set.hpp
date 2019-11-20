/**
* @file my_set.hpp
* @author  Gal Batzia <gal.batzia@mail.huji.ac.il>
* @version 1.0
* @date 18 September 2018
*
* @brief  This file holds the implementations of all the required methods for the "my_set" data structure. It has all
* and all the classes' definitions.
* @section LICENSE
* This program is not a free software; bla bla bla...
*/
#ifndef EX3_MY_SET_HPP
#define EX3_MY_SET_HPP

// ----------- defines ----------- //
/**
 * Tells us if the element that was just erased is the only element in the set
 */
#define LAST_NODE_WAS_ERASED 1

/**
 * Tells us if the element that was just erased isn't the only element in the set
 */
#define REGULAR_ERASURE 0

#include "my_set.h"

using std :: shared_ptr;
using std :: make_shared;
using std :: weak_ptr;
using std :: pair;
using std :: make_pair;

// ----------- constructors ----------- //
/**
 * @brief A copy constructor
 */
template<class T>
my_set<T> :: my_set(const my_set &other)
{
    shared_ptr<Node> otherTemp = other._root;
    this -> _root = _copyHelper(otherTemp, nullptr);
    this -> _size = other._size;
}

/**
 * @brief This method is used by the copy constructor to go recursively over the binary tree
 * @param thisCurNode The node in the tree that we are currently copying to
 * @param otherCurNode The node we are currently copying from
 */
template<class T>
shared_ptr<typename my_set<T> :: Node> my_set<T> :: _copyHelper(shared_ptr<my_set<T>::Node> otherCurNode,
                                                                shared_ptr<my_set<T>::Node> thisCurParent)
{
    if(otherCurNode == nullptr)
    {
        return nullptr;
    }
    shared_ptr<my_set<T> :: Node> thisCurNode = make_shared<my_set<T> :: Node>(otherCurNode -> val, nullptr,
                                                                               nullptr, thisCurParent);
    thisCurNode -> _leftChild = _copyHelper(otherCurNode->_leftChild, thisCurNode);
    thisCurNode -> _rightChild = _copyHelper(otherCurNode->_rightChild, thisCurNode);
    return thisCurNode;
}


/**
 * @brief A move constructor
 * @param other The "my_set" object we'd like to copy
 */
template<class T>
my_set<T> :: my_set(my_set && other) noexcept
{
    this -> _root = other._root;
    this -> _size = other._size;
    other.clear();
}

/**
 * @brief A constructor that by getting an begin iterator and an end iterator, add all the elements that we'd like
 * to add.
 * @param first The begin iterator
 * @param last The end iterator
 */
template<class T> template <class InputIterator> my_set<T> :: my_set(InputIterator first, InputIterator last)
{
    _size = 0;
    for(InputIterator iter = first; iter != last; ++ iter)
    {
        insert(*iter);
    }
}

// ----------- inserts ----------- //
/**
     * @brief This method enables the assigning operation of the "my_set" class
     * @param other The "my_set" object we'd like to assign to "this" "my_Set" object
     * @return A reference to the new object that was just built
     */
template<class T>
my_set<T> &my_set<T> :: operator=(const my_set &other)
{
    this -> _root = nullptr;
    shared_ptr<Node> otherTemp = other._root;
    this -> _root = _copyHelper(otherTemp, nullptr);
    this -> _size = other . _size;
    return *this;
}

/**
     * @brief This method inserts a given element into the set
     * @param val The element we'd like to put in the set
     * @return A "pair" object that in "first" holds a const_iterator to the inserted element with the same value, and
     * int "second" holds
     */
template <class T>
pair<typename my_set<T>  :: const_iterator, bool> my_set<T> :: insert(const T& val)
{
    shared_ptr<Node> temp  = _root;
    return _insertHelper(temp, val);
}

/**
     * @brief This method inserts a given element into the set
     * @param val The element we'd like to put in the set
     * @return A "pair" object that in "first" holds a const_iterator to the inserted element with the same value, and
     * int "second" holds
     */
template<class T>
pair<typename my_set<T> :: const_iterator, bool> my_set<T> :: insert(T && val)
{
    shared_ptr<Node> temp  = _root;
    return _insertHelper(temp, val);
}

/**
     * @brief This method inserts a given element into the set
     * @param position a shared pointer that holds the address of "val"'s successor in the set
     * @param val The element we'd like to put in the set
     * @return A "pair" object that in "first" holds a const_iterator to the inserted element with the same value, and
     * int "second" holds
     */
template<class T>
typename
my_set<T> :: const_iterator my_set<T> :: insert(my_set<T> :: const_iterator position, const T &val)
{
    shared_ptr<my_set<T> :: Node> findInSetResult = _findNumOrSuccessor(_root, val);
    if(findInSetResult != position.getPointer())
    {
        ++ _size;
        return const_iterator(insert(val).first); // In case the position is not relevant (isn't the successor)
    }
    shared_ptr<my_set<T> :: Node> newNode = make_shared<my_set<T> :: Node>(val);
    shared_ptr<my_set<T> :: Node> maxElement = _getMax(_root);
    if(position.getPointer() == nullptr)
    {
        if(maxElement -> val < val)
        {
            maxElement -> _rightChild = newNode;
            newNode -> _parent = maxElement;
        }
    }
    shared_ptr<my_set<T> :: Node> predecessor = _getPredecessor(position.getPointer());
    if(predecessor == nullptr) // In case we are trying to insert an element that is smaller than minElement
    {
        shared_ptr<my_set<T> :: Node> minElement = _getMin(_root);
        minElement -> _leftChild = newNode;
        newNode -> _parent = minElement;
    }
    else if(predecessor == position.getPointer() -> _parent.lock()) // "predecessor" is the _parent of "position"
    {
        position.getPointer() -> _leftChild = newNode;
        newNode -> _parent = position.getPointer();
    }
    else // "predecessor" is not the _parent of "position"
    {
        predecessor -> _rightChild = newNode;
        newNode -> _parent = predecessor;
    }
    ++ _size;
    return const_iterator(newNode);
}

/**
 * @brief This method inserts an element to a set, by getting the root of the tree that represents the set
 * @param curNode The current node we compare it's value to the given element (starts at the root)
 * @param val The element we'd like to add to the set
 * @return  A "pair" object that in "first" holds a const_iterator to the inserted element with the same value, and
 * int "second" holds
 */
template <class T>
pair<typename my_set<T>  :: const_iterator, bool> my_set<T> :: _insertHelper(shared_ptr<my_set::Node> curNode, T val)
{
    if(curNode == nullptr) // In the case of an empty tree
    {
        shared_ptr<my_set :: Node> newNode = make_shared<my_set :: Node>(val);
        _root = newNode;
        ++ _size;
        return make_pair(const_iterator(_root), true);
    }
    if(curNode -> val > val)
    {
        if(curNode -> _leftChild == nullptr)
        {
            shared_ptr<my_set :: Node> newNode = make_shared<my_set :: Node>(val, nullptr, nullptr, curNode);
            curNode-> _leftChild = newNode;
            ++ _size;
            return make_pair(const_iterator(newNode), true);
        }
        else
        {
            return _insertHelper(curNode->_leftChild, val);
        }
    }
    if(curNode -> val < val)
    {
        if(curNode -> _rightChild == nullptr)
        {
            shared_ptr<my_set :: Node> newNode = make_shared<my_set :: Node>(val, nullptr, nullptr, curNode);
            curNode-> _rightChild = newNode;
            ++ _size;
            return make_pair(const_iterator(newNode), true);
        }
        else
        {
            return _insertHelper(curNode->_rightChild, val);
        }
    }
    return make_pair(const_iterator(curNode), false); // The number is already in the set
}

/**
 * @brief This method inserts a given element into the set
 * @tparam InputIterator The type of the iterator that goes over the elements we'd like to add
 * @param first The first element we'd like to add
 * @param last The past-the-end element we'd like to add
 */
template<class T>
template<class InputIterator>
void my_set<T> :: insert(InputIterator first, InputIterator last)
{
    for(InputIterator iter = first; iter != last; ++ iter)
    {
        insert(*iter);
    }
}

template<class T>
typename
my_set<T> :: const_iterator my_set<T> :: insert(my_set<T> :: const_iterator position, T && val)
{
    return insert(position, val);
}

// ----------- finds ----------- //

/**
 * @brief This method searches for an element in a set
 * @param curNode The current node that we compare to the given element
 * @param val The element that we look for
 * @return A shared pointer that points to the element in the set if the element was found, shared pointer that
 * points to the element's successor otherwise
 */
template<class T>
shared_ptr<typename my_set<T> :: Node> my_set<T> :: _findNumOrSuccessor(shared_ptr<my_set<T>::Node> curNode,
                                                                        const T &val)
{
    if(curNode -> val == val)
    {
        return curNode;
    }
    if(curNode -> _leftChild == nullptr && curNode -> _rightChild == nullptr)
    {
        if(curNode -> val > val)
        {
            return curNode;
        }
        return _getSuccessor(curNode); // In case of a number that is bigger than maxElement, returns nullptr
    }
    if(curNode -> val > val)
    {
        if(curNode -> _leftChild == nullptr)
        {
            return curNode;
        }
        return _findNumOrSuccessor(curNode->_leftChild, val);
    }
    if(curNode -> val < val)
    {
        if(curNode -> _rightChild == nullptr)
        {
            return nullptr; // In case of a number that is bigger than maxElement, returns nullptr
        }
        return _findNumOrSuccessor(curNode->_rightChild, val);
    }
    return nullptr;
}

/**
     * @brief This method searches for an element in a set
     * @param val The element that we look for
     * @return A const_iterator object that points to the element if it was found, points to nullptr otherwise
     */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: find(const T &val) const
{
    return _findHelper(_root, val);
}

/**
     * @brief This method searches for an element in a set
     * @param val The element that we look for
     * @return A const_iterator object that points to the element if it was found, points to nullptr otherwise
     */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: find(const T &val)
{
    return _findHelper(_root, val);
}

/**
     * @brief This method searches for an element in a set
     * @param curNode The current node that we compare to the given element
     * @param val The element that we look for
     * @return A const_iterator object that points to the element if it was found, points to nullptr otherwise
     */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: _findHelper(shared_ptr<my_set<T>::Node> curNode, const T &num) const
{
    if(curNode == nullptr)
    {
        return const_iterator(nullptr);
    }
    if(curNode -> val > num)
    {
        return _findHelper(curNode->_leftChild, num);
    }
    if(curNode -> val < num)
    {
        return _findHelper(curNode->_rightChild, num);
    }
    return const_iterator(curNode);
}

// ----------- clear ----------- //
/**
 * @brief This method erases the whole set
 */
template<class T>
void my_set<T> :: clear() noexcept
{
    _root = nullptr;
    _size = 0;
}

// ----------- erases ----------- //
/**
     * @brief This method erases an element from the set
     * @param position The position of the element that we'd like to erase
     * @return A const_iterator object that points to the erased element's successor
     */
template <class T>
typename my_set<T> :: const_iterator my_set<T> :: erase(const_iterator position)
{
    shared_ptr<my_set<T> :: Node> toErase = position.getPointer();
    const_iterator iter(_getSuccessor(toErase));
    if(toErase == nullptr || _eraseMinOrMax(toErase))
    {
        return const_iterator(nullptr);
    }
    if(toErase -> _leftChild  == nullptr && toErase -> _rightChild == nullptr)
    {
        -- _size;
        return _eraseLeaf(toErase);
    }
    if((toErase -> _leftChild  == nullptr) ^ (toErase -> _rightChild  == nullptr))
    {
        if(toErase == _root)
        {
            if(toErase -> _rightChild == nullptr)
            {
                toErase -> _leftChild -> _parent = weak_ptr<Node>(); // Sets the new Root's _parent to "null"
                _root = toErase -> _leftChild;
            }
            else
            {
                toErase -> _rightChild -> _parent = weak_ptr<Node>(); // Sets the new Root's _parent to "null"
                _root = toErase -> _rightChild;
            }
            -- _size;
            return iter;
        }
        else
        {
            -- _size;
            return _eraseNodeWithOneChild(toErase, toErase->val < (toErase->_parent.lock())->val);
        }
    }
    -- _size;
    return _eraseNodeWithTwoChildren(toErase);

}

/**
     * @brief THis method erases a leaf from a tree
     * @param curNode The node we'd like to erase
     * @return A const_iterator object that points to the erased element's successor
     */
template <class T>
typename my_set<T> :: const_iterator my_set<T> :: _eraseLeaf(shared_ptr<typename my_set<T>::Node> toErase)
{
    if(toErase == _root)
    {
        my_set<T> :: const_iterator iter(_getSuccessor(_root));
        _root = nullptr;
        return iter;
    }
    shared_ptr<my_set<T> :: Node> tempParent = toErase -> _parent.lock();
    my_set<T> :: const_iterator iter(_getSuccessor(toErase));
    if(tempParent -> _leftChild == toErase)
    {
        tempParent -> _leftChild = nullptr;
    }
    if(tempParent -> _rightChild == toErase)
    {
        tempParent -> _rightChild = nullptr;
    }
    return iter;
}

/**
     * @brief This method sets the trees pointers as required in the case of wanting to erase the max/min element of
     * the set
     * @param toErase The element we'd like to erase
     * @return 1 iff the erased element was the last one on the set, 0 otherwise
     */
template<class T>
int my_set<T> :: _eraseMinOrMax(shared_ptr<typename my_set<T>::Node> toErase)
{
    shared_ptr<my_set<T> :: Node> maxElement = _getMax(_root);
    if(toErase == maxElement)
    {
        if(maxElement == _root)
        {
            if(maxElement -> _leftChild == nullptr && maxElement -> _rightChild == nullptr)
            {
                -- _size;
                _root = nullptr;
                return LAST_NODE_WAS_ERASED;
            }
            else
            {
                maxElement = maxElement -> _leftChild;
            }
        }
        else
        {
            shared_ptr<my_set<T> :: Node> tempParent = toErase -> _parent.lock();
            maxElement = tempParent;
        }
    }
    shared_ptr<my_set<T> :: Node> minElement = _getMin(_root);
    if(toErase == minElement)
    {
        minElement = _getSuccessor(minElement);
    }
    return REGULAR_ERASURE;
}

/**
     * @brief This method erases a node with one child from a tree
     * @param toErase The node we'd like to erase
     * @param toEraseIsALeftChild Tells us if wether "toErase" is a left child to it's parent, or a right one
     * @return A const_iterator object that points to the erased element's successor
     */
template <class T>
typename my_set<T> :: const_iterator my_set<T>::_eraseNodeWithOneChild(shared_ptr<typename my_set<T>::Node> toErase,
                                                                       bool toEraseIsALeftChild)
{
    shared_ptr<my_set<T> :: Node> child;
    if(toErase -> _leftChild == nullptr)
    {
        child = toErase -> _rightChild;
    }
    else
    {
        child = toErase -> _leftChild;
    }

    child -> _parent = toErase -> _parent;
    shared_ptr<my_set<T> :: Node> toEraseParent = toErase -> _parent.lock();
    const_iterator iter(_getSuccessor(toErase));
    if(toEraseIsALeftChild)
    {
        toEraseParent -> _leftChild = child;
    }
    else
    {
        toEraseParent -> _rightChild = child;
    }
    return iter;
}

/**
     * @brief This method erases a node with two children from a tree
     * @param toErase The node we'd like to erase
     * @return A const_iterator object that points to the erased element's successor
     */
template<class T>
typename
my_set<T> :: const_iterator my_set<T>::_eraseNodeWithTwoChildren(shared_ptr<typename my_set<T>::Node> toErase)
{
    const_iterator iter(_getSuccessor(toErase));
    shared_ptr<my_set<T> :: Node> successor = _getSuccessor(toErase);
    _switchNodeAndItsSuccessor(toErase, successor);
    if(toErase -> _leftChild == nullptr)
    {
        if(toErase -> _rightChild == nullptr)
        {
            return _eraseLeaf(toErase);
        }
        else
        {
            return _eraseNodeWithOneChild(toErase, !(toErase->_parent.lock() == successor));
        }
    }
    return iter;
}

/**
     * @brief This method switches a node and its successor's positions in the tree
     * @param toErase The element that we'd like to erase
     * @param successor "toErase"'s successor
     */
template<class T>
void my_set<T> :: _switchNodeAndItsSuccessor(shared_ptr<typename my_set<T>::Node> toErase,
                                             shared_ptr<typename my_set<T>::Node> successor)
{
    shared_ptr<my_set<T> :: Node> successorParent = successor -> _parent.lock();
    shared_ptr<my_set<T> :: Node> successorChild = successor -> _rightChild;
    if(toErase == _root)
    {
        _root = successor;
        successor -> _parent = weak_ptr<Node>();
    }
    else
    {
        successor -> _parent = toErase -> _parent;
        if(toErase -> val > (toErase -> _parent).lock() -> val)
        {
            (toErase -> _parent).lock() -> _rightChild = successor;
        }
        else
        {
            (toErase -> _parent).lock() -> _leftChild = successor;
        }
    }
    successor -> _leftChild = toErase -> _leftChild;
    if(successor == toErase -> _rightChild)
    {
        toErase -> _parent = successor;
        successor -> _rightChild = toErase;
        toErase -> _rightChild = nullptr;
    }
    else
    {
        toErase -> _parent = successorParent;
        successorParent -> _leftChild = toErase;
        successor -> _rightChild = toErase -> _rightChild;
        toErase -> _rightChild -> _parent = successor;
    }
    toErase -> _leftChild -> _parent = successor;
    toErase -> _rightChild = successorChild;
    toErase -> _leftChild = nullptr;
}

/**
     * @brief This method erases an element from a set
     * @param val The element that we'd like to erase
     * @return 1 iff we erasure succeeded, 0 otherwise
     */
template<class T>
size_t my_set<T> :: erase(const T &val)
{
    const_iterator toEraseIterator = find(val);
    if(toEraseIterator.getPointer() == nullptr)
    {
        return 0;
    }
    erase(toEraseIterator);
    return 1;
}

/**
     * @brief This method erases a number of elements from the set
     * @param first The first element we'd like to erase
     * @param last The past-by-end element that we'd like to erase
     * @return A const_iterator object that points to the erased element's successor
     */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: erase(my_set<T> :: const_iterator first,
                                                        my_set<T> :: const_iterator last)
{
    const_iterator iterator;
    if(*first > *last)
    {
        return first;
    }
    for(my_set<T> :: const_iterator iter = first; iter != last; ++ iter)
    {
        iterator = erase(iter);
        if(iterator.getPointer() != nullptr)
        {
            --_size;
        }
    }
    return last;
}

// ----------- getSuccessor/Predecessor ----------- //
/**
     * @param curNode The current node
     * @return The minimum element of the set
     */
template <class T>
shared_ptr<typename my_set<T> :: Node> my_set<T> :: _getMin(shared_ptr<my_set::Node> curNode)
{
    if(curNode == nullptr) // Handles the case of an empty set
    {
        return nullptr;
    }
    if(curNode -> _leftChild == nullptr)
    {
        return curNode;
    }
    return _getMin(curNode->_leftChild);
}

/**
     * @param curNode The current node
     * @return The maximum element of the set
     */
template <class T>
shared_ptr<typename my_set<T> :: Node> my_set<T> :: _getMax(shared_ptr<my_set::Node> curNode)
{
    if(curNode == nullptr) // Handles the case of an empty set
    {
        return nullptr;
    }
    if(curNode -> _rightChild == nullptr)
    {
        return curNode;
    }
    return _getMax(curNode->_rightChild);
}

/**
 * @brief This method returns a given element's successor
 * @tparam T The type
 * @param node The element we'd like to find thee successor of
 * @return A pointer to the successor
 */
template <class T>
shared_ptr<typename my_set<T> :: Node> my_set<T> :: _getSuccessor(shared_ptr<my_set::Node> node)
{
    if(node -> _rightChild != nullptr)
    {
        return _getMin(node->_rightChild);
    }
    shared_ptr <Node> tempParent = node -> _parent.lock();
    return _getFirstRightParent(node);  // In case of looking for the successor of the max element, returns nullptr
}

/**
     * @brief This method finds a given element's predecessor
     * @param node The node we'd like to find the predecessor of
     * @return A pointer to the predecessor
     */
template <class T>
shared_ptr<typename my_set<T> :: Node> my_set<T> :: _getPredecessor(shared_ptr<my_set<T>::Node> node)
{
    if(node -> _leftChild != nullptr)
    {
        return _getMax(node->_leftChild);
    }
    shared_ptr <Node> tempParent = node -> _parent.lock();
    return _getFirstLeftParent(node);  // In case of looking for the successor of the min element,
                                                   // throws an exception
}

/**
     * @param curNode The current node
     * @return The first parent in the given node's path to the root that is bigger than it's child
     */
template <class T>
shared_ptr<typename my_set<T> :: Node> my_set<T> :: _getFirstRightParent(shared_ptr<my_set::Node> curNode)
{
    shared_ptr<Node> curParent = (curNode -> _parent).lock();
    if(curParent == nullptr) // This means we got to the _root
    {
        return nullptr;
    }
    if(curParent -> _leftChild == curNode)
    {
        return curParent;
    }
    return _getFirstRightParent(curParent);
}

/**
     * @param curNode The current node
     * @return The first parent in the given node's path to the root that is smaller than it's child
     */
template <class T>
shared_ptr<typename my_set<T> :: Node> my_set<T> :: _getFirstLeftParent(shared_ptr<my_set::Node> curNode)
{
    shared_ptr<Node> curParent = (curNode -> _parent).lock();
    if(curParent == nullptr) // This means we got to the _root
    {
        return nullptr;
    }
    if(curParent -> _rightChild == curNode)
    {
        return curParent;
    }
    return _getFirstLeftParent(curParent);
}

/**
 * @return The tree's root
 */
template<class T>
shared_ptr<typename my_set<T> :: Node> my_set<T> :: _getRoot()
{
    return _root;
}

// ----------- begins & ends ----------- //
/**
     * @return A const_iterator object to the first element in the set
     */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: cbegin() const
{

    return const_iterator(_getMin(_root));
}

/**
     * @return A const_iterator object to the past-by-last element in the set
     */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: cend() const
{
    return const_iterator(nullptr);
}

/**
     * @return A const_reverse_iterator object to the last element in the set
     */
template<class T>
typename
my_set<T> :: const_reverse_iterator my_set<T> :: crbegin() const
{
    return my_set::const_reverse_iterator(_getMax(_root));
}

/**
     * @return A const_reverse_iterator object to the one-before-first element in the set
     */
template<class T>
typename
my_set<T> :: const_reverse_iterator my_set<T> :: crend() const
{
    return const_reverse_iterator(nullptr);
}

/**
     * @return The set's currentsize
     */
template<class T>
size_t my_set<T> :: size()
{
    return _size;
}

/**
     * @return true for an empty set, false otherwise
     */
template<class T>
bool my_set<T> :: empty()
{
    return _size == 0;
}

/**
     * @brief This method swaps two sets
     * @param other
     */
template<class T>
void my_set<T> :: swap(my_set &other) noexcept
{
    shared_ptr<my_set<T> :: Node> tempRoot = this -> _root;
    this -> _root = other._root;
    other._root = tempRoot;
    size_t tempSize = this -> _size;
    this -> _size = other._size;
    other._size = tempSize;
}


// ----------- const_iterator operators ----------- //

/**
         * @return The value of the element that is pointed by "this" iterator
         */
template<class T>
const T& my_set<T> :: const_iterator :: operator*() const {return _pointer -> val; }

/**
         * @return The address of the element that is pointed by "this" iterator
         */
template<class T>
const T* my_set<T> :: const_iterator :: operator->() const {return &_pointer -> val; }

/**
         * @brief This method enables the operation of "++ iter" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
template<class T>
typename my_set<T> :: const_iterator &my_set<T> :: const_iterator :: operator++()
{
    _pointer = _getSuccessor(_pointer);
    return *this;
}

/**
         * @brief This method enables the operation of "iter ++" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: const_iterator :: operator++(int)
{
    const_iterator temp = *this;
    _pointer = _getSuccessor(_pointer);
    return temp;
}

/**
         * @brief This method enables the operation of "-- iter" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
template<class T>
typename my_set<T> :: const_iterator &my_set<T> :: const_iterator::operator--()
{
    _pointer = _getPredecessor(_pointer);
    return *this;
}

/**
         * @brief This method enables the operation of "iter --" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: const_iterator::operator--(int)
{
    const_iterator temp = *this;
    _pointer = _getPredecessor(_pointer);
    return temp;
}

/**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff equal, false otherwise
         */
template<class T>
bool my_set<T> :: const_iterator :: operator==(const my_set::const_iterator &other) const
{
    return (_pointer == other._pointer);
}

/**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff different, false otherwise
         */
template<class T>
bool my_set<T> :: const_iterator :: operator!=(const my_set::const_iterator &other) const
{
    return !(operator==(other));
}

// ----------- const_reverse_iterator operators ----------- //
/**
         * @brief This method enables the operation of "++ iter" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
template<class T>
typename my_set<T> :: const_iterator &my_set<T> :: const_reverse_iterator::operator++()
{
    const_iterator :: _pointer = _getPredecessor(const_iterator::_pointer);
    return *this;
}

/**
         * @brief This method enables the operation of "iter ++" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: const_reverse_iterator::operator++(int)
{
    const_iterator temp = *this;
    const_iterator :: _pointer = _getPredecessor(const_iterator::_pointer);
    return temp;
}

/**
         * @brief This method enables the operation of "iter --" (on a "const_iterator" called "iter")
         * @return a reference to the iterator
         */
template<class T>
typename my_set<T> :: const_iterator &my_set<T> :: const_reverse_iterator::operator--()
{
    const_iterator :: _pointer = _getSuccessor(const_iterator::_pointer);
    return *this;
}

/**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff equal, false otherwise
         */
template<class T>
typename my_set<T> :: const_iterator my_set<T> :: const_reverse_iterator::operator--(int)
{
    const_iterator temp = *this;
    const_iterator :: _pointer = _getSuccessor(const_iterator::_pointer);
    return temp;
}

/**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff different, false otherwise
         */
template<class T>
bool my_set<T> :: const_reverse_iterator :: operator==(const my_set::const_reverse_iterator &other) const
{
    return (const_iterator :: _pointer == other._pointer);
}

/**
         * @brief This method enables comparing 2 "const_iterator" objects
         * @param other The object we'd like to compare "this" to
         * @return true iff different, false otherwise
         */
template<class T>
bool my_set<T> :: const_reverse_iterator::operator!=(const my_set::const_reverse_iterator &other) const
{
    return !(operator==(other));
}


#endif //EX3_MY_SET_HPP
